cmake_minimum_required(VERSION 3.0.0)
project(OpenRR VERSION 0.1.0)

add_compile_options(-Wall -Wextra -Wpedantic -Wshadow)

find_package(SFML 2.4 COMPONENTS graphics window system REQUIRED)

add_subdirectory(src)

