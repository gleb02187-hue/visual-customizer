cmake_minimum_required(VERSION 3.25)
project(visual-customizer LANGUAGES CXX)

find_package(Geode REQUIRED)

add_geode_mod(visual-customizer
    src/main.cpp
)
