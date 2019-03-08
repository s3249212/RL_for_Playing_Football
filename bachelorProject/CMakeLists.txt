cmake_minimum_required(VERSION 3.13)
project(bachelorProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(bachelorProject main.cpp world.h player.h view.cpp controller.cpp view.h controller.h world.cpp player.cpp team.h team.cpp observable.h observer.h observable.cpp gridWorld.h gridWorld.cpp)