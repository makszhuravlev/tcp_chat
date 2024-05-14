cmake_minimum_required(VERSION 3.21.3)

project(server VERSION 1.0)

include_directories("src" "include")
file(GLOB_RECURSE SERVER_SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} main.cpp ${SERVER_SOURCES})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD REQUIRED)
#find_package(libpqxx REQUIRED)
find_package(PostgreSQL REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC  pq pqxx pthread)
