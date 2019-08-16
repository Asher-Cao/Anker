#include "anker.h"

Anker::Anker(std::string str):anker_str(str)
{

  anker_data_subscriber = node.subscribe("/anker_data_topic",10,&Anker::ankerDataCallback,this);
  anker_path_publisher = node.advertise<nav_msgs::Path>("path", 1000);
}
Anker::~Anker()
{

}
void Anker::ankerDataCallback(const anker_ekf_pro::AnkerDataType ankerdata_msg)
{
  extractAnkerDatas(ankerdata_msg);

  tf::Transform transform;
  transform.setOrigin(tf::Vector3(cur_data.Optical_pos[0],cur_data.Optical_pos[1],0));
 // float delta_left = cur_data.Odometry_pos[0] - last_data.Odometry_pos[0];
 // float delta_right = cur_data.Odometry_pos[1] - last_data.Odometry_pos[1];
 // cout << "Current TIME: " <<   cur_data.time_s << " s " << "pos: " << cur_data.Optical_pos[0] << " " << cur_data.Optical_pos[1] <<" " << yaw << endl;

  tf::Quaternion q;
  q.setRPY(0, 0, yaw);
  transform.setRotation(q);
  tf_br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", anker_str));
  last_data = cur_data;
}
void Anker::extractAnkerDatas(const anker_ekf_pro::AnkerDataType ankerdata_msg)
{
  cur_data.time_s = ankerdata_msg.time_s;
  cur_data.Acc << ankerdata_msg.ax ,ankerdata_msg.ay ,ankerdata_msg.az ;
  cur_data.Gyro << ankerdata_msg.gx,ankerdata_msg.gy,ankerdata_msg.gz;
  cur_data.Odometry_pos << ankerdata_msg.odo_left_pos,ankerdata_msg.odo_right_pos;
  cur_data.Odometry_vel << ankerdata_msg.odo_left_vel,ankerdata_msg.odo_right_vel;
  cur_data.Optical_pos << ankerdata_msg.opt_pos_x,ankerdata_msg.opt_pos_y;
  cur_data.Optical_quality = ankerdata_msg.opt_quality;
  cur_data.Wall_distance << ankerdata_msg.wall_distance_left,ankerdata_msg.wall_distance_right;
}
void Anker::publishPath()
{
  geometry_msgs::PoseStamped pose_stamped;
  pose_stamped.header = odometry.header;
  pose_stamped.pose = odometry.pose.pose;
  path.header = odometry.header;
  path.poses.push_back(pose_stamped);
  pub_path.publish(path);

}
