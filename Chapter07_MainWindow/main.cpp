/**
 * @file main.cpp
 * @brief 第7章示例 - 程序入口
 * 
 * 本章学习要点总结：
 * 
 * 1. QMainWindow架构：
 *    - 菜单栏（QMenuBar）：位于窗口顶部，包含下拉菜单
 *    - 工具栏（QToolBar）：可移动的工具按钮区域
 *    - 中心部件（Central Widget）：窗口的主要工作区域
 *    - 停靠窗口（QDockWidget）：可停靠的侧边窗口
 *    - 状态栏（QStatusBar）：窗口底部显示状态信息
 * 
 * 2. 菜单栏（QMenuBar）：
 *    - 使用menuBar()获取菜单栏
 *    - addMenu()添加菜单
 *    - addAction()添加菜单项
 *    - addSeparator()添加分隔线
 *    - setShortcut()设置快捷键
 *    - setStatusTip()设置状态栏提示
 * 
 * 3. 工具栏（QToolBar）：
 *    - addToolBar()添加工具栏
 *    - addAction()添加动作（可以重用菜单动作）
 *    - addSeparator()添加分隔线
 *    - addWidget()添加自定义部件（如ComboBox）
 *    - setMovable()设置是否可移动
 *    - setFloatable()设置是否可浮动
 * 
 * 4. 状态栏（QStatusBar）：
 *    - statusBar()获取状态栏
 *    - addWidget()添加部件（左侧显示）
 *    - addPermanentWidget()添加永久部件（右侧显示）
 *    - showMessage()显示临时消息
 *    - clearMessage()清除消息
 * 
 * 5. 中心部件（Central Widget）：
 *    - setCentralWidget()设置中心部件
 *    - 可以是任何QWidget或其子类
 *    - 只能有一个中心部件
 *    - 占据窗口的主要区域
 * 
 * 6. 停靠窗口（QDockWidget）：
 *    - addDockWidget()添加停靠窗口
 *    - setAllowedAreas()设置允许的停靠区域
 *    - setFloating()设置是否浮动
 *    - toggleViewAction()返回显示/隐藏的动作
 *    - 停靠区域：Top, Bottom, Left, Right, All
 * 
 * 7. QAction（动作）：
 *    - 可以添加到菜单、工具栏、快捷键
 *    - setText()设置文本
 *    - setIcon()设置图标
 *    - setShortcut()设置快捷键
 *    - setStatusTip()设置状态提示
 *    - setCheckable()设置是否可勾选
 *    - triggered()信号
 * 
 * 8. QMainWindow的其他功能：
 *    - 保存和恢复窗口状态
 *    - 创建上下文菜单
 *    - 处理窗口关闭事件
 *    - 使用QStatusBar显示状态信息
 * 
 * 9. 主窗口的设计原则：
 *    - 合理使用菜单、工具栏、状态栏
 *    - 保持界面简洁明了
 *    - 提供必要的停靠窗口
 *    - 确保功能齐全但不过于复杂
 */

#include <QApplication>
#include "MainWindowDemo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("Qt6主窗口演示");
    app.setOrganizationName("QtDemo");
    
    MainWindowDemo demo;
    demo.show();
    
    return app.exec();
}
