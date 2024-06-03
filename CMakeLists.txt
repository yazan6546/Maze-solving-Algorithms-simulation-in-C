cmake_minimum_required(VERSION 3.26)
project(ok C)

set(CMAKE_C_STANDARD 11)

add_executable(ok Main.c
        API.c
        Robot.h
        Robot.c
        Algorithm.c
        Algorithm.h)
