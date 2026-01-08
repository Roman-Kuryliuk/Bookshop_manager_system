cmake_minimum_required(VERSION 4.1)
project(Bookshop_manager_system)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        "C:/Program Files/MySQL/MySQL Server 8.0/include"
)

link_directories(
        "C:/Program Files/MySQL/MySQL Server 8.0/lib"
)

add_executable(Bookshop_manager_system main.cpp
        login.h)

target_link_libraries(Bookshop_manager_system libmysql)