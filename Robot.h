#ifndef OK_ROBOT_H
#define OK_ROBOT_H

#include "API.h"
#include "stdbool.h"
#include <limits.h>

typedef enum Orientation {NORTH, EAST, SOUTH, WEST} Orientation;

struct Robot {

    bool L,R,F;
    short coordinates[2];
    Orientation orientation;
};

struct Robot* create_robot(short* initial_point);
void move_forward(struct Robot *robot);
void turn_right(struct Robot *robot);
void turn_left(struct Robot *robot);
void delete_array(short **array);
void updateWalls(struct Robot *robot,int cells[16][16]);
bool is_consistent(struct Robot* robot, int **flood, int** maze);
bool is_accessible(struct Robot *robot, int x1, int y1, int **maze);

#endif //OK_ROBOT_H
