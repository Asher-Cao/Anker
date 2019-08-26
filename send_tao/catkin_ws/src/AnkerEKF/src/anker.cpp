#include "anker.h"

Anker::Anker(std::string str):anker_str(str)
{
  anker_data_subscriber = node.subscribe("/anker_data_topic",10,&Anker::ankerDataCallback,this);
  anker_path_ekf_publisher = node.advertise<nav_msgs::Path>("path_ekf", 1000);
  anker_path_odometry_publisher = node.advertise<nav_msgs::Path>("path_odometry", 1000);

  anker_pose.w_bais = 0;
  anker_pose.euler_rad << 0,0,0;
  anker_pose.position << 0,0,0;
  anker_pose.position_opt << 0,0,0;
  anker_pose.euler2matrix();
  anker_pose.euler2quaternion();
  anker_pose.opt_angle = atan2(OpticalDistY,OpticalDistX);
  anker_pose.opt_length = sqrt(OpticalDistX*OpticalDistX + OpticalDistY*OpticalDistY);

  initial_flg = true;
}
Anker::~Anker()
{

}
void Anker::ankerDataCallback(const anker_ekf_pro::AnkerDataType ankerdata_msg)
{
  extractAnkerDatas(ankerdata_msg);
  if(initial_flg){
    initial_flg = !ankerInitialization();
    if(!initial_flg)
    {
      constructAnkerEkfEstimator();
    }
  }
  else
  {
    ankerEkfFusion();
    ankerMotionPropagate();
    publishPath();
  }

  last_data = cur_data;
}
void Anker::constructAnkerEkfEstimator()
{
  ekf_state _state;
  _state.w_px = anker_pose.position[0];
  _state.w_py = anker_pose.position[1];
  _state.b_vx = 0;
  _state.b_vy = 0;
  _state.yaw = anker_pose.euler_rad[2];
  _state.w_bias = anker_pose.w_bais;
  ekf_motionNoise _motion_noise;
  _motion_noise.pos_x_noise = 0.01f;
  _motion_noise.pos_y_noise = 0.01f;
  _motion_noise.vel_x_noise = 0.02f;
  _motion_noise.vel_y_noise = 0.02f;
  _motion_noise.gyro_noise = 0.0001f;
  _motion_noise.gyro_bias_noise = 0.00001f;
  ekf_measurementNoise _measurement_noise;
  _measurement_noise.gyro_bias_noise = _motion_noise.gyro_bias_noise;
  _measurement_noise.optical_vel_x_noise_q = 0.001f;
  _measurement_noise.optical_vel_y_noise_q = 0.001f;
  _measurement_noise.odometry_vel_l_noise_q = 0.001f;
  _measurement_noise.odometry_vel_r_noise_q = 0.001f;
  ROS_INFO("Construct ekf begin!");
  anker_ekf_estimator = new AnkerEkfEstimator(_state,_motion_noise,_measurement_noise);
  ROS_INFO("Construct ekf over!");
}
bool Anker::ankerInitialization()
{
  static float count = 0;
  static float w_sum = 0;
  static float begin_time = 0;
  if(fabs(cur_data.Odometry_vel[0]) > 0.0001f || fabs(cur_data.Odometry_vel[1]) > 0.0001f || count == 0)
  {
    begin_time = cur_data.time_s;
    count = 0;
    w_sum = 0;
  }
  if((cur_data.time_s - begin_time) > 5.0f)
  {
    anker_pose.w_bais = w_sum/count;
    ROS_INFO("Average %f wz, Initialize wz_bias : %f rad/s",count,anker_pose.w_bais);
    count = 0;
    w_sum = 0;
    begin_time = 0;
    return true;
  }else{
    count++;
    w_sum += cur_data.Gyro[2];
  }
  return false;
}
void Anker::ankerMotionPropagate()
{
  float delta_left = cur_data.Odometry_pos[0] - last_data.Odometry_pos[0];
  float delta_right = cur_data.Odometry_pos[1] - last_data.Odometry_pos[1];
  float delta_yaw = (delta_left - delta_right)/wheel_distance;
  anker_pose.euler_rad += Eigen::Vector3f(0,0,delta_yaw);
  // this is for comparision between odometry yaw and imu yaw
  //  float delta_time_s = cur_data.time_s - last_data.time_s;
  //  anker_pose.euler_rad[0] += (cur_data.Gyro[2] - anker_pose.w_bais)*delta_time_s;
  //  ROS_INFO("Odometry yaw: %f  IMU yaw: %f ",anker_pose.euler_rad[2]*rad2deg,anker_pose.euler_rad[0]*rad2deg);
  anker_pose.euler2matrix();
  anker_pose.euler2quaternion();
  float delta_pos = 0.5f*(cur_data.Odometry_pos[0] + cur_data.Odometry_pos[1] - last_data.Odometry_pos[0] - last_data.Odometry_pos[1]);
  anker_pose.position[0] +=  delta_pos*cos(anker_pose.euler_rad[2]);
  anker_pose.position[1] +=  delta_pos*sin(anker_pose.euler_rad[2]);
  anker_pose.position_opt[0] = anker_pose.position[0] + anker_pose.opt_length*sin(3.141592f/2.0f - anker_pose.opt_angle - anker_pose.euler_rad[2]);
  anker_pose.position_opt[1] = anker_pose.position[1] + anker_pose.opt_length*cos(3.141592f/2.0f - anker_pose.opt_angle - anker_pose.euler_rad[2]);
  ROS_WARN("YAW: %f, GYRO_Z: %f",anker_pose.euler_rad[2],cur_data.Gyro[2]);
}
void Anker::ankerEkfFusion()
{


  float delta_time_s = cur_data.time_s - last_data.time_s;
  float w_px = anker_ekf_estimator->state.w_px;
  float w_py = anker_ekf_estimator->state.w_py;
  float yaw = anker_ekf_estimator->state.yaw;
  float b_vx = anker_ekf_estimator->state.b_vx;
  float b_vy = anker_ekf_estimator->state.b_vy;
  float w_bias = anker_ekf_estimator->state.w_bias;
  Eigen::Matrix<float,6,1> predict_state;
  //step1:prediction
  //predict state
  predict_state(0,0) = w_px + (cos(yaw)*b_vx - sin(yaw)*b_vy)*delta_time_s;
  predict_state(1,0) = w_py + (sin(yaw)*b_vx + cos(yaw)*b_vy)*delta_time_s;
  predict_state(2,0) = yaw  + (cur_data.Gyro[2] - w_bias)*delta_time_s;
  predict_state(3,0) = b_vx;
  predict_state(4,0) = b_vy;
  predict_state(5,0) = w_bias;
  //predict covariance
  anker_ekf_estimator->updateJacbianF(delta_time_s);
  anker_ekf_estimator->updateMatrixG(delta_time_s);
  Eigen::Matrix<float,6,6>  predict_P = anker_ekf_estimator->predictCovariance();

  //step2: update gain K
  Eigen::Matrix<float,6,4>  gain_matrix = anker_ekf_estimator->calculateGainMatrix(predict_P);

  //step3: fix state
  //measurement predicted by predict state.
  Eigen::Matrix<float,4,1> measurement_shouldbe;
  measurement_shouldbe(0,0) = b_vx + OpticalDistY*(cur_data.Gyro[2] - w_bias);
  measurement_shouldbe(1,0) = b_vy + OpticalDistX*(cur_data.Gyro[2] - w_bias);
  measurement_shouldbe(2,0) = b_vx + (cur_data.Gyro[2] - w_bias)*wheel_distance*0.5f;
  measurement_shouldbe(3,0) = b_vx - (cur_data.Gyro[2] - w_bias)*wheel_distance*0.5f;
  //real measurements
  float v_x = (cur_data.Optical_pos[0] - last_data.Optical_pos[0])/delta_time_s;
  float v_y = (cur_data.Optical_pos[1] - last_data.Optical_pos[1])/delta_time_s;
  Eigen::Matrix<float,4,1> measurement_z;
  measurement_z <<v_x,v_y,cur_data.Odometry_vel[0],cur_data.Odometry_vel[1];
  Eigen::Matrix<float,6,1> fix_state;
  //fix
  Eigen::Matrix<float,4,1> error_state = measurement_z - measurement_shouldbe;
  fix_state = predict_state + gain_matrix*error_state;
  anker_ekf_estimator->matrix.P = (Eigen::MatrixXf::Identity(6,6) - gain_matrix*anker_ekf_estimator->matrix.H)*predict_P;
  anker_ekf_estimator->updateState(fix_state);

  //infos
  //ROS_ERROR("State Error: OpticalVel(%f,%f) OdometryVel(%f,%f)",error_state(0,0),error_state(1,0),error_state(2,0),error_state(3,0));
  ROS_WARN("pos(%f,%f,%f), vel(%f,%f), w_bias(%f)",fix_state(0,0),fix_state(1,0),fix_state(2,0),fix_state(3,0),fix_state(4,0),fix_state(5,0));
//  anker_pose.position[0] = fix_state(0,0);
//  anker_pose.position[1] = fix_state(1,0);
//  anker_pose.euler_rad[2] = fix_state(2,0);
//  anker_pose.euler2matrix();
//  anker_pose.euler2quaternion();


}
void Anker::ankerMotionPropagateFromOptical()
{
  //  static float sum_length =0,sum_length_from_imu=0;
  float delta_time_s = cur_data.time_s - last_data.time_s;
  float v_x = (cur_data.Optical_pos[0] - last_data.Optical_pos[0])/delta_time_s;
  float v_y = (cur_data.Optical_pos[1] - last_data.Optical_pos[1])/delta_time_s;
  float v_x_w_d = (cur_data.Gyro[2] - anker_pose.w_bais)*OpticalDistX;
  float v_y_w_d = (cur_data.Gyro[2] - anker_pose.w_bais)*OpticalDistY;
  ROS_WARN("v_x     = %f    v_y     = %f",v_x,v_y);
  ROS_WARN("v_x_w_d = %f    v_y_w_d = %f",v_x_w_d,v_y_w_d);
  /*
  float delta_x = cur_data.Optical_pos[0] - last_data.Optical_pos[0];
  float delta_y = cur_data.Optical_pos[1] - last_data.Optical_pos[1];
  float length = sqrt(delta_x*delta_x+delta_y*delta_y);
  float delta_t = cur_data.time_s - last_data.time_s;
  float length_from_imu = delta_t*anker_pose.opt_length*fabs(cur_data.Gyro[2] - anker_pose.w_bais)/rad2deg;
  sum_length += length;
  sum_length_from_imu += length_from_imu;
  ROS_INFO("Opt Delta length: %f, W*d = %f, ratio = %f ",length,length_from_imu,length/length_from_imu);
  ROS_WARN("Sum from Opt : %f, Sum from ratation :%f",sum_length,sum_length_from_imu);*/
  //anker_pose.euler_rad += Eigen::Vector3f(0,0,delta_yaw);
  anker_pose.euler2matrix();
  anker_pose.euler2quaternion();
  ROS_INFO("Pose Yaw: %f",anker_pose.euler_rad[2]*rad2deg);
}
void Anker::extractAnkerDatas(const anker_ekf_pro::AnkerDataType ankerdata_msg)
{
  cur_data.time_s = ankerdata_msg.time_s;
  cur_data.Acc << ankerdata_msg.ax ,ankerdata_msg.ay ,ankerdata_msg.az ;
  cur_data.Gyro << ankerdata_msg.gx*deg2rad,ankerdata_msg.gy*deg2rad,-ankerdata_msg.gz*deg2rad;
  cur_data.Odometry_pos << ankerdata_msg.odo_left_pos,ankerdata_msg.odo_right_pos;
  cur_data.Odometry_vel << ankerdata_msg.odo_left_vel,ankerdata_msg.odo_right_vel;
  cur_data.Optical_pos << -ankerdata_msg.opt_pos_y,ankerdata_msg.opt_pos_x;
  cur_data.Optical_quality = ankerdata_msg.opt_quality;
  cur_data.Wall_distance << ankerdata_msg.wall_distance_left,ankerdata_msg.wall_distance_right;
}
void Anker::publishPath()
{

  tf::Transform transform;
  transform.setOrigin(tf::Vector3(anker_pose.position[0],anker_pose.position[1],0));
  float yaw = anker_pose.euler_rad[2];
  tf::Quaternion q;
  q.setRPY(0, 0, yaw);
  transform.setRotation(q);
  tf_br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", anker_str));
  ROS_INFO("Anker POSE: (%f,%f,%f)",anker_pose.position[0],anker_pose.position[1],anker_pose.euler_rad[2]*rad2deg);

  geometry_msgs::PoseStamped pose_stamped;
  pose_stamped.header.frame_id = "world";
  pose_stamped.pose.position.x = anker_pose.position[0];
  pose_stamped.pose.position.y = anker_pose.position[1];
  pose_stamped.pose.position.z = anker_pose.position[2];
  pose_stamped.pose.orientation.x = anker_pose.q.x();
  pose_stamped.pose.orientation.y = anker_pose.q.y();
  pose_stamped.pose.orientation.z = anker_pose.q.z();
  pose_stamped.pose.orientation.w = anker_pose.q.w();
  path_odometry.header.frame_id = "world";
  path_odometry.poses.push_back(pose_stamped);
  anker_path_odometry_publisher.publish(path_odometry);


  geometry_msgs::PoseStamped pose_stamped_tmp;
  pose_stamped_tmp.header.frame_id = "world";
  pose_stamped_tmp.pose.position.x = anker_ekf_estimator->state.w_px;
  pose_stamped_tmp.pose.position.y = anker_ekf_estimator->state.w_py;
  pose_stamped_tmp.pose.position.z = 0;
  Eigen::AngleAxisf tmp_yaw( Eigen::AngleAxisf(anker_ekf_estimator->state.yaw,Eigen::Vector3f::UnitZ()));
  Eigen::Quaternionf tmp_q;
  tmp_q = tmp_yaw;
  pose_stamped_tmp.pose.orientation.x = tmp_q.x();
  pose_stamped_tmp.pose.orientation.y = tmp_q.y();
  pose_stamped_tmp.pose.orientation.z = tmp_q.z();
  pose_stamped_tmp.pose.orientation.w = tmp_q.w();
  path_ekf.header.frame_id = "world";
  path_ekf.poses.push_back(pose_stamped_tmp);
  anker_path_ekf_publisher.publish(path_ekf);

}