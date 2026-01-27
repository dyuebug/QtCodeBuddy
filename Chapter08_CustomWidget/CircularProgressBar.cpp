/**
 * @file CircularProgressBar.cpp
 * @brief 圆形进度条自定义部件实现
 */

#include "CircularProgressBar.h"
#include <cmath>
#include <QDebug>

CircularProgressBar::CircularProgressBar(QWidget *parent)
    : QWidget(parent)
    , m_value(0.0)
    , m_minimum(0.0)
    , m_maximum(100.0)
    , m_lineWidth(8)
    , m_progressColor(0, 150, 255)  // 蓝色
    , m_backgroundColor(220, 220, 220)  // 浅灰色
    , m_animationEnabled(false)
    , m_animationTimer(new QTimer(this))
    , m_animationValue(0.0)
    , m_animationTarget(0.0)
    , m_animationStep(1)
{
    setMinimumSize(120, 120);
    
    connect(m_animationTimer, &QTimer::timeout, this, &CircularProgressBar::updateAnimation);
}

/**
 * @brief 获取推荐大小
 */
QSize CircularProgressBar::sizeHint() const
{
    return QSize(150, 150);
}

/**
 * @brief 设置值
 */
void CircularProgressBar::setValue(double value)
{
    if (value < m_minimum) {
        value = m_minimum;
    } else if (value > m_maximum) {
        value = m_maximum;
    }
    
    if (m_value != value) {
        m_value = value;
        
        if (m_animationEnabled) {
            // 启动动画
            m_animationTarget = value;
            m_animationTimer->start(30);  // 30ms更新一次
        } else {
            m_animationValue = value;
        }
        
        update();
        emit valueChanged(value);
        
        if (value == m_maximum) {
            emit finished();
        }
    }
}

/**
 * @brief 设置最小值
 */
void CircularProgressBar::setMinimum(double minimum)
{
    if (minimum < m_maximum) {
        m_minimum = minimum;
        
        if (m_value < m_minimum) {
            setValue(m_minimum);
        }
        
        update();
    }
}

/**
 * @brief 设置最大值
 */
void CircularProgressBar::setMaximum(double maximum)
{
    if (maximum > m_minimum) {
        m_maximum = maximum;
        
        if (m_value > m_maximum) {
            setValue(m_maximum);
        }
        
        update();
    }
}

/**
 * @brief 设置范围
 */
void CircularProgressBar::setRange(double minimum, double maximum)
{
    if (minimum < maximum) {
        m_minimum = minimum;
        m_maximum = maximum;
        
        if (m_value < m_minimum || m_value > m_maximum) {
            setValue(m_minimum);
        }
        
        update();
    }
}

/**
 * @brief 设置线宽
 */
void CircularProgressBar::setLineWidth(int width)
{
    if (width > 0 && width <= 20) {
        m_lineWidth = width;
        update();
    }
}

/**
 * @brief 设置进度条颜色
 */
void CircularProgressBar::setProgressColor(const QColor &color)
{
    m_progressColor = color;
    update();
}

/**
 * @brief 设置背景颜色
 */
void CircularProgressBar::setBackgroundColor(const QColor &color)
{
    m_backgroundColor = color;
    update();
}

/**
 * @brief 设置动画启用状态
 */
void CircularProgressBar::setAnimationEnabled(bool enabled)
{
    m_animationEnabled = enabled;
    
    if (!enabled) {
        m_animationTimer->stop();
        m_animationValue = m_value;
    }
}

/**
 * @brief 重置进度条
 */
void CircularProgressBar::reset()
{
    setValue(m_minimum);
    m_animationValue = m_minimum;
    m_animationTarget = m_minimum;
    update();
}

/**
 * @brief 启动动画
 */
void CircularProgressBar::startAnimation()
{
    if (m_animationEnabled) {
        m_animationTarget = m_maximum;
        m_animationTimer->start(30);
    }
}

/**
 * @brief 停止动画
 */
void CircularProgressBar::stopAnimation()
{
    m_animationTimer->stop();
}

/**
 * @brief 更新动画
 */
void CircularProgressBar::updateAnimation()
{
    const double step = (m_maximum - m_minimum) / 100.0;
    
    if (m_animationValue < m_animationTarget) {
        m_animationValue += step;
        if (m_animationValue > m_animationTarget) {
            m_animationValue = m_animationTarget;
            m_animationTimer->stop();
        }
    } else if (m_animationValue > m_animationTarget) {
        m_animationValue -= step;
        if (m_animationValue < m_animationTarget) {
            m_animationValue = m_animationTarget;
            m_animationTimer->stop();
        }
    } else {
        m_animationTimer->stop();
    }
    
    update();
}

/**
 * @brief 计算角度
 */
double CircularProgressBar::calculateAngle(double value) const
{
    double normalizedValue = (value - m_minimum) / (m_maximum - m_minimum);
    return normalizedValue * 360.0;
}

/**
 * @brief 绘制事件
 */
void CircularProgressBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    drawProgressBar(&painter);
    drawText(&painter);
}

/**
 * @brief 绘制进度条
 */
void CircularProgressBar::drawProgressBar(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int size = qMin(width, height);
    
    int centerX = width / 2;
    int centerY = height / 2;
    int radius = (size / 2) - m_lineWidth;
    
    // 绘制背景圆
    painter->setPen(QPen(m_backgroundColor, m_lineWidth, Qt::SolidLine, Qt::RoundCap));
    painter->drawArc(centerX - radius, centerY - radius, radius * 2, radius * 2, 0, 360 * 16);
    
    // 绘制进度圆
    if (m_animationEnabled) {
        double angle = calculateAngle(m_animationValue);
        painter->setPen(QPen(m_progressColor, m_lineWidth, Qt::SolidLine, Qt::RoundCap));
        painter->drawArc(centerX - radius, centerY - radius, radius * 2, radius * 2, 90 * 16, -angle * 16);
    } else {
        double angle = calculateAngle(m_value);
        painter->setPen(QPen(m_progressColor, m_lineWidth, Qt::SolidLine, Qt::RoundCap));
        painter->drawArc(centerX - radius, centerY - radius, radius * 2, radius * 2, 90 * 16, -angle * 16);
    }
}

/**
 * @brief 绘制文本
 */
void CircularProgressBar::drawText(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int centerX = width / 2;
    int centerY = height / 2;
    
    // 绘制百分比文本
    painter->setPen(Qt::black);
    
    double displayValue = m_animationEnabled ? m_animationValue : m_value;
    double percentage = (displayValue - m_minimum) / (m_maximum - m_minimum) * 100.0;
    
    // 根据进度调整字体大小
    int fontSize = 16;
    if (width > 150) {
        fontSize = 24;
    } else if (width > 100) {
        fontSize = 20;
    }
    
    QFont font("Arial", fontSize, QFont::Bold);
    painter->setFont(font);
    painter->drawText(QRect(0, 0, width, centerY), Qt::AlignCenter, 
                      QString("%1%").arg(qRound(percentage)));
    
    // 绘制数值文本（小字体）
    font.setPointSize(fontSize - 6);
    painter->setFont(font);
    painter->drawText(QRect(0, centerY, width, centerY), Qt::AlignCenter, 
                      QString("%1 / %2").arg(displayValue, 0, 'f', 0).arg(m_maximum, 0, 'f', 0));
}
