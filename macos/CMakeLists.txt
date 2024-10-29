cmake_minimum_required(VERSION 3.16)
project(CircAdaptUI VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(macOSHelpers
    STATIC
    include/helpers.h
    helpers.mm
)
target_include_directories(macOSHelpers PUBLIC "include/")
