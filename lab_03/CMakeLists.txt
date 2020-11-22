cmake_minimum_required(VERSION 3.13)
project(lab_03)


set(CMAKE_CXX_STANDARD 14)
set(SRC ./src)

add_executable(lab_03 ${SRC}/main.cpp ${SRC}/lab_03.h ${SRC}/lab_03.cpp
               ${SRC}/Lexer.cpp ${SRC}/Lexer.h ${SRC}/Syntax.cpp ${SRC}/Syntax.h
               ${SRC}/Lexem.cpp ${SRC}/Lexem.h ${SRC}/Variable.cpp
               ${SRC}/Variable.h ${SRC}/Tree.cpp ${SRC}/Tree.h)
