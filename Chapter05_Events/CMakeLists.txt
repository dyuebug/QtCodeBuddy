# 第5章：事件处理
# 本章详细介绍Qt6的事件处理机制

cmake_minimum_required(VERSION 3.16)

project(Chapter05_Events
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Chapter05_Events
    main.cpp
    EventDemo.cpp
    EventDemo.h
    ClickLabel.h
    ClickLabel.cpp
    MouseTracker.h
    MouseTracker.cpp
)

target_link_libraries(Chapter05_Events PRIVATE
    Qt6::Widgets
)

if(WIN32)
    set_target_properties(Chapter05_Events PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
