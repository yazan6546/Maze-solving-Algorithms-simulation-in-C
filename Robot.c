#include "Robot.h"

struct Robot* create_robot(short* initial_point) {
    struct Robot *robot = malloc(sizeof(struct Robot));
    robot->orientation = NORTH;
    robot->coordinates[0] = initial_point[0];
    robot->coordinates[1] = initial_point[1];
    robot->prevCoordinates[0] = 0;
    robot->prevCoordinates[1] = 0;
    robot->L = API_wallLeft();
    robot->R = API_wallRight();
    robot->F = API_wallFront();

    return robot;
}


void move_forward(struct Robot *robot) {

    API_moveForward();
    switch (robot->orientation) {
        case 0: {
            robot->prevCoordinates[0]=robot->coordinates[0];
            robot->prevCoordinates[1]=robot->coordinates[1];
            robot->coordinates[1]++;

            break;
        }
        case 1: {
            robot->prevCoordinates[0]=robot->coordinates[0];
            robot->prevCoordinates[1]=robot->coordinates[1];
            robot->coordinates[0]++;
            break;
        }

        case 2: {
            robot->prevCoordinates[0]=robot->coordinates[0];
            robot->prevCoordinates[1]=robot->coordinates[1];
            robot->coordinates[1]--;
            break;
        }

        case 3: {
            robot->prevCoordinates[0]=robot->coordinates[0];
            robot->prevCoordinates[1]=robot->coordinates[1];
            robot->coordinates[0]--;
            break;
        }
    }

}

void turn_left(struct Robot *robot) {

    API_turnLeft();
    switch (robot->orientation) {
        case NORTH: robot->orientation = WEST;
            break;
        case EAST: robot->orientation = NORTH;
            break;
        case SOUTH: robot->orientation = EAST;
            break;
        case WEST: robot->orientation = SOUTH;
            break;
    }
}

void turn_right(struct Robot *robot) {

    API_turnRight();
    switch (robot->orientation) {
        case NORTH: robot->orientation = EAST;
            break;
        case EAST: robot->orientation = SOUTH;
            break;
        case SOUTH: robot->orientation = WEST;
            break;
        case WEST: robot->orientation = NORTH;
            break;
    }
}


void print_array (int p[][16], int len, int len2) {
    for (int i = 0; i<len; i++) {

        fprintf(stderr, "\n(");
        fflush(stderr);
        for (int j = 0; j < len2; j++) {
            fprintf(stderr, "%d, ", p[i][j]);
            fflush(stderr);
        }


        fprintf(stderr, ")");
        fflush(stderr);

    }
}


void show_walls(struct Robot* robot) {
    int x, y;
    x = robot->coordinates[0];
    y = robot->coordinates[1];

    if (robot->F) {

        switch (robot->orientation) {
            case NORTH : API_setWall(x, y, 'n');
                break;
            case EAST : API_setWall(x, y, 'e');
                break;
            case SOUTH :API_setWall(x, y, 's');
                break;
            case WEST :API_setWall(x, y, 'w');
                break;
        }
    }

    if (robot->R) {
        switch (robot->orientation) {
            case NORTH : API_setWall(x, y, 'e');
                break;
            case EAST : API_setWall(x, y, 's');
                break;
            case SOUTH :API_setWall(x, y, 'w');
                break;
            case WEST :API_setWall(x, y, 'n');
                break;
        }
    }

    if (robot->L) {
        switch (robot->orientation) {
            case NORTH : API_setWall(x, y, 'w');
                break;
            case EAST : API_setWall(x, y, 'n');
                break;
            case SOUTH :API_setWall(x, y, 'e');
                break;
            case WEST :API_setWall(x, y, 's');
                break;
        }
    }
}

