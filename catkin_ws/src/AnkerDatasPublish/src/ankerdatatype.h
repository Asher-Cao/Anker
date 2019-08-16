#ifndef ANKERDATATYPE_H
#define ANKERDATATYPE_H

struct AnkerData
{
    float time;
    float gx;
    float gy;
    float gz;
    float ax;
    float ay;
    float az;
    float odo_right_pos;
    float odo_left_pos;
    float odo_right_vel;
    float odo_left_vel;
    float opt_pos_x;
    float opt_pos_y;
    unsigned short int opt_quality;
    unsigned short int wall_distance_right;
    unsigned short int wall_distance_left;
};

#endif // ANKERDATATYPE_H
