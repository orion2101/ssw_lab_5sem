cmake_minimum_required(VERSION 3.13)
project(lab_02)


set(CMAKE_CXX_STANDARD 14)
set(SRC ./src)

add_executable(lab_02 ${SRC}/main.cpp ${SRC}/lab_02.h ${SRC}/lab_02.cpp
               ${SRC}/Lexer.cpp ${SRC}/Lexer.h ${SRC}/Syntax.cpp ${SRC}/Syntax.h
               ${SRC}/Lexem.cpp ${SRC}/Lexem.h ${SRC}/Variable.cpp
               ${SRC}/Variable.h)
