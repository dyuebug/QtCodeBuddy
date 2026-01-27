/**
 * @file ColorPickerWidget.h
 * @brief 颜色选择器自定义部件
 * 
 * 学习要点：
 * 1. 如何创建自定义绘制部件
 * 2. 如何处理鼠标事件
 * 3. 如何发射自定义信号
 * 4. 如何管理自定义属性
 */

#ifndef COLORPICKERWIDGET_H
#define COLORPICKERWIDGET_H

#include <QWidget>
#include <QColor>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

/**
 * @class ColorPickerWidget
 * @brief 一个圆形颜色选择器，显示色环并允许选择颜色
 */
class ColorPickerWidget : public QWidget
{
    Q_OBJECT
    
    // 声明属性，使其可以在Qt Designer中使用
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor NOTIFY colorChanged)
    Q_PROPERTY(int colorCount READ colorCount WRITE setColorCount)
    Q_PROPERTY(int innerRadius READ innerRadius WRITE setInnerRadius)
    Q_PROPERTY(int outerRadius READ outerRadius WRITE setOuterRadius)

public:
    explicit ColorPickerWidget(QWidget *parent = nullptr);
    
    /**
     * @brief 获取选中的颜色
     */
    QColor selectedColor() const { return m_selectedColor; }
    
    /**
     * @brief 设置选中的颜色
     */
    void setSelectedColor(const QColor &color);
    
    /**
     * @brief 获取颜色数量
     */
    int colorCount() const { return m_colorCount; }
    
    /**
     * @brief 设置颜色数量
     */
    void setColorCount(int count);
    
    /**
     * @brief 获取内半径
     */
    int innerRadius() const { return m_innerRadius; }
    
    /**
     * @brief 设置内半径
     */
    void setInnerRadius(int radius);
    
    /**
     * @brief 获取外半径
     */
    int outerRadius() const { return m_outerRadius; }
    
    /**
     * @brief 设置外半径
     */
    void setOuterRadius(int radius);
    
    /**
     * @brief 获取推荐大小
     */
    QSize sizeHint() const override;

signals:
    /**
     * @brief 颜色改变信号
     */
    void colorChanged(const QColor &color);
    
    /**
     * @brief 颜色选择信号（用户点击时发射）
     */
    void colorSelected(const QColor &color);

protected:
    /**
     * @brief 重写绘制事件
     */
    void paintEvent(QPaintEvent *event) override;
    
    /**
     * @brief 重写鼠标按下事件
     */
    void mousePressEvent(QMouseEvent *event) override;
    
    /**
     * @brief 重写鼠标移动事件
     */
    void mouseMoveEvent(QMouseEvent *event) override;
    
    /**
     * @brief 重写鼠标释放事件
     */
    void mouseReleaseEvent(QMouseEvent *event) override;
    
    /**
     * @brief 重写进入事件
     */
    void enterEvent(QEnterEvent *event) override;
    
    /**
     * @brief 重写离开事件
     */
    void leaveEvent(QEvent *event) override;

private:
    /**
     * @brief 根据角度和半径计算颜色
     */
    QColor getColorAtPosition(int angle, float normalizedRadius) const;
    
    /**
     * @brief 根据点击位置计算颜色
     */
    QColor colorFromPosition(const QPoint &pos) const;
    
    /**
     * @brief 更新鼠标位置的颜色
     */
    void updateHoverColor(const QPoint &pos);

private:
    QColor m_selectedColor;       ///< 当前选中的颜色
    QColor m_hoverColor;          ///< 鼠标悬停的颜色
    int m_colorCount;             ///< 颜色数量
    int m_innerRadius;            ///< 内圆半径
    int m_outerRadius;            ///< 外圆半径
    QPoint m_center;              ///< 中心点
    bool m_isHovered;             ///< 是否鼠标悬停
    bool m_isPressed;             ///< 是否按下鼠标
};

#endif // COLORPICKERWIDGET_H
