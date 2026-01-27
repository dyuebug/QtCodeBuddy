/**
 * @file MouseTracker.cpp
 * @brief 鼠标跟踪部件实现
 */

#include "MouseTracker.h"
#include <QDebug>

MouseTracker::MouseTracker(QWidget *parent)
    : QWidget(parent)
    , m_tracking(false)
    , m_updateTimer(new QTimer(this))
{
    setMouseTracking(true);  // 启用鼠标跟踪（即使没有按键也能收到移动事件）
    setMinimumSize(400, 300);
    setStyleSheet("background-color: white; border: 2px solid #333;");
    
    // 设置定时器，用于定时更新显示
    connect(m_updateTimer, &QTimer::timeout, this, &MouseTracker::updateInfo);
    m_updateTimer->start(100);  // 每100毫秒更新一次
}

/**
 * @brief 清除轨迹
 */
void MouseTracker::clearPath()
{
    m_mousePath.clear();
    update();  // 触发重绘
}

/**
 * @brief 鼠标移动事件
 */
void MouseTracker::mouseMoveEvent(QMouseEvent *event)
{
    if (m_tracking) {
        m_currentPos = event->pos();
        m_mousePath.append(m_currentPos);
        
        // 限制轨迹点的数量，避免内存无限增长
        if (m_mousePath.size() > 1000) {
            m_mousePath.removeFirst();
        }
        
        update();  // 触发重绘
    }
    
    QWidget::mouseMoveEvent(event);
}

/**
 * @brief 鼠标按下事件
 */
void MouseTracker::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_tracking = !m_tracking;  // 切换跟踪状态
        
        if (m_tracking) {
            setCursor(Qt::CrossCursor);  // 设置光标为十字
            m_mousePath.clear();
            m_currentPos = event->pos();
            m_mousePath.append(m_currentPos);
        } else {
            setCursor(Qt::ArrowCursor);  // 恢复默认光标
        }
        
        update();
    }
    
    QWidget::mousePressEvent(event);
}

/**
 * @brief 绘制事件
 */
void MouseTracker::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 启用抗锯齿
    
    // 绘制轨迹
    if (!m_mousePath.isEmpty()) {
        // 绘制轨迹线
        painter.setPen(QPen(QColor(255, 100, 100), 2));
        painter.drawPolyline(m_mousePath);
        
        // 绘制当前位置
        painter.setBrush(QBrush(QColor(255, 0, 0)));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(m_currentPos, 6, 6);
    }
    
    // 绘制背景网格
    painter.setPen(QPen(QColor(200, 200, 200), 1, Qt::DotLine));
    for (int x = 0; x < width(); x += 50) {
        painter.drawLine(x, 0, x, height());
    }
    for (int y = 0; y < height(); y += 50) {
        painter.drawLine(0, y, width(), y);
    }
    
    // 绘制信息文本
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12));
    
    QString status = m_tracking ? "跟踪中" : "停止跟踪";
    painter.drawText(10, 25, QString("状态: %1").arg(status));
    painter.drawText(10, 45, QString("位置: (%1, %2)").arg(m_currentPos.x()).arg(m_currentPos.y()));
    painter.drawText(10, 65, QString("轨迹点数: %1").arg(m_mousePath.size()));
    painter.drawText(10, 85, QString("点击开始/停止跟踪"));
}

/**
 * @brief 窗口大小改变事件
 */
void MouseTracker::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    update();  // 触发重绘
}

/**
 * @brief 更新信息（定时器槽函数）
 */
void MouseTracker::updateInfo()
{
    // 如果需要定期更新某些状态，可以在这里实现
    // 目前由paintEvent负责显示信息
}
