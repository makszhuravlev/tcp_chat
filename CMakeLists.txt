cmake_minimum_required(VERSION 3.21.3)

project(server VERSION 1.0)

include_directories("server/include")
include_directories(${Boost_INCLUDE_DIRS})

#find_package(libpqxx REQUIRED)не рекомендуется уже есть в зависимостях
find_package(PostgreSQL REQUIRED)
#find_package(PostgreSQL )остальные зависимости
find_package(Boost REQUIRED COMPONENTS system)

file(GLOB_RECURSE SERVER_SOURCES "server/src/*.cpp")
add_executable(server ${SERVER_SOURCES})

# (First set LIBVERSION to the libpqxx version you have.)
set(libpqxxdir "libpqxx-${LIBVERSION}")

# You can usually skip building the tests.
set(SKIP_BUILD_TEST ON)

set(BUILD_SHARED_LIBS OFF)

add_subdirectory(deps/libpqxx)

target_link_libraries(server PUBLIC pthread pq pqxx)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD REQUIRED)


# FILE MANAGEMENT
file(COPY ${CMAKE_SOURCE_DIR}/server/data/ DESTINATION ${CMAKE_BINARY_DIR}/server_data)
