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
  void ankerEkfFusion();
  void ankerMotionPropagateFromOptical();
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
    Eigen::Vector3f position_opt;
    Eigen::Vector3f euler_rad;
    Eigen::Matrix3f rotation_matrix;
    float w_bais;
    float opt_angle;
    float opt_length;
    void euler2matrix()
    {
      Eigen::AngleAxisf aa_roll( Eigen::AngleAxisf(euler_rad[0],Eigen::Vector3f::UnitX()));
      Eigen::AngleAxisf aa_pitch( Eigen::AngleAxisf(euler_rad[1],Eigen::Vector3f::UnitY()));
      Eigen::AngleAxisf aa_yaw( Eigen::AngleAxisf(euler_rad[2],Eigen::Vector3f::UnitZ()));
      rotation_matrix = aa_roll*aa_pitch*aa_yaw;
    }
    void euler2quaternion()
    {
      Eigen::AngleAxisf aa_roll( Eigen::AngleAxisf(euler_rad[0],Eigen::Vector3f::UnitX()));
      Eigen::AngleAxisf aa_pitch( Eigen::AngleAxisf(euler_rad[1],Eigen::Vector3f::UnitY()));
      Eigen::AngleAxisf aa_yaw( Eigen::AngleAxisf(euler_rad[2],Eigen::Vector3f::UnitZ()));
      q = aa_roll*aa_pitch*aa_yaw;
    }
  };
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
