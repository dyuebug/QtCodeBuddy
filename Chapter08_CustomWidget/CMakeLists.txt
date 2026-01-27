cmake_minimum_required(VERSION 3.5)

project(Chapter08_CustomWidget VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        CustomWidgetDemo.cpp
        CustomWidgetDemo.h
        ColorPickerWidget.cpp
        ColorPickerWidget.h
        CircularProgressBar.cpp
        CircularProgressBar.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Chapter08_CustomWidget
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Chapter08_CustomWidget SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Chapter08_CustomWidget
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Chapter08_CustomWidget PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Chapter08_CustomWidget PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Chapter08_CustomWidget)
endif()
