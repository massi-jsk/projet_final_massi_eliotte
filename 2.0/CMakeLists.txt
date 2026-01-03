cmake_minimum_required(VERSION 4.1)
project(2_0 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(2_0
        algo_hash.c
        algo_hash.h
        algo_liste.c
        algo_liste.h
        algo_tableau.c
        algo_tableau.h
        gereMem.c
        gererMem.h
        main.c
        structures.h
        utils.c
        utils.h)
