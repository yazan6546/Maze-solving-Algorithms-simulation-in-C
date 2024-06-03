#include "Robot.h"

struct Robot* create_robot(short* initial_point) {
    struct Robot *robot = malloc(sizeof(struct Robot));
    robot->orientation = NORTH;
    robot->coordinates[0] = initial_point[0];
    robot->coordinates[1] = initial_point[1];

    return robot;
}


void move_forward(struct Robot *robot) {

    API_moveForward();

    fprintf(stderr,"%d\n", !API_wallFront());
    fflush(stderr);
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

// return an array of all the coordinates that surround the current
//North, East, South, West
int ** get_surrounds(struct Robot *robot) {
    int **array = malloc(4 * sizeof(int *));

    for (int i = 0; i<4; i++) {
        int *temp = malloc(2 * sizeof(int));
        array[i] = temp;
    }

    array[0][0] = robot->coordinates[0];
    array[0][1] = robot->coordinates[1] + 1;

    array[1][0] = robot->coordinates[0] + 1;
    array[1][1] = robot->coordinates[1];

    array[2][0] = robot->coordinates[0];
    array[2][1] = robot->coordinates[1] - 1;

    array[3][0] = robot->coordinates[0] - 1;
    array[3][1] = robot->coordinates[1];

    if (array[1][0] >= 16) {
        array[1][0] = -1;
    }

    if (array[0][1] >= 16) {
        array[0][1] = -1;
    }

    return array;
}


// returns true if the mouse can move from (x, y) to (x1, y1)
bool is_accessible(struct Robot *robot, int x1, int y1, int maze[16][16]) {

    int x = robot->coordinates[0];
    int y = robot->coordinates[1];

    if (x == x1) {
        if (y > y1) {
            if (maze[x][y] == 4 || maze[x][y] == 5 || maze[x][y] == 6 ||
                maze[x][y] == 10 || maze[x][y] == 11 ||
                    maze[x][y] == 12 || maze[x][y] == 14) {

                return false;
            }

            else {
                return true;
            }
        }

        else {

            if (maze[x][y] == 2 || maze[x][y] == 7 ||
                    maze[x][y] == 8 || maze[x][y] == 10 ||
                    maze[x][y] == 12 || maze[x][y] == 13 ||
                    maze[x][y] == 14) {
                return false;
            }
            else {
                return true;
            }

        }
    }

    else if (y == y1) {
        if (x > x1) {
            if (maze[y][x] == 1 || maze[y][x] == 5 || maze[y][x] == 8 ||
                    maze[y][x] == 9 || maze[y][x] == 11 ||
                    maze[y][x] == 13 || maze[y][x] == 14) {

                return false;
            }

            else {
                return true;
            }
        }

        else {

            if (maze[x][y] == 3 || maze[x][y] == 6 ||
                    maze[x][y] == 7 || maze[x][y] == 9 ||
                    maze[x][y] == 11 || maze[x][y] == 12 ||
                    maze[x][y] == 13) {
                return false;
            }
            else {
                return true;
            }

        }
    }

    return false;
}


bool is_consistent(struct Robot* robot, int flood[16][16], int maze[16][16]) {

    int x = robot->coordinates[0];
    int y = robot->coordinates[1];

    int **coordinates = get_surrounds(robot);
    int val = flood[x][y];

    for (int i = 0; i<4 ; i++) {

        int x_i = coordinates[i][0];
        int y_i = coordinates[i][1];
        if (x_i >= 0 && y_i >= 0 && is_accessible(robot, x_i, y_i, maze)
            && flood[x_i][y_i] == val - 1) {

            delete_array(coordinates);
            return true;

        }
    }

    delete_array(coordinates);
    return false;
}

bool make_consistent(struct Robot* robot, int flood[16][16], int maze[16][16]) {

    int x = robot->coordinates[0];
    int y = robot->coordinates[1];

    int **coordinates = get_surrounds(robot);
    int val = flood[x][y];
    int min_vals[] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};

    for (int i = 0; i<4 ; i++) {

        int x_i = coordinates[i][0];
        int y_i = coordinates[i][1];
        if (x_i >= 0 && y_i >= 0 && is_accessible(robot, x_i, y_i, maze)) {

            min_vals[i] = flood[x_i][y_i];
        }
    }

    int min = min_vals[0];

    for (int i = 1;i<4;i++) {
        if (min_vals[i] < min) {
            min = min_vals[i];
        }
    }

    flood[x][y] = min + 1;
    delete_array(coordinates);
    return false;
}





void delete_array(int **array) {

    for (int i = 0; i<4;i++) {
        free(array[i]);
    }

    free(array);
}


