/**
 * @file main.cpp
 * @brief 第12章 - 模型视图演示程序入口
 *
 * 本章学习要点：
 * 1. QStringListModel 字符串列表模型
 * 2. QStandardItemModel 标准项模型
 * 3. QListView 列表视图
 * 4. QTableView 表格视图
 */

#include <QApplication>
#include "ModelViewDemo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Qt6模型视图演示");

    ModelViewDemo demo;
    demo.show();

    return app.exec();
}
