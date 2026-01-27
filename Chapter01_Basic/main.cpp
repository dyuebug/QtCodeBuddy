/**
 * @file main.cpp
 * @brief 第1章示例 - 程序入口
 * 
 * 本章学习要点：
 * 1. QApplication是Qt应用程序的核心类
 * 2. Qt应用程序的基本生命周期
 * 3. 事件循环的概念
 */

#include <QApplication>
#include "HelloWorld.h"

/**
 * @brief 主函数
 * @param argc 命令行参数数量
 * @param argv 命令行参数数组
 * @return 应用程序退出码
 * 
 * Qt应用程序的标准入口函数结构：
 * 1. 创建QApplication对象（处理命令行参数）
 * 2. 创建并显示窗口
 * 3. 进入事件循环
 * 4. 返回退出码
 */
int main(int argc, char *argv[])
{
    // 1. 创建QApplication对象
    // QApplication管理GUI应用程序的控制流和主要设置
    // 它必须在任何显示相关代码之前创建
    QApplication app(argc, argv);
    
    // 设置应用程序信息
    app.setApplicationName("Qt6基础教程");    // 应用程序名称
    app.setOrganizationName("MyCompany");     // 组织名称
    app.setApplicationVersion("1.0.0");        // 应用程序版本
    
    // 2. 创建主窗口
    // 在堆上创建窗口对象，使用智能指针或由父窗口自动管理内存
    HelloWorld window;
    
    // 3. 显示窗口
    // show()使窗口可见并显示在屏幕上
    window.show();
    
    // 4. 进入事件循环
    // exec()启动主事件循环，等待并处理事件
    // 当调用quit()或关闭最后一个窗口时（取决于quitOnLastWindowClosed属性），exec()返回
    // 返回值：0表示正常退出，非0表示异常退出
    return app.exec();
}

/**
 * Qt6核心概念总结：
 * 
 * 1. QApplication：
 *    - 每个GUI应用程序必须有且仅有一个QApplication对象
 *    - 负责处理命令行参数、事件循环、应用程序级设置
 * 
 * 2. QWidget：
 *    - 所有用户界面对象的基类
 *    - 可以是窗口（没有父窗口）或子部件（有父窗口）
 *    - 顶层窗口可以显示在任务栏中
 * 
 * 3. 部件（Widget）：
 *    - QLabel：显示文本或图像
 *    - QPushButton：可点击的按钮
 *    - QLineEdit：单行文本输入
 *    - 等等...
 * 
 * 4. 布局管理：
 *    - QVBoxLayout：垂直布局
 *    - QHBoxLayout：水平布局
 *    - QGridLayout：网格布局
 *    - 布局自动管理部件的大小和位置
 * 
 * 5. 信号和槽：
 *    - Qt的对象通信机制
 *    - 信号：当某个事件发生时发出的通知
 *    - 槽：响应信号的函数
 *    - 通过connect()函数连接
 * 
 * 6. 事件循环：
 *    - exec()启动事件循环
 *    - 持续等待和处理用户事件（点击、按键等）
 *    - 直到应用程序退出
 */
