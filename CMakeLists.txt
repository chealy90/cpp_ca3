cmake_minimum_required(VERSION 3.30)
project(cpp_ca3)

set(CMAKE_CXX_STANDARD 20)

add_executable(CA3 main.cpp
        Crawler.h
        Position.h
        Crawler.cpp
        Direction.h
        Board.cpp
        Board.h
        Bug.cpp
        Bug.h
        Hopper.cpp
        Hopper.h)


set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics network REQUIRED)

include_directories(C:/SFML-2.5.1/include)
target_link_libraries(CA3 sfml-system sfml-window sfml-graphics)
