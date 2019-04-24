cmake_minimum_required(VERSION 3.13)
project(triangulation)

set(CMAKE_CXX_STANDARD 14)

add_executable(triangulation src/main.cpp src/primitives.cpp src/primitives.h src/DCEL.cpp src/DCEL.h src/Polygon.cpp src/Polygon.h)