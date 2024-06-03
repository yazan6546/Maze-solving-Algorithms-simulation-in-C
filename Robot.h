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
void delete_array(int **array);
void updateWalls(struct Robot *robot,int cells[16][16]);
int ** get_surrounds(struct Robot *robot);
bool is_consistent(struct Robot* robot, int flood[16][16], int maze[16][16]);
bool is_accessible(struct Robot *robot, int x1, int y1, int maze[16][16]);
char tomove(struct Robot *robot,int maze[16][16],int flood[16][16]);
void print_array (int **p, int len);
#endif //OK_ROBOT_H