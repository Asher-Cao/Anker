#include "readankerdatafile.h"

ReadAnkerDataFile::ReadAnkerDataFile(const string& imu_file,const string& odometry_file,const string& optical_file)
{
    ifstream imu_fin;
    imu_fin.open(imu_file.c_str());
    if(!imu_fin){std::cout << "File " << imu_file << "doesnot exit!" << std::endl;}
    ifstream odo_fin(odometry_file.c_str());
    if(!odo_fin){std::cout << "File " << odometry_file << "doesnot exit!" << std::endl;}
    ifstream opt_fin(optical_file.c_str());
    if(!opt_fin){std::cout << "File " << optical_file << "doesnot exit!" << std::endl;}
    string str_skip;
    getline(imu_fin, str_skip);
    std::cout << "IMU First Line : " << str_skip << std::endl;
    str_skip.clear();
    getline(odo_fin, str_skip);
    std::cout << "Odometry First Line : " << str_skip << std::endl;
    str_skip.clear();
    getline(opt_fin, str_skip);
    std::cout << "Optical First Line : " << str_skip << std::endl;
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
