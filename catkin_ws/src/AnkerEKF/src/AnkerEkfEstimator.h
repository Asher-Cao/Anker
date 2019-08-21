#ifndef ANKEREKFESTIMATOR_H
#define ANKEREKFESTIMATOR_H
#include "ankerekfdefine.h"
#include "ankerinfomation.h"
class AnkerEkfEstimator
{
public:

  AnkerEkfEstimator(ekf_state _state,ekf_motionNoise _motion_noise,ekf_measurementNoise _measure_noise);
  void updateJacbianF(float delta_time_s);
  void updateMatrixG(float delta_time_s);
  void updateState(Eigen::Matrix<float,6,1>& new_state);
  Eigen::Matrix<float,6,6> predictCovariance();
  Eigen::Matrix<float,6,4> calculateGainMatrix(Eigen::Matrix<float,6,6>& predict_P);

  ekf_state state;
  ekf_matrix matrix;
  ekf_motionNoise motion_noise;
  ekf_measurementNoise measue_noise;

};

#endif // ANKEREKFESTIMATOR_H
