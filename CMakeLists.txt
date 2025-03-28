cmake_minimum_required(VERSION 3.30)
project(CA3)

set(CMAKE_CXX_STANDARD 20)

add_executable(CA3 main.cpp
        Crawler.h
        Position.h
        Crawler.cpp
        Direction.h)
