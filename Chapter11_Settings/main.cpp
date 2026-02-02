/**
 * @file main.cpp
 * @brief 第11章 - QSettings 配置存储演示程序入口
 *
 * 本章学习要点：
 * 1. QSettings 基本用法
 * 2. 保存和读取各种数据类型
 * 3. 分组管理配置
 * 4. 窗口状态保存和恢复
 */

#include <QApplication>
#include "SettingsDemo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("MyCompany");
    app.setApplicationName("SettingsDemo");

    SettingsDemo demo;
    demo.show();

    return app.exec();
}
