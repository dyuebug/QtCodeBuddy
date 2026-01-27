# 第8章：自定义部件
# 本章详细介绍如何创建自定义部件

cmake_minimum_required(VERSION 3.16)

project(Chapter08_CustomWidget
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Chapter08_CustomWidget
    main.cpp
    CustomWidgetDemo.cpp
    CustomWidgetDemo.h
    ColorPickerWidget.h
    ColorPickerWidget.cpp
    CircularProgressBar.h
    CircularProgressBar.cpp
)

target_link_libraries(Chapter08_CustomWidget PRIVATE
    Qt6::Widgets
)

if(WIN32)
    set_target_properties(Chapter08_CustomWidget PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
