/**
 * @file main.cpp
 * @brief 第3章示例 - 程序入口
 * 
 * 本章学习要点总结：
 * 
 * 1. QVBoxLayout（垂直布局）：
 *    - 部件从上到下排列
 *    - 使用addWidget()添加部件
 *    - 使用addLayout()添加子布局
 *    - 使用addStretch()添加弹性空间
 * 
 * 2. QHBoxLayout（水平布局）：
 *    - 部件从左到右排列
 *    - 用法与QVBoxLayout类似
 *    - 可以使用addSpacing()添加固定间距
 * 
 * 3. QGridLayout（网格布局）：
 *    - 部件按行列网格排列
 *    - 支持跨行和跨列
 *    - 语法：addWidget(widget, row, column, rowSpan, columnSpan)
 *    - 可以设置单独行和列的拉伸因子
 * 
 * 4. QFormLayout（表单布局）：
 *    - 专门用于表单界面
 *    - 自动管理标签和字段的成对排列
 *    - 使用addRow(label, field)添加表单项
 *    - 标签默认右对齐
 * 
 * 5. 布局嵌套：
 *    - 可以将一种布局嵌入到另一种布局中
 *    - 使用addLayout()添加子布局
 *    - 可以创建复杂的界面结构
 * 
 * 6. 拉伸因子（Stretch Factor）：
 *    - 控制部件在可用空间中的分配比例
 *    - 语法：addWidget(widget, stretch)
 *    - 拉伸因子越大，占据的空间越多
 * 
 * 7. 布局管理的重要方法：
 *    - setSpacing(int)：设置部件之间的间距
 *    - setContentsMargins(int, int, int, int)：设置边距
 *    - setStretch(index, factor)：设置指定位置的拉伸因子
 *    - count()：获取布局中的项目数量
 *    - takeAt(index)：移除指定位置的项目
 * 
 * 8. QSpacerItem（弹簧）：
 *    - 用于创建可伸缩的空间
 *    - addStretch()相当于添加一个可伸缩的弹簧
 *    - addSpacing(width/height)添加固定大小的空间
 * 
 * 9. 布局的最佳实践：
 *    - 始终使用布局管理器，而不是硬编码位置
 *    - 适当使用嵌套布局来组织复杂界面
 *    - 合理设置拉伸因子，使界面在不同窗口大小下都能良好显示
 *    - 使用margins和spacing使界面更加美观
 */

#include <QApplication>
#include "LayoutDemo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("Qt6布局管理演示");
    
    LayoutDemo demo;
    demo.show();
    
    return app.exec();
}
