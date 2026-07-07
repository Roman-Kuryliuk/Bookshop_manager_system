cmake_minimum_required(VERSION 4.1)
project(Bookshop_manager_system)

set(CMAKE_CXX_STANDARD 20)

add_executable(Bookshop_manager_system main.cpp
        login.h)

find_package(MySQL QUIET)

if (MySQL_FOUND)
    target_include_directories(Bookshop_manager_system PRIVATE ${MySQL_INCLUDE_DIRS})
    target_link_libraries(Bookshop_manager_system PRIVATE ${MySQL_LIBRARIES})
else()
    set(MYSQL_INCLUDE_DIR "" CACHE PATH "Path to MySQL include directory")
    set(MYSQL_LIBRARY "" CACHE FILEPATH "Path to MySQL client library")

    if (NOT MYSQL_INCLUDE_DIR OR NOT MYSQL_LIBRARY)
        message(FATAL_ERROR
                "MySQL was not found. Please install MySQL development files or configure "
                "MYSQL_INCLUDE_DIR and MYSQL_LIBRARY.")
    endif()

    target_include_directories(Bookshop_manager_system PRIVATE ${MYSQL_INCLUDE_DIR})
    target_link_libraries(Bookshop_manager_system PRIVATE ${MYSQL_LIBRARY})
endif()