void updateWalls(struct Robot *robot,int cells[16][16]) {
    if (robot->L && robot->R && robot->F) {
        if (robot->orientation == NORTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 13;

        else if (robot->orientation == EAST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 12;

        else if (robot->orientation == SOUTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 11;
        else if (robot->orientation == WEST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 14;

    } else if (robot->L && robot->R && !(robot->F)) {
        if (robot->orientation == NORTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 9;

        else if (robot->orientation == SOUTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 9;

        else if (robot->orientation == EAST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 10;

        else if (robot->orientation == WEST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 10;
    } else if (robot->L && robot->F && !(robot->R)) {
        if (robot->orientation == NORTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 8;

        else if (robot->orientation == EAST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 7;

        else if (robot->orientation == SOUTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 6;


        else if (robot->orientation == WEST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 5;

    } else if (robot->R && robot->F && !(robot->L)) {
        if (robot->orientation == NORTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 7;

        else if (robot->orientation == EAST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 6;


        else if (robot->orientation == SOUTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 5;

        else if (robot->orientation == WEST) {
            cells[robot->coordinates[0]][robot->coordinates[1]] = 8;


        }

    } else if (robot->F) {
        if (robot->orientation == NORTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 2;
        else if (robot->orientation == EAST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 3;
        else if (robot->orientation == SOUTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 4;
        else if (robot->orientation == WEST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 1;
    } else if (robot->L) {
        if (robot->orientation == NORTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 1;
        else if (robot->orientation == EAST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 2;
        else if (robot->orientation == SOUTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 3;
        else if (robot->orientation == WEST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 4;
    } else if (robot->R) {
        if (robot->orientation == NORTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 3;
        else if (robot->orientation == EAST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 4;
        else if (robot->orientation == SOUTH)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 1;
        else if (robot->orientation == WEST)
            cells[robot->coordinates[0]][robot->coordinates[1]] = 2;
    }

}



char tomove(struct Robot *robot,int maze[16][16],int flood[16][16]) {

    fprintf(stderr, "tessssssssssst tomove");
    fflush(stderr);
    int **surraounds;
    surraounds = get_surrounds(robot);
    print_array(surraounds, 4);

    fprintf(stderr, "prev : %d %d\n", robot->prevCoordinates[0], robot->prevCoordinates[1]);
    fflush(stderr);


    int prev = 0;
    int minVals[] = {1000, 1000, 1000, 1000};
    if (is_accessible(robot, surraounds[0][0], surraounds[0][1], maze)) {
        if (surraounds[0][0] == robot->prevCoordinates[0] &&
            surraounds[0][0] == robot->prevCoordinates[1]) {
            prev = 0;
        }
        minVals[0]=flood[surraounds[0][0]][surraounds[0][1]];
    }

    if (is_accessible(robot,surraounds[1][0],surraounds[1][1],maze)) {
        if(surraounds[1][0]==robot->prevCoordinates[0]&&
           surraounds[1][1]==robot->prevCoordinates[1]) {
            prev=1;
        }
        minVals[1]=flood[surraounds[1][0]][surraounds[1][1]];
    }
    if (is_accessible(robot,surraounds[2][0],surraounds[2][1],maze)) {
        if(surraounds[2][0]==robot->prevCoordinates[0]&&
           surraounds[2][1]==robot->prevCoordinates[1]) {
            prev=2;
        }
        minVals[2]=flood[surraounds[2][0]][surraounds[2][1]];
    }
    if (is_accessible(robot,surraounds[3][0],surraounds[3][1],maze)) {
        if(surraounds[3][0]==robot->prevCoordinates[0]&&
           surraounds[3][1]==robot->prevCoordinates[1]) {
            prev=3;
        }
        minVals[3]=flood[surraounds[3][0]][surraounds[3][1]];
    }

    int minVal=minVals[0];
    int minCell=0;
    int noMovements=0;
    for(int i=0;i<4;i++) {
        if(minVals[i]!=1000)
            noMovements+=1;

    }
    for(int i=0;i<4;i++) {
        if(i==prev)
            continue;

        if(minVals[i]<minVal) {
            minVal=minVals[i];
            minCell=i;
        }

    }

    if (minCell==robot->orientation)
        return 'F';
    else if((minCell==robot->orientation-1) || (minCell== robot->orientation+3))
        return('L');
    else if ((minCell==robot->orientation+1) || (minCell== robot->orientation-3))
        return('R');
    else
        return('B');

}


void print_array (int **p, int len) {
    for (int i = 0; i<len; i++) {

        fprintf(stderr, "\n(");
        fflush(stderr);
        for (int j = 0; j < 2; j++) {
            fprintf(stderr, "%d ", p[i][j]);
            fflush(stderr);
        }


        fprintf(stderr, ")");
        fflush(stderr);

    }
}