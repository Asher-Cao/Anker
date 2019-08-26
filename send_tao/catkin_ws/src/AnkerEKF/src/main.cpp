#include <iostream>


#include "anker.h"
using namespace std;


int main(int argc,char ** argv)
{
  ros::init(argc, argv, "anker_ekf_node");
  ROS_INFO("AnkerEkf Node Working Now!");
  Anker anker("anker");
  ros::spin();
  return 0;
}
