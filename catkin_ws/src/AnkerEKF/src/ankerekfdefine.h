#ifndef ANKEREKFDEFINE_H
#define ANKEREKFDEFINE_H
#include <Eigen/Core>
#include <Eigen/Geometry>
struct ekf_state
{
    float w_px;
    float w_py;
    float yaw;
    float b_v;
    float w;
    float w_bias;
};
struct ekf_matrix{
    Eigen::Matrix<float,6,6> P;
    Eigen::Matrix<float,6,6> F;
    Eigen::Matrix<float,3,3> Q;
    Eigen::Matrix<float,6,3> G;
    Eigen::Matrix<float,2,6> H;
    Eigen::Matrix<float,2,2> R;
    Eigen::Matrix<float,2,2> M;
};
struct ekf_motionNoise{
    float body_vel_noise;
    float gyro_noise;
    float gyro_bias_noise;
};
struct ekf_measurementNoise
{
    float odometry_vel_l_noise_q;
    float odometry_vel_r_noise_q;
};
#endif // ANKEREKFDEFINE_H
