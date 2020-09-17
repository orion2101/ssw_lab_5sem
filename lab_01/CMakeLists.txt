cmake_minimum_required(VERSION 3.13)
project(lab_01)

set(CMAKE_CXX_STANDARD 14)
set(SRC ./src)

add_executable(lab_01 ${SRC}/main.cpp ${SRC}/lab_01.cpp ${SRC}/lab_01.h)
