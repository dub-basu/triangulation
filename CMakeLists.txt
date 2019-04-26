cmake_minimum_required(VERSION 3.10)
project(triangulation)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)

# flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -g")

add_executable(triangulation
               src/main.cpp 
               src/primitives.cpp 
               src/primitives.h 
               src/DCEL.cpp 
               src/DCEL.h 
               src/Polygon.cpp 
               src/Polygon.h 
               src/Triangulator.cpp 
               src/EventQueue.tpp
               src/Status.tpp
               src/LSISegment.cpp 
               src/Graphix.cpp
               src/TriangulatorGraphix.cpp
               src/LSISegment.h src/Triangulator.h)

target_link_libraries(triangulation glfw ${OPENGL_LIBRARY})
