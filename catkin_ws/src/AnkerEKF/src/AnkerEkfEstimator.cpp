#include "AnkerEkfEstimator.h"

AnkerEkfEstimator::AnkerEkfEstimator(ekf_state _state,ekf_motionNoise _motion_noise,ekf_measurementNoise _measure_noise)
  :state(_state),motion_noise(_motion_noise),measue_noise(_measure_noise)
{
  matrix.F = Eigen::MatrixXf::Identity(6,6);
  matrix.Q = Eigen::MatrixXf::Zero(6,6);
  matrix.Q(0,0) = motion_noise.pos_x_noise;
  matrix.Q(1,1) = motion_noise.pos_y_noise;
  matrix.Q(2,2) = motion_noise.vel_x_noise;
  matrix.Q(3,3) = motion_noise.vel_y_noise;
  matrix.Q(4,4) = motion_noise.gyro_noise;
  matrix.Q(5,5) = motion_noise.gyro_bias_noise;
  matrix.G = Eigen::MatrixXf::Zero(6,6);
  matrix.G(0,0) = 1.0f;
  matrix.G(1,1) = 1.0f;
  matrix.G(3,2) = 1.0f;
  matrix.G(4,3) = 1.0f;
  matrix.G(5,5) = 1.0f;


  matrix.H = Eigen::MatrixXf::Zero(4,6);
  matrix.H(0,3) =  1.0f;
  matrix.H(0,5) = -OpticalDistY;
  matrix.H(1,4) =  1.0f;
  matrix.H(1,5) = -OpticalDistX;
  matrix.H(2,3) =  1.0f;
  matrix.H(2,5) = -0.5f*wheel_distance;
  matrix.H(3,3) =  1.0f;
  matrix.H(3,5) =  0.5f*wheel_distance;
  matrix.R = Eigen::MatrixXf::Zero(5,5);
  matrix.R(0,0) = motion_noise.gyro_bias_noise;
  matrix.R(1,1) = measue_noise.optical_vel_x_noise_q;
  matrix.R(2,2) = measue_noise.optical_vel_y_noise_q;
  matrix.R(3,3) = measue_noise.odometry_vel_l_noise_q;
  matrix.R(4,4) = measue_noise.odometry_vel_r_noise_q;
  matrix.M = Eigen::MatrixXf::Zero(4,5);
  matrix.M(0,0) = -OpticalDistY;
  matrix.M(0,1) =  1.0f;
  matrix.M(1,0) = -OpticalDistX;
  matrix.M(1,2) =  1.0f;
  matrix.M(2,0) = -0.5f*wheel_distance;
  matrix.M(2,3) =  1.0f;
  matrix.M(3,0) =  0.5f*wheel_distance;
  matrix.M(3,4) =  1.0f;

  matrix.P = 0.01*Eigen::MatrixXf::Identity(6,6);
}


void AnkerEkfEstimator::updateJacbianF(float delta_time_s)
{
  matrix.F(0,2) = -(sin(state.yaw)*state.b_vx + cos(state.yaw)*state.b_vy)*delta_time_s;
  matrix.F(0,3) =  cos(state.yaw)*delta_time_s;
  matrix.F(0,4) = -sin(state.yaw)*delta_time_s;
  matrix.F(1,2) =  (cos(state.yaw)*state.b_vx - sin(state.yaw)*state.b_vy)*delta_time_s;
  matrix.F(1,3) =  sin(state.yaw)*delta_time_s;
  matrix.F(1,4) =  cos(state.yaw)*delta_time_s;
  matrix.F(2,5) = -delta_time_s;
}
void AnkerEkfEstimator::updateMatrixG(float delta_time_s)
{
  matrix.G(2,4) = delta_time_s;
}

Eigen::Matrix<float,6,6> AnkerEkfEstimator::predictCovariance()
{
  Eigen::Matrix<float,6,6> predict_P = matrix.F*matrix.P*matrix.F.transpose() + matrix.G*matrix.Q*matrix.G.transpose();
  return predict_P;

}
Eigen::Matrix<float,6,4> AnkerEkfEstimator::calculateGainMatrix(Eigen::Matrix<float,6,6>& predict_P)
{
  Eigen::Matrix<float,4,4>  tmp_matrix = matrix.H*predict_P*matrix.H.transpose() + matrix.M*matrix.R*matrix.M.transpose();
  Eigen::Matrix<float,6,4>  gain_matrix = predict_P*matrix.H.transpose()*tmp_matrix.inverse();
  return gain_matrix;
}

void AnkerEkfEstimator::updateState(Eigen::Matrix<float,6,1>& new_state)
{

  state.w_px = new_state(0,0);
  state.w_py = new_state(1,0);
  state.yaw = new_state(2,0);
  state.b_vx = new_state(3,0);
  state.b_vy = new_state(4,0);
  state.w_bias = new_state(5,0);
}















