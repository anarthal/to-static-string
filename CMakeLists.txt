#
# Copyright (c) 2023 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#

cmake_minimum_required(VERSION 3.8...3.22)

# Project
project(to_static_string LANGUAGES CXX)


# Library
add_library(to_static_string INTERFACE)
target_compile_features(to_static_string INTERFACE cxx_std_17)
target_include_directories(to_static_string INTERFACE include)


# Test
include(CTest)
if (BUILD_TESTING)
    find_package(Catch2 REQUIRED)
    add_executable(unit_test test/test.cpp)
    target_link_libraries(unit_test PRIVATE to_static_string Catch2::Catch2WithMain)

    find_package(benchmark REQUIRED)
    add_executable(bench bench/bench.cpp)
    target_link_libraries(bench PRIVATE to_static_string benchmark::benchmark)
endif()