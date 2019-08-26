#include "imu.h"

IMU::IMU()
{
  paras.Acc_Bias << acc_bias_x,acc_bias_y,acc_bias_z;
  paras.Acc_Scalar << acc_scalar_x,acc_scalar_y,acc_scalar_z;
  paras.Gyro_Bias << 0,0,0;
}
bool IMU::calibrationAccScalarAndBias(AnkerDataType& data)
{
  static Eigen::Vector3d max_acc = Eigen::Vector3d(0,0,0);
  static Eigen::Vector3d min_acc = Eigen::Vector3d(0,0,0);
  static Eigen::Vector3d sum_acc = Eigen::Vector3d(0,0,0);
  static int count = 0;
  count++;
  sum_acc += data.Acc;
  if(count < 20)
    return false;
  Eigen::Vector3d Acc = sum_acc/count;
  sum_acc << 0,0,0;
  count = 0;
  for(int i=0;i<3;i++)
  {
    if(max_acc[i] < Acc[i])
    {
      max_acc[i] = Acc[i];
    }
    if(min_acc[i] > Acc[i])
    {
      min_acc[i] = Acc[i];
    }
  }
  for(int i=0;i<3;i++)
  {
    if(max_acc[i] < 9.5f)
      return false;
    if(min_acc[i] > -9.5f)
      return false;
  }
  if(fabs(Acc[2]) > 9.5f)
  {
    paras.Acc_Bias = (max_acc + min_acc)*0.5f;
    double g_inv = 1.0f/gravity_g;
    paras.Acc_Scalar = g_inv*(max_acc - min_acc)*0.5f;
    ROS_INFO("****************ACC Calibration**************");
    ROS_INFO("Acc Bias:(%f,%f,%f) m/s^2s",paras.Acc_Bias[0],paras.Acc_Bias[1],paras.Acc_Bias[2]);
    ROS_INFO("Acc Scalar:(%f,%f,%f)",paras.Acc_Scalar[0],paras.Acc_Scalar[1],paras.Acc_Scalar[2]);
    return true;
  }
  return false;
}
bool IMU::calibrationGyroBias(AnkerDataType& data)
{
  static double count = 0;
  static Eigen::Vector3d w_sum = Eigen::Vector3d(0,0,0);
  static double begin_time = 0;
  if(fabs(data.Odometry_vel[0]) > 0.0001f || fabs(data.Odometry_vel[1]) > 0.0001f || count == 0)
  {
    begin_time = data.time_s;
    count = 0;
    w_sum << 0,0,0;
  }
  if((data.time_s - begin_time) > gyro_calibration_time)
  {
    if(count > 1.0f)
    {
      paras.Gyro_Bias = w_sum/count;
      ROS_INFO("****************ACC Calibration**************");
      ROS_INFO("Gyro Bias : (%f,%f,%f)deg/s",paras.Gyro_Bias[0]*rad2deg,paras.Gyro_Bias[1]*rad2deg,paras.Gyro_Bias[2]*rad2deg);
      count = 0;
      w_sum << 0,0,0;
      begin_time = 0;
      return true;
    }else{
      count = 0;
      w_sum << 0,0,0;
      begin_time = 0;
      return false;
    }
  }else{
    count++;
    w_sum += data.Gyro;
  }
  return false;
}
bool IMU::imuAlignWithAnkerBody(AnkerDataType& data)
{
  static double count = 0;
  static Eigen::Vector3d acc_sum = Eigen::Vector3d(0,0,0);
  static double begin_time = 0;
  if(fabs(data.Odometry_vel[0]) > 0.0001f || fabs(data.Odometry_vel[1]) > 0.0001f || count == 0)
  {
    begin_time = data.time_s;
    count = 0;
    acc_sum << 0,0,0;
  }
  if((data.time_s - begin_time) > gyro_calibration_time)
  {
    if(count > 1.0f)
    {
      Eigen::Vector3d acc_average = acc_sum/count - paras.Acc_Bias;
      Eigen::Vector3d acc = Eigen::Vector3d(acc_average[0]*paras.Acc_Scalar[0],acc_average[1]*paras.Acc_Scalar[1],acc_average[2]*paras.Acc_Scalar[2]);
      paras.tilt_angle = atan2(sqrt(acc[0]*acc[0]+acc[1]*acc[1]),acc[2]);
      ROS_INFO("****************IMU Align With Anker**************");
      ROS_INFO("Align angle: %f deg",paras.tilt_angle*rad2deg);
      count = 0;
      acc_sum << 0,0,0;
      begin_time = 0;
      return true;
    }else{
      count = 0;
      acc_sum << 0,0,0;
      begin_time = 0;
      return false;
    }
  }else{
    count++;
    acc_sum += data.Acc;
  }
  return false;
}

