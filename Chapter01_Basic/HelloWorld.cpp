/**
 * @file HelloWorld.cpp
 * @brief 第1章示例 - Hello World窗口类实现
 */

#include "HelloWorld.h"
#include <QMessageBox>
#include <QApplication>

/**
 * @brief HelloWorld构造函数
 * @param parent 父窗口指针
 * 
 * 构造流程：
 * 1. 调用QWidget构造函数，设置父窗口
 * 2. 调用setupUi()初始化界面
 * 3. 调用connectSignals()连接信号和槽
 */
HelloWorld::HelloWorld(QWidget *parent)
    : QWidget(parent)          // 调用基类构造函数
    , m_label(nullptr)         // 初始化成员指针为空
    , m_button(nullptr)
    , m_layout(nullptr)
{
    // 初始化界面
    setupUi();
    
    // 连接信号和槽
    connectSignals();
    
    // 设置窗口属性
    setWindowTitle("第1章：Qt6基础入门 - Hello World");  // 设置窗口标题
    resize(400, 300);                                     // 设置窗口大小
}

/**
 * @brief 初始化界面
 * 
 * 创建所有部件并设置属性
 */
void HelloWorld::setupUi()
{
    // 1. 创建标签部件
    // QLabel用于显示文本或图片
    m_label = new QLabel("欢迎使用Qt6！", this);
    m_label->setAlignment(Qt::AlignCenter);  // 设置文本居中对齐
    m_label->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");
    
    // 2. 创建按钮部件
    // QPushButton是最常用的按钮部件
    m_button = new QPushButton("点击我", this);
    m_button->setMinimumHeight(40);  // 设置最小高度
    m_button->setStyleSheet("font-size: 14px;");
    
    // 3. 创建布局管理器
    // QVBoxLayout用于垂直排列部件
    m_layout = new QVBoxLayout(this);
    
    // 4. 将部件添加到布局中
    // addWidget()会将部件添加到布局，布局会自动管理部件的位置和大小
    m_layout->addWidget(m_label);
    m_layout->addWidget(m_button);
    
    // 5. 设置布局的间距
    m_layout->setSpacing(20);        // 部件之间的间距
    m_layout->setContentsMargins(30, 30, 30, 30);  // 边距（左、上、右、下）
}

/**
 * @brief 连接信号和槽
 * 
 * Qt6推荐使用函数指针语法连接信号和槽
 * 语法：connect(sender, &SenderClass::signal, receiver, &ReceiverClass::slot)
 */
void HelloWorld::connectSignals()
{
    // 方式1：使用成员函数指针（Qt6推荐）
    // 当按钮被点击时，调用onButtonClicked()槽函数
    connect(m_button, &QPushButton::clicked, this, &HelloWorld::onButtonClicked);
}

/**
 * @brief 槽函数 - 按钮点击事件处理
 * 
 * 当用户点击按钮时，此函数会被自动调用
 */
void HelloWorld::onButtonClicked()
{
    // 使用QMessageBox显示消息对话框
    static int clickCount = 0;  // 静态变量，记录点击次数
    clickCount++;
    
    // 设置标签的新文本
    QString text = QString("你已点击按钮 %1 次！").arg(clickCount);
    m_label->setText(text);
    
    // 根据点击次数显示不同的消息
    if (clickCount == 1) {
        QMessageBox::information(this, "提示", "这是第一次点击！\nQt6的信号和槽机制工作正常！");
    } else if (clickCount == 5) {
        QMessageBox::information(this, "恭喜", "你已经点击了5次！\n继续探索Qt6吧！");
    }
}
