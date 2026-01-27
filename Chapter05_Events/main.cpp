/**
 * @file main.cpp
 * @brief 第5章示例 - 程序入口
 * 
 * 本章学习要点总结：
 * 
 * 1. Qt事件系统概述：
 *    - Qt使用事件驱动模型
 *    - 事件是QEvent及其子类的实例
 *    - 事件通过事件循环分发
 *    - 事件可以被处理、忽略或传播
 * 
 * 2. 鼠标事件：
 *    - mousePressEvent(): 鼠标按下
 *    - mouseReleaseEvent(): 鼠标释放
 *    - mouseMoveEvent(): 鼠标移动（需要setMouseTracking(true)才能持续接收）
 *    - mouseDoubleClickEvent(): 鼠标双击
 *    - enterEvent(): 鼠标进入部件
 *    - leaveEvent(): 鼠标离开部件
 * 
 * 3. 键盘事件：
 *    - keyPressEvent(): 键盘按下
 *    - keyReleaseEvent(): 键盘释放
 *    - event->key(): 获取按键码（Qt::Key_*）
 *    - event->text(): 获取按键文本
 *    - event->modifiers(): 获取修饰键（Ctrl, Alt, Shift等）
 * 
 * 4. 焦点事件：
 *    - focusInEvent(): 获得焦点
 *    - focusOutEvent(): 失去焦点
 *    - setFocus(): 设置焦点
 *    - hasFocus(): 检查是否有焦点
 *    - focusPolicy(): 获取焦点策略
 * 
 * 5. 窗口事件：
 *    - resizeEvent(): 窗口大小改变
 *    - moveEvent(): 窗口移动
 *    - closeEvent(): 窗口关闭（可以拦截）
 *    - showEvent(): 窗口显示
 *    - hideEvent(): 窗口隐藏
 * 
 * 6. 绘制事件：
 *    - paintEvent(): 需要重绘时调用
 *    - 使用QPainter进行绘制
 *    - update()或repaint()触发重绘
 *    - 不要在paintEvent中调用update()或repaint()
 * 
 * 7. 定时器事件：
 *    - 方式1：使用QTimer类（推荐）
 *    - 方式2：重写timerEvent()
 *    - startTimer()启动定时器
 *    - killTimer()停止定时器
 * 
 * 8. 事件过滤器：
 *    - installEventFilter(): 安装事件过滤器
 *    - removeEventFilter(): 移除事件过滤器
 *    - eventFilter(): 重写此函数实现过滤
 *    - 返回true表示事件被处理，false表示继续传递
 * 
 * 9. 事件处理流程：
 *    - 事件产生 -> 事件循环 -> 分发给目标对象
 *    - 目标对象调用event()方法
 *    - event()根据类型调用具体的事件处理函数
 *    - 可以忽略事件（调用基类的处理函数）
 * 
 * 10. 事件和信号的区别：
 *     - 事件：由系统或用户产生，处理具体的交互
 *     - 信号：由程序主动发射，用于对象间通信
 *     - 事件是低层机制，信号是高层抽象
 * 
 * 11. 最佳实践：
 *     - 使用信号处理高级事件
 *     - 使用事件处理底层事件
 *     - 注意调用基类的事件处理函数
 *     - 合理使用事件过滤器
 */

#include <QApplication>
#include "EventDemo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("Qt6事件处理演示");
    
    EventDemo demo;
    demo.show();
    
    return app.exec();
}
