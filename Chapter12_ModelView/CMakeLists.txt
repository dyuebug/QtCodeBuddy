cmake_minimum_required(VERSION 3.16)
project(Chapter12_ModelView LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
    main.cpp
    ModelViewDemo.h
    ModelViewDemo.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
