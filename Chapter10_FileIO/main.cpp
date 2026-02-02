/**
 * @file main.cpp
 * @brief 第10章 - 文件操作演示程序入口
 *
 * 本章学习要点：
 * 1. QFile - 文件读写操作
 * 2. QTextStream - 文本流处理
 * 3. QDataStream - 二进制流处理
 * 4. QDir - 目录操作
 * 5. QFileInfo - 文件信息获取
 */

#include <QApplication>
#include "FileIODemo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Qt6文件操作演示");

    FileIODemo demo;
    demo.show();

    return app.exec();
}
