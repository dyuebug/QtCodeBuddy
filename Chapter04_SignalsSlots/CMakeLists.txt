# 第4章：信号和槽
# 本章详细介绍Qt6的信号和槽机制

cmake_minimum_required(VERSION 3.16)

project(Chapter04_SignalsSlots
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Chapter04_SignalsSlots
    main.cpp
    SignalsSlotsDemo.cpp
    SignalsSlotsDemo.h
    Counter.h
    Counter.cpp
)

target_link_libraries(Chapter04_SignalsSlots PRIVATE
    Qt6::Widgets
)

if(WIN32)
    set_target_properties(Chapter04_SignalsSlots PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
