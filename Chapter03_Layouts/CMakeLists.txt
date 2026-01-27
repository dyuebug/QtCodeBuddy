# 第3章：布局管理
# 本章详细介绍Qt6的各种布局管理器及其使用方法

cmake_minimum_required(VERSION 3.16)

project(Chapter03_Layouts
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Chapter03_Layouts
    main.cpp
    LayoutDemo.cpp
    LayoutDemo.h
)

target_link_libraries(Chapter03_Layouts PRIVATE
    Qt6::Widgets
)

if(WIN32)
    set_target_properties(Chapter03_Layouts PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
