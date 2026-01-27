# 第1章：Qt6基础入门
# 本章介绍Qt6的基本结构，包括应用程序类、窗口部件的基本使用

cmake_minimum_required(VERSION 3.16)

project(Chapter01_Basic
    VERSION 1.0
    LANGUAGES CXX
)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用Qt的自动MOC（元对象编译器）
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找Qt6包，需要Widgets模块
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# 添加可执行文件
add_executable(Chapter01_Basic
    main.cpp
    HelloWorld.cpp
    HelloWorld.h
)

# 链接Qt库
target_link_libraries(Chapter01_B PRIVATE
    Qt6::Widgets
)

# 如果是Windows系统，设置为GUI应用程序（不显示控制台）
if(WIN32)
    set_target_properties(Chapter01_Buddy PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()
