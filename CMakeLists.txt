cmake_minimum_required(VERSION 3.24)
project(Spline_Interpolation C)

set(CMAKE_C_STANDARD 11)

add_executable(Spline_Interpolation
        spline_interpolation.c subpackages/subfuncs.h subpackages/subfuncs.c subpackages/echo.h subpackages/echo.c subpackages/constants.h)


