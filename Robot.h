#ifndef OK_ROBOT_H
#define OK_ROBOT_H

#include "API.h"
#include "stdbool.h"
#include <limits.h>

typedef enum Orientation {NORTH, EAST, SOUTH, WEST} Orientation;

struct Robot {

    bool L,R,F;
    short prevCoordinates[2];
    short coordinates[2];
    Orientation orientation;
};

struct Robot* create_robot(short* initial_point);
void move_forward(struct Robot *robot);
void turn_right(struct Robot *robot);
void turn_left(struct Robot *robot);
void show_walls(struct Robot* robot);
void print_array (int p[16][16], int len, int len2);
#endif //OK_ROBOT_H