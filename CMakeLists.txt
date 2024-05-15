cmake_minimum_required(VERSION 3.21.3)


# SERVER
project(server VERSION 1.0)

file(GLOB_RECURSE SERVER_SOURCES "server/src/*.cpp")
add_executable(server ${SERVER_SOURCES})

include_directories("server/include")
target_link_libraries(server PUBLIC pthread pq pqxx)

# CLIENT
project(client VERSION 1.0)

file(GLOB_RECURSE CLIENT_SOURCES "client/src/*.cpp")
add_executable(client ${CLIENT_SOURCES})

include_directories("client/include")
target_link_libraries(client PUBLIC pthread pq pqxx)


# GLOBAL
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD REQUIRED)

include_directories("include")

#find_package(libpqxx REQUIRED)
#find_package(PostgreSQL REQUIRED)

# FILE MANAGEMENT
file(COPY ${CMAKE_SOURCE_DIR}/server/data/ DESTINATION ${CMAKE_BINARY_DIR}/server_data)
file(COPY ${CMAKE_SOURCE_DIR}/client/data/ DESTINATION ${CMAKE_BINARY_DIR}/client_data)