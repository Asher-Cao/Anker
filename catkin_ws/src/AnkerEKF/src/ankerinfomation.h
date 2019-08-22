#ifndef ANKERINFOMATION_H
#define ANKERINFOMATION_H
#include <Eigen/Core>
#include <Eigen/Geometry>

#define wheel_distance 0.2063f
#define ImuDistX  0.1205f;
#define ImuDistY  0.0103f;
#define OpticalDistX 0.101f
#define OpticalDistY 0.087f
#define rad2deg  57.29578f
#define deg2rad  0.017453292f

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

#endif // ANKERINFOMATION_H
