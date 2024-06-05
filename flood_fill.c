#include "flood_fill.h"

void flood_fill(int x, int y, int xprev, int yprev, int flood[16][16], int maze[16][16]) {

    bool visited[16][16];

    if (!is_consistent(x, y, flood, maze)) {
        flood[x][y] = flood[xprev][yprev] + 1;
    }

    Node* stack = createStack();
    push(stack, x, y);
    visited[x][y] = true;

    int** surrounds = get_surrounds(x, y);
    for (int i = 0; i < 4; i++) {
        int x_i = surrounds[i][0];
        int y_i = surrounds[i][1];

        if (x_i >= 0 && y_i >= 0 && !visited[x_i][y_i] && is_accessible(x, y, x_i, y_i, maze)) {
            push(stack, x_i, y_i);
            visited[x_i][y_i] = true;
        }
    }
    delete_array(surrounds);

    while (!empty(stack)) {
        int* temp = pop(stack);
        int xrun = temp[0];
        int yrun = temp[1];
        free(temp);

        if (!is_consistent(xrun, yrun, flood, maze)) {
            make_consistent(xrun, yrun, flood, maze);

            surrounds = get_surrounds(xrun, yrun);
            for (int i = 0; i < 4; i++) {
                int x_i = surrounds[i][0];
                int y_i = surrounds[i][1];

                if (x_i >= 0 && y_i >= 0 && !visited[x_i][y_i] && is_accessible(xrun, yrun, x_i, y_i, maze)) {
                    push(stack, x_i, y_i);
                    visited[x_i][y_i] = true;
                }
            }
            delete_array(surrounds);
        }
    }

    deleteStack(stack);
}

void update_maze(struct Robot* robot, int maze[16][16], int flood[16][16]) {
    show_flood(flood);
    API_setColor(robot->coordinates[0], robot->coordinates[1], 'G');
    show_walls(robot);
}

void show_flood(int flood[16][16]) {

    for (int i = 0; i<16; i++) {
        for (int j = 0;j<16; j++) {
            char str[3];
            sprintf(str, "%d", flood[i][j]);
            API_setText(i, j, str);
        }
    }
}


// return an array of all the coordinates that surround the current
//North, East, South, West
int ** get_surrounds(int x, int y) {
    int **array = malloc(4 * sizeof(int *));

    for (int i = 0; i<4; i++) {
        int *temp = malloc(2 * sizeof(int));
        array[i] = temp;
    }

    array[0][0] = x;
    array[0][1] = y + 1;

    array[1][0] = x + 1;
    array[1][1] = y;

    array[2][0] = x;
    array[2][1] = y - 1;

    array[3][0] = x - 1;
    array[3][1] = y;

    if (array[1][0] >= 16) {
        array[1][0] = -1;
    }

    if (array[0][1] >= 16) {
        array[0][1] = -1;
    }

    return array;
}


// returns true if the mouse can move from (x, y) to (x1, y1)
bool is_accessible(int x, int y, int x1, int y1, int maze[16][16]) {


    if (x1 < 0 || y1 < 0 || x1 > 15 || y1 > 15) {
        return false;
    }


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
            if (maze[x][y] == 1 || maze[x][y] == 5 || maze[x][y] == 8 ||
                maze[x][y] == 9 || maze[x][y] == 11 ||
                maze[x][y] == 13 || maze[x][y] == 14) {

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


bool is_consistent(int x, int y, int flood[16][16], int maze[16][16]) {

    int **coordinates = get_surrounds(x, y);
    int val = flood[x][y];

    if (val == 0) {
        return true;
    }
    for (int i = 0; i<4 ; i++) {

        int x_i = coordinates[i][0];
        int y_i = coordinates[i][1];
        if (x_i >= 0 && y_i >= 0 && is_accessible(x, y, x_i, y_i, maze)
            && flood[x_i][y_i] == val - 1) {

            delete_array(coordinates);
            return true;

        }
    }

    delete_array(coordinates);
    return false;
}

bool make_consistent(int x, int y, int flood[16][16], int maze[16][16]) {

    int **coordinates = get_surrounds(x, y);
    int val = flood[x][y];
    int min_vals[] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};

    for (int i = 0; i<4 ; i++) {

        int x_i = coordinates[i][0];
        int y_i = coordinates[i][1];
        if (x_i >= 0 && y_i >= 0 && is_accessible(x, y, x_i, y_i, maze)) {

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


void updateWalls(struct Robot *robot, int cells[16][16]) {


    fprintf(stderr, "\n(%d, %d)\n", robot->coordinates[0], robot->coordinates[1]);
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

    int **surraounds;
    int x = robot->coordinates[0];
    int y = robot->coordinates[1];
    surraounds = get_surrounds(robot->coordinates[0], robot->coordinates[1]);

    int prev = 0;
    int minVals[] = {1000, 1000, 1000, 1000};
    if (is_accessible(x, y, surraounds[0][0], surraounds[0][1], maze)) {
        if (surraounds[0][0] == robot->prevCoordinates[0] &&
            surraounds[0][0] == robot->prevCoordinates[1]) {
            prev = 0;
        }
        minVals[0]=flood[surraounds[0][0]][surraounds[0][1]];
    }

    if (is_accessible(x, y,surraounds[1][0],surraounds[1][1],maze)) {
        if(surraounds[1][0]==robot->prevCoordinates[0]&&
           surraounds[1][1]==robot->prevCoordinates[1]) {
            prev=1;
        }
        minVals[1]=flood[surraounds[1][0]][surraounds[1][1]];
    }
    if (is_accessible(x, y,surraounds[2][0],surraounds[2][1],maze)) {
        if(surraounds[2][0]==robot->prevCoordinates[0]&&
           surraounds[2][1]==robot->prevCoordinates[1]) {
            prev=2;
        }
        minVals[2]=flood[surraounds[2][0]][surraounds[2][1]];
    }
    if (is_accessible(x, y,surraounds[3][0],surraounds[3][1],maze)) {
        if(surraounds[3][0]==robot->prevCoordinates[0]&&
           surraounds[3][1]==robot->prevCoordinates[1]) {
            prev=3;
        }
        minVals[3]=flood[surraounds[3][0]][surraounds[3][1]];
    }

    delete_array(surraounds);

    int minVal=minVals[0];
    int minCell=0;
    int noMovements=0;
    for(int i=0;i<4;i++) {
        if(minVals[i]!=1000)
            noMovements+=1;

    }
    for(int i=0;i<4;i++) {
        if(minVals[i]<minVal) {

            if (noMovements == 1 || i != prev) {
                minVal = minVals[i];
                minCell = i;
            }
        }

    }

    if (minCell==robot->orientation)
        return 'F';
    else if((minCell==robot->orientation-1) || (minCell== (robot->orientation+3) % 4))
        return('L');
    else if ((minCell==(robot->orientation+1)) || (minCell== (robot->orientation-3) % 4))
        return('R');
    else
        return('B');

}


