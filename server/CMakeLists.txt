cmake_minimum_required(VERSION 3.21.3)


# SERVER
project(server VERSION 1.0)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(server server.cpp)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(server PUBLIC pthread pq pqxx)


# GLOBAL
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD REQUIRED)

include_directories("include")

