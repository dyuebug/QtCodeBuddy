/**
 * @file ColorPickerWidget.cpp
 * @brief 颜色选择器自定义部件实现
 */

#include "ColorPickerWidget.h"
#include <cmath>
#include <QPainterPath>

ColorPickerWidget::ColorPickerWidget(QWidget *parent)
    : QWidget(parent)
    , m_selectedColor(Qt::red)
    , m_hoverColor(Qt::transparent)
    , m_colorCount(24)
    , m_innerRadius(20)
    , m_outerRadius(80)
    , m_center()
    , m_isHovered(false)
    , m_isPressed(false)
{
    setMouseTracking(true);
    setMinimumSize(200, 200);
    
    // 设置默认选中的颜色
    m_selectedColor = Qt::red;
}

/**
 * @brief 获取推荐大小
 */
QSize ColorPickerWidget::sizeHint() const
{
    return QSize(m_outerRadius * 2 + 20, m_outerRadius * 2 + 20);
}

/**
 * @brief 设置选中的颜色
 */
void ColorPickerWidget::setSelectedColor(const QColor &color)
{
    if (m_selectedColor != color) {
        m_selectedColor = color;
        update();
        emit colorChanged(color);
    }
}

/**
 * @brief 设置颜色数量
 */
void ColorPickerWidget::setColorCount(int count)
{
    if (count > 0 && count <= 360) {
        m_colorCount = count;
        update();
    }
}

/**
 * @brief 设置内半径
 */
void ColorPickerWidget::setInnerRadius(int radius)
{
    if (radius >= 0 && radius < m_outerRadius) {
        m_innerRadius = radius;
        update();
    }
}

/**
 * @brief 设置外半径
 */
void ColorPickerWidget::setOuterRadius(int radius)
{
    if (radius > m_innerRadius) {
        m_outerRadius = radius;
        updateGeometry();
        update();
    }
}

/**
 * @brief 绘制事件
 */
void ColorPickerWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    m_center = rect().center();
    
    // 绘制色环
    for (int i = 0; i < m_colorCount; ++i) {
        float angle1 = 2.0 * M_PI * i / m_colorCount;
        float angle2 = 2.0 * M_PI * (i + 1) / m_colorCount;
        
        // 创建渐变
        QConicalGradient gradient(m_center, 0);
        
        QColor color1 = QColor::fromHsv(i * 360 / m_colorCount, 255, 255);
        QColor color2 = QColor::fromHsv((i + 1) * 360 / m_colorCount, 255, 255);
        
        QPainterPath path;
        path.moveTo(m_center.x() + m_innerRadius * cos(angle1), 
                    m_center.y() + m_innerRadius * sin(angle1));
        path.arcTo(m_center.x() - m_outerRadius, m_center.y() - m_outerRadius, 
                   m_outerRadius * 2, m_outerRadius * 2, 
                   i * 360.0 / m_colorCount, 360.0 / m_colorCount);
        path.lineTo(m_center.x() + m_innerRadius * cos(angle2), 
                    m_center.y() + m_innerRadius * sin(angle2));
        path.arcTo(m_center.x() - m_innerRadius, m_center.y() - m_innerRadius, 
                   m_innerRadius * 2, m_innerRadius * 2, 
                   (i + 1) * 360.0 / m_colorCount, -360.0 / m_colorCount);
        path.closeSubpath();
        
        QRadialGradient radialGradient(m_center, m_outerRadius);
        radialGradient.setColorAt(0, color1);
        radialGradient.setColorAt(1, color2);
        
        painter.fillPath(path, radialGradient);
        
        // 绘制边框
        painter.setPen(QPen(Qt::black, 1));
        painter.drawPath(path);
    }
    
    // 绘制中心圆（显示当前选中的颜色）
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_selectedColor);
    painter.drawEllipse(m_center, m_innerRadius - 2, m_innerRadius - 2);
    
    // 绘制选中颜色的边框
    painter.setPen(QPen(Qt::black, 3));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(m_center, m_innerRadius - 2, m_innerRadius - 2);
    
    // 如果鼠标悬停，显示悬停颜色
    if (m_isHovered && m_hoverColor.isValid()) {
        painter.setPen(QPen(Qt::white, 2));
        painter.setBrush(m_hoverColor);
        painter.drawEllipse(m_center, m_innerRadius + 5, m_innerRadius + 5);
    }
}

/**
 * @brief 鼠标按下事件
 */
void ColorPickerWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isPressed = true;
        QColor color = colorFromPosition(event->pos());
        if (color.isValid()) {
            setSelectedColor(color);
            emit colorSelected(color);
        }
    }
    
    QWidget::mousePressEvent(event);
}

/**
 * @brief 鼠标移动事件
 */
void ColorPickerWidget::mouseMoveEvent(QMouseEvent *event)
{
    updateHoverColor(event->pos());
    QWidget::mouseMoveEvent(event);
}

/**
 * @brief 鼠标释放事件
 */
void ColorPickerWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    QWidget::mouseReleaseEvent(event);
}

/**
 * @brief 进入事件
 */
void ColorPickerWidget::enterEvent(QEnterEvent *event)
{
    Q_UNUSED(event);
    m_isHovered = true;
    setCursor(Qt::CrossCursor);
    update();
}

/**
 * @brief 离开事件
 */
void ColorPickerWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_isHovered = false;
    m_hoverColor = Qt::transparent;
    setCursor(Qt::ArrowCursor);
    update();
}

/**
 * @brief 根据位置获取颜色
 */
QColor ColorPickerWidget::colorFromPosition(const QPoint &pos) const
{
    QPoint delta = pos - m_center;
    int distance = sqrt(delta.x() * delta.x() + delta.y() * delta.y());
    
    // 检查是否在色环范围内
    if (distance < m_innerRadius || distance > m_outerRadius) {
        return QColor();  // 无效颜色
    }
    
    // 计算角度
    float angle = atan2(delta.y(), delta.x());
    if (angle < 0) {
        angle += 2 * M_PI;
    }
    
    // 计算色相
    int hue = (angle * 180 / M_PI) + 90;  // +90度偏移，使红色在顶部
    if (hue > 360) {
        hue -= 360;
    }
    
    // 计算饱和度（基于半径）
    int saturation = 255;
    
    // 返回颜色
    return QColor::fromHsv(hue, saturation, 255);
}

/**
 * @brief 更新悬停颜色
 */
void ColorPickerWidget::updateHoverColor(const QPoint &pos)
{
    QColor color = colorFromPosition(pos);
    if (color.isValid()) {
        m_hoverColor = color;
        update();
    }
}
