cmake_minimum_required(VERSION 3.25)
project(Concu)

set(CMAKE_CXX_STANDARD 20)

add_executable(Concu start.cpp Mutex/mutex_test.cpp)
