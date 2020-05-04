cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(NumericArray-dev)

set(ENABLE_TESTS ON CACHE BOOL "" FORCE)
set(ENABLE_UNITTESTS ON CACHE BOOL "" FORCE)

add_subdirectory(NumericArray)
