#ifndef IMU_H
#define IMU_H
#include <Eigen/Core>
#include "ankerinfomation.h"
#include <ros/ros.h>

class IMU
{

public:
  IMU();
  struct IMUParameters
  {
    Eigen::Vector3d Acc_Scalar;
    Eigen::Vector3d Acc_Bias;
    Eigen::Vector3d Gyro_Bias;
    double tilt_angle;
  };
  bool calibrationGyroBias(AnkerDataType& data);
  bool imuAlignWithAnkerBody(AnkerDataType& data);
  bool calibrationAccScalarAndBias(AnkerDataType& data);
  const Eigen::Vector3d getAccScalar(){return paras.Acc_Scalar;}
  const Eigen::Vector3d getAccBias(){return paras.Acc_Bias;}
  const Eigen::Vector3d getGyroBias(){return paras.Gyro_Bias;}
  double getTiltAngle(){return paras.tilt_angle;}
private:
  IMUParameters paras;
};

#endif // IMU_H
