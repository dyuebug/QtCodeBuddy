/**
 * @file main.cpp
 * @brief 第4章示例 - 程序入口
 * 
 * 本章学习要点总结：
 * 
 * 1. 信号和槽的基本概念：
 *    - 信号（Signal）：当某个事件发生时发出的通知
 *    - 槽（Slot）：响应信号的函数
 *    - 通过connect()函数连接信号和槽
 * 
 * 2. Qt6的connect语法（函数指针语法）：
 *    - connect(sender, &SenderClass::signal, receiver, &ReceiverClass::slot)
 *    - 这是Qt6推荐的方式，编译时类型检查
 *    - 比旧版的SIGNAL/SLOT宏更安全、更高效
 * 
 * 3. 信号的发射：
 *    - 使用emit关键字：emit signalName(parameters);
 *    - emit是可选的，可以省略
 *    - 所有连接到该信号的槽都会被调用
 * 
 * 4. 自定义信号：
 *    - 在signals:部分声明
 *    - 只需声明，无需实现
 *    - 可以有参数，参数会传递给槽
 *    - 信号不能返回值
 * 
 * 5. 槽函数：
 *    - 在public slots:、protected slots:或private slots:部分声明
 *    - 普通成员函数也可以作为槽（Qt6）
 *    - 可以有参数，但参数类型和数量要与信号匹配
 *    - 可以是虚函数
 * 
 * 6. 信号和槽的参数：
 *    - 槽的参数数量可以少于信号
 *    - 槽的参数类型必须与信号对应
 *    - 如果信号有参数，会自动传递给槽
 * 
 * 7. Lambda表达式作为槽：
 *    - 可以内联定义，无需单独声明
 *    - 语法：connect(sender, &signal, [](){ lambda code *});
 *    - 可以捕获外部变量：[this](){} 或 [variable](){} 或 [&variable](){}
 *    - 适合简单的、一次性的操作
 * 
 * 8. 断开连接：
 *    - disconnect(sender, &signal, receiver, &slot)
 *    - 断开特定连接
 *    - 可以使用blockSignals(bool)临时阻止信号发射
 * 
 * 9. 多重连接：
 *    - 一个信号可以连接多个槽：所有槽都会被调用
 *    - 一个槽可以连接多个信号：任一信号触发都会执行
 *    - 连接顺序就是执行顺序
 * 
 * 10. Q_OBJECT宏：
 *     - 使用信号和槽的类必须包含Q_OBJECT宏
 *     - 必须放在类定义的第一行
 *     - 启用MOC（元对象编译器）
 * 
 * 11. 信号和槽的最佳实践：
 *     - 使用函数指针语法，而不是SIGNAL/SLOT宏
 *     - 信号名使用驼峰命名法：valueChanged()
 *     - 槽名使用on前缀：onValueChanged()
 *     - 合理使用Lambda简化代码
 *     - 注意信号循环，必要时使用blockSignals()
 */

#include <QApplication>
#include "SignalsSlotsDemo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("Qt6信号和槽演示");
    
    SignalsSlotsDemo demo;
    demo.show();
    
    return app.exec();
}
