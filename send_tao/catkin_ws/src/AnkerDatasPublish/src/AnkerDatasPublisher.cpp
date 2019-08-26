#include <iostream>
#include <ros/ros.h>
#include <readankerdatafile.h>
#include <anker_data_publish/AnkerDataType.h>
using namespace std;

int main(int argc,char** argv)
{
  ros::init(argc,argv,"anker_data_publisher_node");
  ros::NodeHandle n("~");
  ROS_INFO("AnkerDatasPublish Node Begin!");
  ros::Publisher ankerpublisher = n.advertise<anker_data_publish::AnkerDataType>("/anker_data_topic",10);

  //std::string file_path = "/home/kdq/Workspace/Anker/cvs_datas/201908191207/";
  std::string file_path = "/home/kdq/Workspace/Anker/cvs_datas/ankerdata_30m_trival/";
  std::string imu_file = file_path +  "imu_file.cvs";
  std::string odo_file = file_path + "odometer_file.cvs";
  std::string opt_file = file_path + "optical_flow_file.cvs";
  ROS_INFO("Datas come from file %s..",file_path.c_str());

  ReadAnkerDataFile AnkerDatas(imu_file,odo_file,opt_file);
  int num = AnkerDatas.AnkerDataSet.size();
  if(num ==0)
  {
    ROS_ERROR("There are no data in Anker Data file!!!");
    ros::shutdown();
    return 0;
  }
  int i;
  for(i=0;i < num ;i++)
    if(AnkerDatas.AnkerDataSet[i].time > 90.0f)
      break;


  ros::Rate loop_rate(400);
  while(ros::ok() && i<num)
  {
    i++;
    anker_data_publish::AnkerDataType raw_data(AnkerDatas.AnkerDataSet[i]);

    ankerpublisher.publish(raw_data);
    loop_rate.sleep();
  }

  ros::shutdown();
  return 0;
}
