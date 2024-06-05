#include <stdio.h>
#include "Robot.h"

void update_maze(struct Robot* robot);
void log(char* text);

int main(int argc, char* argv[]) {

    log("Running...");
    API_setColor(7, 7, 'B');
    API_setText(0, 0, "START");
    API_setText(7, 7, "FINISH");
    API_setColor(7, 7, 'B');

    struct Robot *robot = create_robot((short[]) {0, 0});
    while (1) {

        robot->L = API_wallLeft();
        robot->R = API_wallRight();
        robot->F = API_wallFront();

        update_maze(robot);


        // turn to the right whenever you can
        if (!API_wallRight()) {
            turn_right(robot);
        }

        // perform a U-turn if there is wall in the front, or turn left if you cannot turn right
        while (API_wallFront()) {
            turn_left(robot);
        }

        // move forward if none applies
        move_forward(robot);
    }

}



void update_maze(struct Robot* robot) {
    API_setColor(robot->coordinates[0], robot->coordinates[1], 'G');
    show_walls(robot);
}

void log(char* text) {
    fprintf(stderr, "%s\n", text);
    fflush(stderr);
}

