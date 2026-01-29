/**
 * @file main.cpp
 * @brief NotepadPro 个人笔记本应用 - 程序入口
 *
 * 本项目是一个综合性的 Qt6 学习项目，整合了以下知识点：
 * - Chapter01: QApplication 程序入口
 * - Chapter02: 基础控件使用
 * - Chapter03: 布局管理
 * - Chapter04: 信号与槽机制
 * - Chapter05: 事件处理
 * - Chapter06: 对话框
 * - Chapter07: QMainWindow 主窗口
 * - Chapter08: 自定义控件
 */

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 设置应用程序信息
    app.setApplicationName("NotepadPro");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("QtCodeBuddy");
    app.setOrganizationDomain("qtcodebuddy.com");

    // 设置应用程序样式
    app.setStyle("Fusion");

    // 创建并显示主窗口
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
