cmake_minimum_required(VERSION 3.0)
project(first)

set(CMAKE_CXX_STANDARD 17)

add_executable(first main.cpp 5-1.h 5-2.h 5-3.h 5-4.h 5-5.h 5-6.h 5-7.h colors.h 6-1.h 6-2.h 6-3.h 6-4.h 6-5.h 6-6.h)
target_link_libraries(first gmp gmpxx)
