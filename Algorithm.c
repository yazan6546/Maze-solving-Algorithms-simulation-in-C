//
// Created by yazan on 6/2/2024.
//

#include "Algorithm.h"


void flood_fill(struct Robot *robot, int xprev, int yprev, int **maze, int **flood) {
// Condition for checking out of bounds

    int x = robot->coordinates[0];
    int y = robot->coordinates[1];

    if (!is_consistent(robot, flood, maze)) {
        flood[x][y] = flood[xprev][yprev] + 1;
    }


}



