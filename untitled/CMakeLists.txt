cmake_minimum_required(VERSION 3.20)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled main.c)

project(cs455openGL)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
