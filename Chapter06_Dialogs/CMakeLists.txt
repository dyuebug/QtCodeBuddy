# 第6章：对话框
# 本章详细介绍Qt6的各种对话框

cmake_minimum_required(VERSION 3.16)

project(Chapter06_Dialogs
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Chapter06_Dialogs
    main.cpp
    DialogDemo.cpp
    DialogDemo.h
    CustomDialog.h
    CustomDialog.cpp
)

target_link_libraries(Chapter06_Dialogs PRIVATE
    Qt6::Widgets
)

if(WIN32)
    set_target_properties(Chapter06_Dialogs PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
