#include "anker.h"

Anker::Anker(std::string str):anker_str(str)
{
  anker_data_subscriber = node.subscribe("/anker_data_topic",10,&Anker::ankerDataCallback,this);
  anker_path_ekf_publisher = node.advertise<nav_msgs::Path>("path_ekf", 1000);
  anker_path_odometry_publisher = node.advertise<nav_msgs::Path>("path_odometry", 1000);
  anker_path_tmp_publisher = node.advertise<nav_msgs::Path>("path_tmp", 1000);

  anker_pose.w_bais = 0;
  anker_pose.euler_rad << 0,0,0;
  anker_pose.position << 0,0,0;
  anker_pose.position_opt << 0,0,0;
  anker_pose.euler2matrix();
  anker_pose.euler2quaternion();
  anker_pose.opt_angle = atan2(OpticalDistY,OpticalDistX);
  anker_pose.opt_length = sqrt(OpticalDistX*OpticalDistX + OpticalDistY*OpticalDistY);

  tmp_pose.position << 0,0,0;
  tmp_pose.euler_rad << 0,0,0;

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

    ankerMotionPropagate();
    //ankerMotionPropagateFromOptical();
    if(anker_ekf_estimator)
    {
      double delta_time_s = cur_data.time_s - last_data.time_s;
      anker_ekf_estimator->ankerEkfFusion(cur_data,delta_time_s);
      publishPath();
    }
  }

  last_data = cur_data;
}
void Anker::constructAnkerEkfEstimator()
{
  ekf_state _state;
  _state.w_px = anker_pose.position[0];
  _state.w_py = anker_pose.position[1];
  _state.yaw = anker_pose.euler_rad[2];
  _state.b_v = 0;
  _state.w = 0;
  _state.w_bias = anker_pose.w_bais;
  ekf_motionNoise _motion_noise;
  _motion_noise.body_vel_noise = 0.04f;
  _motion_noise.gyro_noise = gyro_z_noise_density;
  _motion_noise.gyro_bias_noise = gyro_z_noise_random_walk;
  ekf_measurementNoise _measurement_noise;
  _measurement_noise.odometry_vel_l_noise_q = 0.001f;
  _measurement_noise.odometry_vel_r_noise_q = 0.001f;
  ROS_INFO("Construct ekf begin!");
  anker_ekf_estimator = new AnkerEkfEstimator(_state,_motion_noise,_measurement_noise);
  ROS_INFO("Construct ekf over!");
}
bool Anker::ankerInitialization()
{
  static double count = 0;
  static double w_sum = 0;
  static double begin_time = 0;
  if(fabs(cur_data.Odometry_vel[0]) > 0.0001f || fabs(cur_data.Odometry_vel[1]) > 0.0001f || count == 0)
  {
    begin_time = cur_data.time_s;
    count = 0;
    w_sum = 0;
  }
  if((cur_data.time_s - begin_time) > 10.0f)
  {
    anker_pose.w_bais = w_sum/count;
    ROS_INFO("Average %f wz, Initialize wz_bias : %f deg/s",count,anker_pose.w_bais*rad2deg);
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
  //Coordinate of robot:
  // x -- forward
  // y -- left
  // z -- up
  double delta_left = cur_data.Odometry_pos[0] - last_data.Odometry_pos[0];
  double delta_right = cur_data.Odometry_pos[1] - last_data.Odometry_pos[1];
  double delta_yaw_1 = (delta_right - delta_left)/wheel_distance;



  anker_pose.euler_rad += Eigen::Vector3d(0,0,delta_yaw_1);
  anker_pose.euler2matrix();
  anker_pose.euler2quaternion();
  double delta_pos = 0.5f*(cur_data.Odometry_pos[0] + cur_data.Odometry_pos[1] - last_data.Odometry_pos[0] - last_data.Odometry_pos[1]);
  anker_pose.position[0] +=  delta_pos*cos(anker_pose.euler_rad[2]);
  anker_pose.position[1] +=  delta_pos*sin(anker_pose.euler_rad[2]);


  double delta_time_s = cur_data.time_s - last_data.time_s;
  double delta_yaw_2 = (cur_data.Gyro[2] - anker_pose.w_bais)*delta_time_s;
  tmp_pose.euler_rad += Eigen::Vector3d(0,0,delta_yaw_2);
  tmp_pose.euler2matrix();
  tmp_pose.euler2quaternion();
  tmp_pose.position[0] +=  delta_pos*cos(tmp_pose.euler_rad[2]);
  tmp_pose.position[1] +=  delta_pos*sin(tmp_pose.euler_rad[2]);
  // this is for comparision between odometry yaw and imu yaw
  //  double delta_time_s = cur_data.time_s - last_data.time_s;
  //  anker_pose.euler_rad[0] += (cur_data.Gyro[2] - anker_pose.w_bais)*delta_time_s;
  //  ROS_INFO("Odometry yaw: %f  IMU yaw: %f ",anker_pose.euler_rad[2]*rad2deg,anker_pose.euler_rad[0]*rad2deg);
  //anker_pose.position_opt[0] = anker_pose.position[0] + anker_pose.opt_length*sin(3.141592f/2.0f - anker_pose.opt_angle - anker_pose.euler_rad[2]);
  //anker_pose.position_opt[1] = anker_pose.position[1] + anker_pose.opt_length*cos(3.141592f/2.0f - anker_pose.opt_angle - anker_pose.euler_rad[2]);
  //ROS_WARN("YAW: %f, GYRO_Z: %f",anker_pose.euler_rad[2],cur_data.Gyro[2]);
//  double delta_time_s = cur_data.time_s - last_data.time_s;
//  double vel = 0.5f*(cur_data.Odometry_vel[0] + cur_data.Odometry_vel[1]);
//  double delta_pose = vel*delta_time_s;
//  anker_pose.position_opt[0] += delta_pose*cos(anker_pose.euler_rad[2]);
//  anker_pose.position_opt[1] += delta_pose*sin(anker_pose.euler_rad[2]);

}


void Anker::ankerMotionPropagateFromOptical()
{
  //  static double sum_length =0,sum_length_from_imu=0;
 // double delta_time_s = cur_data.time_s - last_data.time_s;
  double delta_x = cur_data.Optical_pos[0] - last_data.Optical_pos[0];
 // double delta_y = cur_data.Optical_pos[1] - last_data.Optical_pos[1];
  double delta_left = cur_data.Odometry_pos[0] - last_data.Odometry_pos[0];
  double delta_right = cur_data.Odometry_pos[1] - last_data.Odometry_pos[1];
  double delta_yaw = (delta_right - delta_left)/wheel_distance;
  double delta_pose = delta_x + delta_yaw*OpticalDistX;
  anker_pose.euler_rad += Eigen::Vector3d(0,0,delta_yaw);
  anker_pose.position_opt[0] += delta_pose*cos(anker_pose.euler_rad[2]);
  anker_pose.position_opt[1] += delta_pose*sin(anker_pose.euler_rad[2]);
  /*
  double delta_x = cur_data.Optical_pos[0] - last_data.Optical_pos[0];
  double delta_y = cur_data.Optical_pos[1] - last_data.Optical_pos[1];
  double length = sqrt(delta_x*delta_x+delta_y*delta_y);
  double delta_t = cur_data.time_s - last_data.time_s;
  double length_from_imu = delta_t*anker_pose.opt_length*fabs(cur_data.Gyro[2] - anker_pose.w_bais)/rad2deg;
  sum_length += length;
  sum_length_from_imu += length_from_imu;
  ROS_INFO("Opt Delta length: %f, W*d = %f, ratio = %f ",length,length_from_imu,length/length_from_imu);
  ROS_WARN("Sum from Opt : %f, Sum from ratation :%f",sum_length,sum_length_from_imu);*/
  //anker_pose.euler_rad += Eigen::Vector3d(0,0,delta_yaw);
  anker_pose.euler2matrix();
  anker_pose.euler2quaternion();
  ROS_INFO("Pose Yaw: %f",anker_pose.euler_rad[2]*rad2deg);
}
void Anker::extractAnkerDatas(const anker_ekf_pro::AnkerDataType ankerdata_msg)
{
  cur_data.time_s = ankerdata_msg.time_s;
  cur_data.Acc << ankerdata_msg.ax,ankerdata_msg.ay,ankerdata_msg.az;
  cur_data.Gyro << ankerdata_msg.gx*deg2rad,ankerdata_msg.gy*deg2rad,ankerdata_msg.gz*deg2rad;
  cur_data.Odometry_pos << ankerdata_msg.odo_left_pos,ankerdata_msg.odo_right_pos;
  cur_data.Odometry_vel << ankerdata_msg.odo_left_vel,ankerdata_msg.odo_right_vel;
  cur_data.Optical_pos << -ankerdata_msg.opt_pos_y,-ankerdata_msg.opt_pos_x;
  cur_data.Optical_quality = ankerdata_msg.opt_quality;
  cur_data.Wall_distance << ankerdata_msg.wall_distance_left,ankerdata_msg.wall_distance_right;
}
void Anker::publishPath()
{

  tf::Transform transform;
  transform.setOrigin(tf::Vector3(anker_pose.position[0],anker_pose.position[1],0));
  double yaw = anker_pose.euler_rad[2];
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


  geometry_msgs::PoseStamped tmp_pose_stamped;
  tmp_pose_stamped.header.frame_id = "world";
  tmp_pose_stamped.pose.position.x = tmp_pose.position[0];
  tmp_pose_stamped.pose.position.y = tmp_pose.position[1];
  tmp_pose_stamped.pose.position.z = tmp_pose.position[2];
  tmp_pose_stamped.pose.orientation.x = tmp_pose.q.x();
  tmp_pose_stamped.pose.orientation.y = tmp_pose.q.y();
  tmp_pose_stamped.pose.orientation.z = tmp_pose.q.z();
  tmp_pose_stamped.pose.orientation.w = tmp_pose.q.w();
  path_tmp.header.frame_id = "world";
  path_tmp.poses.push_back(tmp_pose_stamped);
  anker_path_tmp_publisher.publish(path_tmp);


  geometry_msgs::PoseStamped pose_stamped_tmp;
  pose_stamped_tmp.header.frame_id = "world";
  pose_stamped_tmp.pose.position.x = anker_ekf_estimator->state.w_px;
  pose_stamped_tmp.pose.position.y = anker_ekf_estimator->state.w_py;
  pose_stamped_tmp.pose.position.z = 0;
  Eigen::AngleAxisd tmp_yaw( Eigen::AngleAxisd(anker_ekf_estimator->state.yaw,Eigen::Vector3d::UnitZ()));
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
