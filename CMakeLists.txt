cmake_minimum_required(VERSION 3.21)
project(El_classico_experience C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(El_classico_experience
        main.c
        globals.h spectator.c spectator.h group.c group.h goal.c goal.h wrapper.c wrapper.h)
