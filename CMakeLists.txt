cmake_minimum_required(VERSION 3.10.0)
project(DigitalCircuitSimulator VERSION 1.0.0 LANGUAGES CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -DMEMTRACE")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.cpp")

add_executable(DigitalCircuitSimulator "${source_files}")

