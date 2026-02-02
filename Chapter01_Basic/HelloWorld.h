/**
 * @file HelloWorld.h
 * @brief 第1章示例 - Hello World窗口类头文件
 * 
 * 本章学习要点：
 * 1. QWidget是所有用户界面对象的基类
 * 2. 继承QWidget创建自定义窗口类
 * 3. Q_OBJECT宏是使用信号和槽机制必须的
 */

#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

/**
 * @class HelloWorld
 * @brief 第一个Qt6窗口示例
 * 
 * 该类演示了Qt6中最基本的窗口创建和部件添加
 */
class HelloWorld : public QWidget
{
    // 必须使用Q_OBJECT宏，才能使用信号和槽机制
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针，默认为nullptr表示顶层窗口
     * 
     * 构造函数中：
     * 1. 调用父类构造函数
     * 2. 初始化UI界面
     */
    explicit HelloWorld(QWidget *parent = nullptr);

private:
    /**
     * @brief 初始化界面
     * 
     * 创建和设置窗口中的各个部件
     */
    void setupUi();

    /**
     * @brief 连接信号和槽
     * 
     * 演示信号和槽的基本使用
     */
    void connectSignals();

private slots:
    /**
     * @brief 槽函数 - 点击按钮时调用
     * 
     * 使用slots关键字声明槽函数
     * Qt6推荐使用函数指针语法连接信号和槽
     */
    void onButtonClicked();
    void onButtonTimeClicked();

private:
    QLabel *m_label;      ///< 标签部件，用于显示文本
    QPushButton *m_button;///< 按钮部件
    QVBoxLayout *m_layout;///< 垂直布局管理器
    QLabel *m_label_time;      ///< 标签部件，用于显示文本-time
    QPushButton *m_button_time; //当前时间
};

#endif // HELLOWORLD_H
