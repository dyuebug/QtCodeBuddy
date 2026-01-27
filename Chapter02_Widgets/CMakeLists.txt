# 第2章：窗口和部件
# 本章详细介绍各种常用窗口部件的使用方法

cmake_minimum_required(VERSION 3.16)

project(Chapter02_Widgets
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Chapter02_Widgets
    main.cpp
    WidgetsDemo.cpp
    WidgetsDemo.h
)

target_link_libraries(Chapter02_Widgets PRIVATE
    Qt6::Widgets
)

if(WIN32)
    set_target_properties(Chapter02_Widgets PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
