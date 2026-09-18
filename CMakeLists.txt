cmake_minimum_required(VERSION 4.3)
project(jellyplex C)

set(CMAKE_C_STANDARD 11)

find_package(CURL REQUIRED)

add_executable(jellyplex main.c)

target_link_libraries(jellyplex PRIVATE CURL::libcurl)
