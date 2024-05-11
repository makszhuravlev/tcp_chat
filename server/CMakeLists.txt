cmake_minimum_required(VERSION 3.0)

project(server VERSION 1.0)

add_executable(${PROJECT_NAME} main.cpp)
set(CMAKE_CXX_STANDARD 20)

find_package(libpqxx REQUIRED)
find_package(PostgreSQL REQUIRED)


target_link_libraries(${PROJECT_NAME} PUBLIC  pq pqxx)
