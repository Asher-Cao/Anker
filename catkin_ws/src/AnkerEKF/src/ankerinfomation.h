#ifndef ANKERINFOMATION_H
#define ANKERINFOMATION_H
#include <Eigen/Core>
#include <Eigen/Geometry>

#define wheel_distance 0.209f
#define ImuDistX  0.1205f;
#define ImuDistY  0.0103f;
#define OpticalDistX 0.087f
#define OpticalDistY 0.101f

#define rad2deg  57.29578f
#define deg2rad  0.017453292f
#define gyro_z_noise_density  0.00014467f
#define gyro_z_noise_random_walk    0.00000413f

struct AnkerDataType
{
  double time_s;
  Eigen::Vector3d Gyro;
  Eigen::Vector3d Acc;
  Eigen::Vector2d Odometry_pos;
  Eigen::Vector2d Odometry_vel;
  Eigen::Vector2d Optical_pos;
  Eigen::Vector2i Wall_distance;
  unsigned short int Optical_quality;
};

struct AnkerPose
{
  Eigen::Quaterniond q;
  Eigen::Vector3d position;
  Eigen::Vector3d position_opt;
  Eigen::Vector3d euler_rad;
  Eigen::Matrix3d rotation_matrix;
  double w_bais;
  double opt_angle;
  double opt_length;
  void euler2matrix()
  {
    Eigen::AngleAxisd aa_roll( Eigen::AngleAxisd(euler_rad[0],Eigen::Vector3d::UnitX()));
    Eigen::AngleAxisd aa_pitch( Eigen::AngleAxisd(euler_rad[1],Eigen::Vector3d::UnitY()));
    Eigen::AngleAxisd aa_yaw( Eigen::AngleAxisd(euler_rad[2],Eigen::Vector3d::UnitZ()));
    rotation_matrix = aa_roll*aa_pitch*aa_yaw;
  }
  void euler2quaternion()
  {
    Eigen::AngleAxisd aa_roll( Eigen::AngleAxisd(euler_rad[0],Eigen::Vector3d::UnitX()));
    Eigen::AngleAxisd aa_pitch( Eigen::AngleAxisd(euler_rad[1],Eigen::Vector3d::UnitY()));
    Eigen::AngleAxisd aa_yaw( Eigen::AngleAxisd(euler_rad[2],Eigen::Vector3d::UnitZ()));
    q = aa_roll*aa_pitch*aa_yaw;
  }
};

#endif // ANKERINFOMATION_H
