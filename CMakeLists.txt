cmake_minimum_required(VERSION 3.21.3)

project(server VERSION 1.0)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути для include файлов
include_directories("server/include")
include_directories(${Boost_INCLUDE_DIRS})

# Поиск зависимостей
find_package(PostgreSQL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# Добавление исходных файлов
file(GLOB_RECURSE SERVER_SOURCES "server/src/*.cpp")
add_executable(server ${SERVER_SOURCES})

# Установка версии библиотеки libpqxx 
set(LIBVERSION "7.6")  
set(libpqxxdir "libpqxx-${LIBVERSION}")

# Отключение сборки тестов
set(SKIP_BUILD_TEST ON)

# 
set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")

# Настройка сборки статических библиотек
#set(BUILD_SHARED_LIBS OFF)


# Добавление подкаталога с зависимостью libpqxx
add_subdirectory(deps/libpqxx)

# Линковка библиотек
target_link_libraries(server PUBLIC pthread pq pqxx)

# Копирование данных
file(COPY ${CMAKE_SOURCE_DIR}/server/data/ DESTINATION ${CMAKE_BINARY_DIR}/server_data)

# Установка целевого файла
#install(TARGETS server RUNTIME DESTINATION bin)

# Настройки для создания пакета
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "Server-chat")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "CyberConnectSoftwere")
set(CPACK_PACKAGE_VENDOR "CyberConnect")
set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/some")
set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)
set(CPACK_DEB_COMPONENT_INSTALL YES)
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libstdc++6")

# Включение всех необходимых динамических библиотек
include(GNUInstallDirs)

install(TARGETS server
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Настройка включения динамических библиотек
file(GLOB_RECURSE LIBS_TO_PACKAGE ${CMAKE_BINARY_DIR}/*.so*)

foreach(lib ${LIBS_TO_PACKAGE})
    install(FILES ${lib} DESTINATION ${CMAKE_INSTALL_LIBDIR})
endforeach()

# Включение CPack для создания пакета (make package)
include(CPack)