/**
 * @file main.cpp
 * @brief 第8章示例 - 程序入口
 * 
 * 本章学习要点总结：
 * 
 * 1. 自定义部件的基本概念：
 *    - 继承QWidget或其子类
 *    - 重写paintEvent()进行自定义绘制
 *    - 重写事件处理函数（mouseEvent, keyEvent等）
 *    - 定义自定义信号和槽
 * 
 * 2. 重写paintEvent()：
 *    - 使用QPainter进行绘制
 *    - 可以绘制基本图形（线、矩形、椭圆、多边形等）
 *    - 可以绘制文本
 *    - 可以创建渐变效果
 *    - 启用抗锯齿（setRenderHint）
 * 
 * 3. 事件处理：
 *    - mousePressEvent()：鼠标按下
 *    - mouseReleaseEvent()：鼠标释放
 *    - mouseMoveEvent()：鼠标移动
 *    - keyPressEvent()：键盘按下
 *    - resizeEvent()：大小改变
 *    - 等等...
 * 
 * 4. 自定义属性（Q_PROPERTY）：
 *    - 使用Q_PROPERTY宏声明属性
 *    - 使其可在Qt Designer中使用
 *    - 提供getter、setter和信号
 *    - 支持多种类型（int, double, QColor, QString等）
 * 
 * 5. 自定义信号和槽：
 *    - 定义反映部件状态的信号
 *    - 信号可以有参数
 *    - 使用emit关键字发射信号
 * 
 * 6. 动画效果：
 *    - 使用QTimer创建定时动画
 *    - 通过update()触发重绘
 *    - 使用插值实现平滑过渡
 *    - 动画参数（时长、缓动函数等）
 * 
 * 7. 在Qt Designer中使用自定义部件：
 *    - 使用Q_PLUGIN_METADATA导出插件
 *    - 继承QDesignerCustomWidgetInterface
 *    - 提供图标、组、工具提示等信息
 *    - 编译为插件库
 * 
 * 8. 最佳实践：
 *    - 提供合理的默认大小（sizeHint）
 *    - 支持样式表（QSS）
 *    - 提供丰富的属性控制
 *    - 提供清晰的信号和槽
 *    - 添加详细的文档注释
 *    - 考虑性能优化（避免不必要的重绘）
 * 
 * 9. 绘制技巧：
 *    - 使用抗锯齿使图形更平滑
 *    - 使用渐变创建视觉效果
 *    - 使用透明度创建层次
 *    - 使用缓存避免重复计算
 *    - 合理使用坐标变换
 * 
 * 10. 交互设计：
 *    - 提供视觉反馈（悬停、按下效果）
 *    - 使用合适的光标形状
 *    - 支持键盘导航
 *    - 提供工具提示
 *    - 考虑无障碍访问
 */

#include <QApplication>
#include "CustomWidgetDemo.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("Qt6自定义部件演示");
    
    CustomWidgetDemo demo;
    demo.show();
    
    return app.exec();
}
