#ifndef ANKER_H
#define ANKER_H
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <ros/ros.h>
#include <anker_ekf_pro/AnkerDataType.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Path.h>
#include <iostream>
#include <math.h>
#include "ankerinfomation.h"
#include "AnkerEkfEstimator.h"
using namespace std;
class Anker
{
public:
  Anker(std::string str);
  ~Anker();
  void ankerDataCallback(const anker_ekf_pro::AnkerDataType ankerdata_msg);
  void extractAnkerDatas(const anker_ekf_pro::AnkerDataType ankerdata_msg);
  void constructAnkerEkfEstimator();
  bool ankerInitialization();
  void ankerMotionPropagate();
  void ankerMotionPropagateFromOptical();
  void publishPath();


protected:
  ros::NodeHandle node;
  tf::TransformBroadcaster tf_br;
  std::string anker_str;
  ros::Subscriber anker_data_subscriber;
  ros::Publisher anker_path_ekf_publisher;
  ros::Publisher anker_path_odometry_publisher;
  nav_msgs::Path path_ekf;
  nav_msgs::Path path_odometry;
  bool initial_flg;
  AnkerEkfEstimator *anker_ekf_estimator;
private:
  AnkerDataType cur_data;
  AnkerDataType last_data;
  AnkerPose anker_pose;

};

#endif // ANKER_H
