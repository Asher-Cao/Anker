#ifndef READANKERDATAFILE_H
#define READANKERDATAFILE_H
#include "ankerdatatype.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <ros/ros.h>
using namespace std;

class ReadAnkerDataFile
{
public:
    ReadAnkerDataFile(const string& imu_file,const string& odometry_file,const string& optical_file);
    vector<AnkerData> AnkerDataSet;

};

#endif // READANKERDATAFILE_H
