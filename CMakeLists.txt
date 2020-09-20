cmake_minimum_required(VERSION 3.10)
project(efrei_m1_str_tp1_rappels C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(efrei_m1_str_tp1_rappels main.c)