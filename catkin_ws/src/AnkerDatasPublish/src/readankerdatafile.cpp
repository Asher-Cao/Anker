#include "readankerdatafile.h"

ReadAnkerDataFile::ReadAnkerDataFile(const string& imu_file,const string& odometry_file,const string& optical_file)
{
  ifstream imu_fin;
  imu_fin.open(imu_file.c_str());
  if(!imu_fin)
  {
    ROS_ERROR("File %s doesn't exist!",imu_file.c_str());
  }
  ifstream odo_fin(odometry_file.c_str());
  if(!odo_fin)
  {
    ROS_ERROR("File %s doesn't exist!",odometry_file.c_str());
  }
  ifstream opt_fin(optical_file.c_str());
  if(!opt_fin)
  {
    ROS_ERROR("File %s doesn't exist!",optical_file.c_str());
  }

  string str_skip;
  getline(imu_fin, str_skip);
  ROS_INFO("IMU First Line : %s", str_skip.c_str());
  str_skip.clear();
  getline(odo_fin, str_skip);
  ROS_INFO("Odometry First Line : %s", str_skip.c_str());
  str_skip.clear();
  getline(opt_fin, str_skip);
  ROS_INFO("Optical First Line : %s", str_skip.c_str());

  while(!imu_fin.eof())
  {
    double t_imu,t_odo,t_opt;
    imu_fin >> t_imu;
    odo_fin >> t_odo;
    opt_fin >> t_opt;
    if(fabs(t_imu - t_odo) > 0.011f)
      continue;
    if(fabs(t_imu - t_opt) > 0.011f)
      continue;
    AnkerData raw_data;
    raw_data.time = t_imu;
    imu_fin >> raw_data.ax;
    imu_fin >> raw_data.ay;
    imu_fin >> raw_data.az;
    imu_fin >> raw_data.gx;
    imu_fin >> raw_data.gy;
    imu_fin >> raw_data.gz;

    odo_fin >> raw_data.odo_right_pos;
    odo_fin >> raw_data.odo_left_pos;
    odo_fin >> raw_data.odo_right_vel;
    odo_fin >> raw_data.odo_left_vel;

    opt_fin >> raw_data.opt_pos_x;
    opt_fin >> raw_data.opt_pos_y;
    opt_fin >> raw_data.wall_distance_right;
    opt_fin >> raw_data.wall_distance_left;
    opt_fin >> raw_data.opt_quality;

    AnkerDataSet.push_back(raw_data);
  }


}
