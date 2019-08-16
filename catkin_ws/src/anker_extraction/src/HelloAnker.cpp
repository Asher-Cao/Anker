#include "iostream"
#include "readankerdatafile.h"
int main()
{
  std::cout << "Hello Anker!" << std::endl;
  std::string imu_file = "/home/kdq/Workspace/Anker/anker_kdq_tools/ankerdata_30m_trival/imu_file.cvs";
  std::string odo_file = "/home/kdq/Workspace/Anker/anker_kdq_tools/ankerdata_30m_trival/odometer_file.cvs";
  std::string opt_file = "/home/kdq/Workspace/Anker/anker_kdq_tools/ankerdata_30m_trival/optical_flow_file.cvs";
  ReadAnkerDataFile AnkerDatas(imu_file,odo_file,opt_file);

  for(int it= 0;it < AnkerDatas.AnkerDataSet.size();it++)
  {
    AnkerData data = AnkerDatas.AnkerDataSet[it];
    std::cout << "time: " << data.time << " " << data.ax  << " " << data.ay  << " " << data.az
                 << " " << data.gx << " " << data.gy  << " " << data.gz  << " " << data.odo_right_pos
                    << " " << data.odo_left_pos  << " " << data.odo_right_vel  << " " << data.odo_left_vel
                    << " " << data.opt_pos_x << " " << data.opt_pos_y <<" " << data.opt_quality <<" " <<data.wall_distance_left
                    <<" " << data.wall_distance_right << endl;

  }

}
