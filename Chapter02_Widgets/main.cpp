/**
 * @file main.cpp
 * @brief 第2章示例 - 程序入口
 * 
 * 本章学习要点总结：
 * 
 * 1. 按钮部件：
 *    - QPushButton：普通按钮，可点击触发操作
 *    - QCheckBox：复选框，可多选
 *    - QRadioButton：单选按钮，需要放在同一组中互斥
 * 
 * 2. 输入部件：
 *    - QLineEdit：单行文本输入
 *    - QTextEdit：多行文本输入（支持富文本）
 *    - QSpinBox：整数输入，有范围限制
 *    - QDoubleSpinBox：浮点数输入
 *    - QComboBox：下拉选择框
 *    - QSlider：滑动条，可用于调整数值
 * 
 * 3. 显示部件：
 *    - QLabel：显示文本或图像
 *    - QProgressBar：进度条
 *    - QLCDNumber：LCD风格数字显示
 * 
 * 4. 容器部件：
 *    - QGroupBox：分组框，用于组织相关控件
 *    - QTabWidget：选项卡部件
 *    - QStackedWidget：堆叠部件，一次只显示一个页面
 * 
 * 5. 窗口属性：
 *    - setWindowTitle()：设置窗口标题
 *    - resize()：设置窗口大小
 *    - move()：移动窗口位置
 *    - show()：显示窗口
 *    - hide()：隐藏窗口
 *    - close()：关闭窗口
 * 
 * 6. 窗口模态性：
 *    - 模态窗口（exec()）：阻塞父窗口，必须先关闭
 *    - 非模态窗口（show()）：不阻塞，可同时操作其他窗口
 *    - Qt::WindowModal：只阻塞父窗口
 *    - Qt::ApplicationModal：阻塞整个应用程序
 * 
 * 7. 其他常用方法：
 *    - setToolTip()：设置工具提示（鼠标悬停显示）
 *    - setStyleSheet()：设置样式表（QSS）
 *    - setEnabled()：启用/禁用部件
 *    - setVisible()：显示/隐藏部件
 */

#include <QApplication>
#include "WidgetsDemo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("Qt6部件演示");
    
    WidgetsDemo demo;
    demo.show();
    
    return app.exec();
}
