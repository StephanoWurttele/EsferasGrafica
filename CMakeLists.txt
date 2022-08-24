cmake_minimum_required(VERSION 3.20)
project(LABGRAFICA)

file(GLOB source_files
        main.cpp
        *.cpp)

add_executable(${PROJECT_NAME}
        ${source_files} Luz.cpp Luz.h)