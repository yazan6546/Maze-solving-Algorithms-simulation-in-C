cmake_minimum_required(VERSION 3.26)
project(ok C)

set(CMAKE_C_STANDARD 11)

add_executable(flood_fill
        API.c
        Robot.c
        flood_fill.c
        Stack.c
        Flood_fill_driver.c
)

add_executable(right_turn
        right_turn_driver.c
        API.c
        Robot.c
)