# 第7章：主窗口
# 本章详细介绍Qt6的QMainWindow主窗口架构

cmake_minimum_required(VERSION 3.16)

project(Chapter07_MainWindow
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Chapter07_MainWindow
    main.cpp
    MainWindowDemo.cpp
    MainWindowDemo.h
    TextEditWidget.h
    TextEditWidget.cpp
)

target_link_libraries(Chapter07_MainWindow PRIVATE
    Qt6::Widgets
)

if(WIN32)
    set_target_properties(Chapter07_MainWindow PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
