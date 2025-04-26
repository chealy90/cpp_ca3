cmake_minimum_required(VERSION 3.21)
project(cpp_ca3)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_ca3 main.cpp
        Crawler.h
        Position.h
        Crawler.cpp
        Direction.h
        Board.cpp
        Board.h)


set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Users/favou/Documents/SFML-2.6.2/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics network REQUIRED) # remove audio references

include_directories(C:/Users/favou/Documents/SFML-2.6.2/include)
target_link_libraries(cpp_ca3 sfml-system sfml-window sfml-graphics)
