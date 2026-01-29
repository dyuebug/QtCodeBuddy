cmake_minimum_required(VERSION 3.5)

project(NotepadPro VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# 核心数据层
set(CORE_SOURCES
    core/Note.h
    core/Note.cpp
    core/Category.h
    core/Category.cpp
    core/NoteManager.h
    core/NoteManager.cpp
)

# 自定义控件层
set(WIDGETS_SOURCES
    widgets/NoteListWidget.h
    widgets/NoteListWidget.cpp
    widgets/RichTextEditor.h
    widgets/RichTextEditor.cpp
    widgets/CategoryTree.h
    widgets/CategoryTree.cpp
    widgets/SearchWidget.h
    widgets/SearchWidget.cpp
    widgets/StatusWidget.h
    widgets/StatusWidget.cpp
)

# 对话框层
set(DIALOGS_SOURCES
    dialogs/NotePropertiesDialog.h
    dialogs/NotePropertiesDialog.cpp
    dialogs/CategoryDialog.h
    dialogs/CategoryDialog.cpp
    dialogs/SettingsDialog.h
    dialogs/SettingsDialog.cpp
    dialogs/AboutDialog.h
    dialogs/AboutDialog.cpp
)

# 主窗口层
set(MAINWINDOW_SOURCES
    mainwindow/MainWindow.h
    mainwindow/MainWindow.cpp
)

# 资源文件
set(RESOURCE_FILES
    resources/icons.qrc
)

# 所有源文件
set(PROJECT_SOURCES
    main.cpp
    ${CORE_SOURCES}
    ${WIDGETS_SOURCES}
    ${DIALOGS_SOURCES}
    ${MAINWINDOW_SOURCES}
    ${RESOURCE_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NotepadPro
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(NotepadPro SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(NotepadPro
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(NotepadPro PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# 包含目录
target_include_directories(NotepadPro PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/dialogs
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow
)

set_target_properties(NotepadPro PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.qtcodebuddy.notepadpro
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NotepadPro)
endif()
