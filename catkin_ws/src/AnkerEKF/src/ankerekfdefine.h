#ifndef ANKEREKFDEFINE_H
#define ANKEREKFDEFINE_H
#include <Eigen/Core>
#include <Eigen/Geometry>
struct ekf_state
{
    float w_px;
    float w_py;
    float yaw;
    float b_vx;
    float b_vy;
    float w_bias;
};
struct ekf_matrix{
    Eigen::Matrix<float,6,6> P;
    Eigen::Matrix<float,6,6> F;
    Eigen::Matrix<float,6,6> Q;
    Eigen::Matrix<float,6,6> G;
    Eigen::Matrix<float,4,6> H;
    Eigen::Matrix<float,12,6> R;
    Eigen::Matrix<float,4,5> M;
};
struct ekf_motionNoise{
    float pos_x_noise;
    float pos_y_noise;
    float vel_x_noise;
    float vel_y_noise;
    float gyro_noise;
    float gyro_bias_noise;

};
struct ekf_measurementNoise
{
    float gyro_bias_noise;
    float optical_vel_x_noise_q;
    float optical_vel_y_noise_q;
    float odometry_vel_l_noise_q;
    float odometry_vel_r_noise_q;
};
#endif // ANKEREKFDEFINE_H
