cmake_minimum_required(VERSION 3.30)
project(untitled6)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled6 src/main.cpp
        src/red-black.h
        src/hash.h
        src/Menu.cpp
)
configure_file(data/graduates.csv data/graduates.csv COPYONLY)
configure_file(data/college_student_placement_dataset.csv data/college_student_placement_dataset.csv COPYONLY)

