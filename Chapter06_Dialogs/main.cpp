/**
 * @file main.cpp
 * @brief 第6章示例 - 程序入口
 * 
 * 本章学习要点总结：
 * 
 * 1. QMessageBox（消息对话框）：
 *    - information(): 显示信息提示
 *    - question(): 提问用户，返回用户选择
 *    - warning(): 显示警告
 *    - critical(): 显示严重错误
 *    - about(): 显示关于信息
 * 
 * 2. QFileDialog（文件对话框）：
 *    - getOpenFileName(): 打开单个文件
 *    - getOpenFileNames(): 打开多个文件
 *    - getSaveFileName(): 保存文件
 *    - getExistingDirectory(): 选择目录
 *    - 可以设置文件过滤器
 * 
 * 3. QColorDialog（颜色对话框）：
 *    - getColor(): 选择颜色
 *    - 返回QColor对象
 *    - 可以设置初始颜色
 * 
 * 4. QFontDialog（字体对话框）：
 *    - getFont(): 选择字体
 *    - 返回QFont对象
 *    - 可以设置初始字体
 * 
 * 5. QInputDialog（输入对话框）：
 *    - getText(): 获取文本输入
 *    - getInt(): 获取整数输入
 *    - getDouble(): 获取浮点数输入
 *    - getItem(): 从列表中选择
 *    - 可以设置范围和默认值
 * 
 * 6. QProgressDialog（进度对话框）：
 *    - 用于显示长时间操作的进度
 *    - setValue()更新进度
 *    - wasCanceled()检查是否被取消
 *    - 可以设置最小值、最大值
 * 
 * 7. 自定义对话框：
 *    - 继承QDialog类
 *    - 使用QDialogButtonBox添加标准按钮
 *    - setModal(true)设置为模态
 *    - exec()显示模态对话框
 *    - show()显示非模态对话框
 *    - accept()和reject()设置返回值
 * 
 * 8. 对话框的返回值：
 *    - QDialog::Accepted: 用户接受（确定）
 *    - QDialog::Rejected: 用户拒绝（取消）
 *    - 通过exec()的返回值获取
 * 
 * 9. 对话框的模态性：
 *    - 模态对话框（Modal）：阻塞父窗口，必须先关闭
 *    - 非模态对话框（Modeless）：不阻塞，可同时操作
 *    - setWindowModality()设置模态性
 *    - Qt::ApplicationModal: 阻塞整个应用
 *    - Qt::WindowModal: 只阻塞父窗口
 * 
 * 10. QDialogButtonBox：
 *     - 提供标准按钮布局
 *     - 支持不同角色的按钮
 *     - 自动处理按钮点击事件
 */

#include <QApplication>
#include "DialogDemo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("Qt6对话框演示");
    
    DialogDemo demo;
    demo.show();
    
    return app.exec();
}
