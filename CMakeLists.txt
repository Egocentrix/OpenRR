cmake_minimum_required(VERSION 3.5.0)
project(OpenRR VERSION 0.1.0)

add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -std=c++20)

add_compile_options(-fsanitize=address -fsanitize=leak -fsanitize=undefined)
add_link_options(-fsanitize=address -fsanitize=leak -fsanitize=undefined)

find_package(SFML 2.4 COMPONENTS graphics window system REQUIRED)

set(OPENRR_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

