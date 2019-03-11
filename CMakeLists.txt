cmake_minimum_required(VERSION 3.13)
project(RL_for_Playing_Football)

set(CMAKE_CXX_STANDARD 14)

include_directories(bachelorProject)

add_executable(RL_for_Playing_Football
        bachelorProject/controller.cpp
        bachelorProject/controller.h
        bachelorProject/gridWorld.cpp
        bachelorProject/gridWorld.h
        bachelorProject/main.cpp
        bachelorProject/observable.cpp
        bachelorProject/observable.h
        bachelorProject/observer.h
        bachelorProject/player.cpp
        bachelorProject/player.h
        bachelorProject/team.cpp
        bachelorProject/team.h
        bachelorProject/view.cpp
        bachelorProject/view.h
        bachelorProject/world.cpp
        bachelorProject/world.h)
