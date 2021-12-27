cmake_minimum_required(VERSION 3.22)
project(minescpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(minescpp src/main.cpp src/GameOver.cpp src/GameOver.h src/SteppedOnMine.cpp src/SteppedOnMine.h src/Cell.cpp src/Cell.h src/Minefield.cpp src/Minefield.h src/Coordinate.cpp src/Coordinate.h src/Action.cpp src/Action.h)
