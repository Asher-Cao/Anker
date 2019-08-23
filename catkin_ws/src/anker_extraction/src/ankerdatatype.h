#ifndef ANKERDATATYPE_H
#define ANKERDATATYPE_H

struct AnkerData
{
    double time;
    double gx;
    double gy;
    double gz;
    double ax;
    double ay;
    double az;
    double odo_right_pos;
    double odo_left_pos;
    double odo_right_vel;
    double odo_left_vel;
    double opt_pos_x;
    double opt_pos_y;
    unsigned short int opt_quality;
    unsigned short int wall_distance_right;
    unsigned short int wall_distance_left;
};

#endif // ANKERDATATYPE_H
