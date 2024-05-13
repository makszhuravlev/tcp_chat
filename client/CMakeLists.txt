cmake_minimum_required(VERSION 3.21.3)

project(client VERSION 1.0)

include_directories("src")
file(GLOB_RECURSE CLIENT_SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${CLIENT_SOURCES})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD REQUIRED)

#find_package(libpqxx REQUIRED)
find_package(PostgreSQL REQUIRED)


target_link_libraries(${PROJECT_NAME} PUBLIC  pq pqxx)
