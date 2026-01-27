/**
 * @file Counter.cpp
 * @brief 自定义计数器类实现
 */

#include "Counter.h"

Counter::Counter(QObject *parent)
    : QObject(parent)
    , m_value(0)
    , m_threshold(10)
{
}

/**
 * @brief 设置计数值
 * @param value 新的计数值
 */
void Counter::setValue(int value)
{
    if (m_value != value) {
        m_value = value;
        emit valueChanged(m_value);  // 发射信号，通知值已改变
        
        // 检查是否达到特定值（例如5的倍数）
        if (m_value % 5 == 0 && m_value != 0) {
            emit valueReached(m_value);
        }
        
        checkThreshold();  // 检查是否超过阈值
    }
}

/**
 * @brief 增加计数值
 * @param delta 增加的量
 */
void Counter::increment(int delta)
{
    setValue(m_value + delta);
}

/**
 * @brief 减少计数值
 * @param delta 减少的量
 */
void Counter::decrement(int delta)
{
    setValue(m_value - delta);
}

/**
 * @brief 检查是否超过阈值
 */
void Counter::checkThreshold()
{
    if (m_value > m_threshold) {
        emit exceededThreshold(m_value, m_threshold);
    }
}
