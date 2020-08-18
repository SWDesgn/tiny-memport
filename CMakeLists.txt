cmake_minimum_required(VERSION 3.2)

project(tiny_memport C CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(tiny_memport INTERFACE include/)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)