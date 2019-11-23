cmake_minimum_required(VERSION 3.12)
project(dominion C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(dominion
        dominion.c
        dominion.h
        dominion_helpers.h
        interface.c
        interface.h
        playdom.c
        player.c
        rngs.c
        rngs.h
        rt.c
        testdrawcard.c)
