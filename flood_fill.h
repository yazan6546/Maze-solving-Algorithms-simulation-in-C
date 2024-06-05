#ifndef OK_ALGORITHM_H
#define OK_ALGORITHM_H

#include "Robot.h"
#include "Stack.h"

void flood_fill(int x, int y, int xprev, int yprev, int flood[16][16], int maze[16][16]);
void update_maze(struct Robot* robot, int maze[16][16], int flood[16][16]);
void show_flood(int flood[16][16]);
void delete_array(int **array);
void updateWalls(struct Robot *robot,int cells[16][16]);
int ** get_surrounds(int x, int y);
bool is_consistent(int x, int y, int flood[16][16], int maze[16][16]);
bool make_consistent(int x, int y, int flood[16][16], int maze[16][16]);
bool is_accessible(int x, int y, int x1, int y1, int maze[16][16]);
char tomove(struct Robot *robot, int maze[16][16],int flood[16][16]);

#endif //OK_ALGORITHM_H
