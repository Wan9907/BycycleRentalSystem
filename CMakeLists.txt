cmake_minimum_required(VERSION 3.20)
project(BycycleRentalSystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(BycycleRentalSystem
        main.cpp
        member.cpp
        member.h
        Bicycle.h
        Bicycle.cpp
)