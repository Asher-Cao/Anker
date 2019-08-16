#ifndef ANKER_H
#define ANKER_H
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <ros/ros.h>
#include <anker_ekf_pro/AnkerDataType.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Path.h>
#include <iostream>
#define wheel_distance 0.205f
#define rad2deg  57.29578f
using namespace std;
class Anker
{
public:
  Anker(std::string str);
  ~Anker();
  void ankerDataCallback(const anker_ekf_pro::AnkerDataType ankerdata_msg);
  void extractAnkerDatas(const anker_ekf_pro::AnkerDataType ankerdata_msg);
  void publishPath();
  struct AnkerDataType
  {
    float time_s;
    Eigen::Vector3f Gyro;
    Eigen::Vector3f Acc;
    Eigen::Vector2f Odometry_pos;
    Eigen::Vector2f Odometry_vel;
    Eigen::Vector2f Optical_pos;
    Eigen::Vector2i Wall_distance;
    unsigned short int Optical_quality;
  };
  struct AnkerPose
  {
    Eigen::Quaternionf q;
    Eigen::Vector3f position;
    Eigen::Vector3f euler_rad;
  };
protected:
  ros::NodeHandle node;
  tf::TransformBroadcaster tf_br;
  std::string anker_str;
  ros::Subscriber anker_data_subscriber;
  ros::Publisher anker_path_publisher;
  nav_msgs::Path path;

private:
  AnkerDataType cur_data;
  AnkerDataType last_data;
  AnkerPose anker_pose;
};

#endif // ANKER_H
