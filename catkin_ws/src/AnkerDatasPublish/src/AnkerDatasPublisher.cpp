#include <iostream>
#include <ros/ros.h>
#include <readankerdatafile.h>
#include <anker_data_publish/AnkerDataType.h>
using namespace std;

void extractAnkerData( anker_data_publish::AnkerDataType& anker_publish_data,AnkerData& anker_data)
{
  anker_publish_data.time_s = anker_data.time;
  anker_publish_data.gx = anker_data.gx;
  anker_publish_data.gy = anker_data.gy;
  anker_publish_data.gz = anker_data.gz;
  anker_publish_data.ax = anker_data.ax;
  anker_publish_data.ay = anker_data.ay;
  anker_publish_data.az = anker_data.az;
  anker_publish_data.odo_left_pos = anker_data.odo_left_pos;
  anker_publish_data.odo_right_pos = anker_data.odo_right_pos;
  anker_publish_data.odo_left_vel = anker_data.odo_left_vel;
  anker_publish_data.odo_right_vel = anker_data.odo_right_vel;
  anker_publish_data.opt_pos_x = anker_data.opt_pos_x;
  anker_publish_data.opt_pos_y = anker_data.opt_pos_y;
  anker_publish_data.opt_quality = anker_data.opt_quality;
  anker_publish_data.wall_distance_left = anker_data.wall_distance_left;
  anker_publish_data.wall_distance_right = anker_data.wall_distance_right;

}

int main(int argc,char** argv)
{
  ros::init(argc,argv,"anker_data_publisher_node");
  ros::NodeHandle n("~");
  ROS_INFO("AnkerDatasPublish Node Begin!");
  ros::Publisher ankerpublisher = n.advertise<anker_data_publish::AnkerDataType>("/anker_data_topic",10);

  //std::string file_path = "/home/kdq/Workspace/Anker/cvs_datas/201908261435/";
  //std::string file_path = "/home/kdq/Workspace/Anker/cvs_datas/201908261145/";
  std::string file_path = "/home/kdq/Workspace/Anker/cvs_datas/201908231925/";
 // std::string file_path = "/home/kdq/Workspace/Anker/cvs_datas/201908212215/";
  //std::string file_path = "/home/kdq/Workspace/Anker/cvs_datas/201908191207/";
  //std::string file_path = "/home/kdq/Workspace/Anker/cvs_datas/ankerdata_30m_trival/";
  std::string imu_file = file_path +  "imu_file.cvs";
  std::string odo_file = file_path + "odometer_file.cvs";
  std::string opt_file = file_path + "optical_flow_file.cvs";
  ROS_INFO("Datas come from file %s..",file_path.c_str());
  //double time_begin=1300.0f; // 231925
  //double time_begin = 70.0f;//30m_trival
  // double time_begin = 0.0f; // 212215 //261145
  //double time_over = 3300.0f; //261145
  double time_begin = 1300.0f; //231925
   double time_over = 4000.0f; //261435 //231925
  ReadAnkerDataFile AnkerDatas(imu_file,odo_file,opt_file);
  int num = AnkerDatas.AnkerDataSet.size();
  if(num ==0)
  {
    ROS_ERROR("There are no data in Anker Data file!!!");
    ros::shutdown();
    return 0;
  }
  int i;//ankerdata_30m_trival
  for(i=0;i < num ;i++)
    if(AnkerDatas.AnkerDataSet[i].time > time_begin)
      break;

  int j;
  for(j=i;j<num;j++)
   if(AnkerDatas.AnkerDataSet[j].time > time_over)
      break;

  ros::Rate loop_rate(1000);
  while(ros::ok() && i<j)
  {
    i++;
    anker_data_publish::AnkerDataType raw_data;
    extractAnkerData(raw_data,AnkerDatas.AnkerDataSet[i]);

    ankerpublisher.publish(raw_data);
    loop_rate.sleep();
  }

  ros::shutdown();
  return 0;
}
