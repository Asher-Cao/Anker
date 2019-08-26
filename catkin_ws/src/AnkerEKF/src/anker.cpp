#include "anker.h"

Anker::Anker(std::string str):anker_str(str)
{
  anker_data_subscriber = node.subscribe("/anker_data_topic",10,&Anker::ankerDataCallback,this);
  anker_path_ekf_publisher = node.advertise<nav_msgs::Path>("path_ekf", 1000);
  anker_path_odometry_publisher = node.advertise<nav_msgs::Path>("path_odometry", 1000);
  anker_path_tmp_publisher = node.advertise<nav_msgs::Path>("path_tmp", 1000);
  anker_pose.tilt_angle = 0;
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
    if(anker_ekf_estimator)
    {
      double delta_time_s = cur_data.time_s - last_data.time_s;
      if(fabs(delta_time_s - 0.01f) > 0.005f )
        ROS_ERROR("Delta Time is wrong: %f !",delta_time_s);
      //anker_ekf_estimator->ankerEkfFusion(cur_data,delta_time_s);
      //publishPath();
    }
  }

  last_data = cur_data;
}

bool Anker::ankerInitialization()
{
  static bool flg[2] ={false};
  //return imu.calibrationAccScalarAndBias(cur_data);;
  if(flg[0] == false)
   flg[0] = imu.calibrationGyroBias(cur_data);
  if(flg[1] == false)
   flg[1] = imu.imuAlignWithAnkerBody(cur_data);
  return (flg[0]&&flg[1]);
}

void Anker::constructAnkerEkfEstimator()
{
  ekf_state _state;
  _state.w_px = anker_pose.position[0];
  _state.w_py = anker_pose.position[1];
  _state.yaw = anker_pose.euler_rad[2];
  _state.b_v = 0;
  _state.w = 0;
  _state.w_bias = imu.getGyroBias()[2];
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
  Eigen::Vector3d delta_yaw_2 = (cur_data.Gyro - imu.getGyroBias())*delta_time_s;
  tmp_pose.euler_rad +=  Eigen::Vector3d(0,0,delta_yaw_2[2]);
  //tmp_pose.euler_rad += delta_yaw_2;
  tmp_pose.euler2matrix();
  tmp_pose.euler2quaternion();
  tmp_pose.position[0] +=  delta_pos*cos(tmp_pose.euler_rad[2]);
  tmp_pose.position[1] +=  delta_pos*sin(tmp_pose.euler_rad[2]);

  ROS_WARN("CurTime: %f, Odometry Yaw: %f, IMU_Angle: (%f,%f,%f)",cur_data.time_s,anker_pose.euler_rad[2]*rad2deg,tmp_pose.euler_rad[0]*rad2deg,tmp_pose.euler_rad[1]*rad2deg,tmp_pose.euler_rad[2]*rad2deg);

  //  double delta_time_s = cur_data.time_s - last_data.time_s;
//  double vel = 0.5f*(cur_data.Odometry_vel[0] + cur_data.Odometry_vel[1]);
//  double delta_pose = vel*delta_time_s;
//  anker_pose.position_opt[0] += delta_pose*cos(anker_pose.euler_rad[2]);
//  anker_pose.position_opt[1] += delta_pose*sin(anker_pose.euler_rad[2]);

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
 // ROS_INFO("Anker POSE: (%f,%f,%f)",anker_pose.position[0],anker_pose.position[1],anker_pose.euler_rad[2]*rad2deg);

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
  Eigen::Quaterniond tmp_q;
  tmp_q = tmp_yaw;
  pose_stamped_tmp.pose.orientation.x = tmp_q.x();
  pose_stamped_tmp.pose.orientation.y = tmp_q.y();
  pose_stamped_tmp.pose.orientation.z = tmp_q.z();
  pose_stamped_tmp.pose.orientation.w = tmp_q.w();
  path_ekf.header.frame_id = "world";
  path_ekf.poses.push_back(pose_stamped_tmp);
  anker_path_ekf_publisher.publish(path_ekf);

}
