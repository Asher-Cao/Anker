#ifndef ANKEREKFESTIMATOR_H
#define ANKEREKFESTIMATOR_H
#include "ankerekfdefine.h"
#include "ankerinfomation.h"
class AnkerEkfEstimator
{
public:

  AnkerEkfEstimator(ekf_state _state,ekf_motionNoise _motion_noise,ekf_measurementNoise _measure_noise);
  void updateJacbianF(float delta_time_s);
  void updateCovariance(Eigen::Matrix<float,6,2>& gain_matrix,Eigen::Matrix<float,6,6>& predict_P);
  void updateState(Eigen::Matrix<float,6,1>& new_state);
  Eigen::Matrix<float,6,6> predictCovariance();
  Eigen::Matrix<float,6,2> calculateGainMatrix(Eigen::Matrix<float,6,6>& predict_P);
  Eigen::Matrix<float,6,1> ankerEkfFusion(AnkerDataType& cur_data,float delta_time_s);
  ekf_state state;
  ekf_matrix matrix;
  ekf_motionNoise motion_noise;
  ekf_measurementNoise measue_noise;

};

#endif // ANKEREKFESTIMATOR_H
