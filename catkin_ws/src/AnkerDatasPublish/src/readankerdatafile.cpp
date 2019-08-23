#include "readankerdatafile.h"

ReadAnkerDataFile::ReadAnkerDataFile(const string& imu_file,const string& odometry_file,const string& optical_file)
{

  ifstream imu_fin;
  imu_fin.open(imu_file.c_str());
  if(!imu_fin)
  {
    ROS_ERROR("File %s doesn't exist!",imu_file.c_str());
  }
  ifstream odo_fin(odometry_file.c_str());
  if(!odo_fin)
  {
    ROS_ERROR("File %s doesn't exist!",odometry_file.c_str());
  }
  ifstream opt_fin(optical_file.c_str());
  if(!opt_fin)
  {
    ROS_ERROR("File %s doesn't exist!",optical_file.c_str());
  }

  string str_skip;
  getline(imu_fin, str_skip);
  ROS_INFO("IMU First Line : %s", str_skip.c_str());
  str_skip.clear();
  getline(odo_fin, str_skip);
  ROS_INFO("Odometry First Line : %s", str_skip.c_str());
  str_skip.clear();
  getline(opt_fin, str_skip);
  ROS_INFO("Optical First Line : %s", str_skip.c_str());
  double test_data_type;
  imu_fin >> test_data_type;
  int test_data_type_int = test_data_type;
  if(fabs(test_data_type - (double)test_data_type_int) > 0.00001f)
  {
    type_is_int = false;
    ROS_ERROR("Data type is float!!!");
  }
  else
  {
    type_is_int = true;
     ROS_ERROR("Data type is Int!!!");
  }
  bool lck = true;
  while(!imu_fin.eof())
  {
    double t_imu,t_odo,t_opt;
    if(lck == false)
      imu_fin >> t_imu;
    lck = false;
    odo_fin >> t_odo;
    opt_fin >> t_opt;
    if(type_is_int)
    {
      t_imu = t_imu*TIME_Resolution;
      t_odo = t_odo*TIME_Resolution;
      t_opt = t_opt*TIME_Resolution;
    }
    if(fabs(t_imu - t_odo) > 0.011f)
      continue;
    if(fabs(t_imu - t_opt) > 0.011f)
      continue;
    AnkerData raw_data;
    raw_data.time = t_imu;
    imu_fin >> raw_data.ax;
    imu_fin >> raw_data.ay;
    imu_fin >> raw_data.az;
    imu_fin >> raw_data.gx;
    imu_fin >> raw_data.gy;
    imu_fin >> raw_data.gz;

    odo_fin >> raw_data.odo_right_pos;
    odo_fin >> raw_data.odo_left_pos;
    odo_fin >> raw_data.odo_right_vel;
    odo_fin >> raw_data.odo_left_vel;

    opt_fin >> raw_data.opt_pos_x;
    opt_fin >> raw_data.opt_pos_y;
    opt_fin >> raw_data.opt_quality;
    opt_fin >> raw_data.wall_distance_left;
    opt_fin >> raw_data.wall_distance_right;
    if(type_is_int)
    {
      raw_data.time = raw_data.time*TIME_Resolution;
      raw_data.ax = raw_data.ax*ACC_Resolution;
      raw_data.ay = raw_data.ay*ACC_Resolution;
      raw_data.az = raw_data.az*ACC_Resolution;
      raw_data.gx = raw_data.gx*GYRO_Resolution;
      raw_data.gy = raw_data.gy*GYRO_Resolution;
      raw_data.gz = raw_data.gz*GYRO_Resolution;
      raw_data.odo_left_pos = raw_data.odo_left_pos*ODO_Resolution;
      raw_data.odo_right_pos = raw_data.odo_right_pos*ODO_Resolution;
      raw_data.odo_left_vel = raw_data.odo_left_vel*ODO_Resolution;
      raw_data.odo_right_vel = raw_data.odo_right_vel*ODO_Resolution;
      raw_data.opt_pos_x = raw_data.opt_pos_x*OPT_Resolution;
      raw_data.opt_pos_y = raw_data.opt_pos_y*OPT_Resolution;
    }

    AnkerDataSet.push_back(raw_data);
  }


}
