/**
 * @file Counter.h
 * @brief 自定义计数器类 - 用于演示自定义信号和槽
 * 
 * 学习要点：
 * 1. 如何定义自定义信号
 * 2. 如何发射信号
 * 3. 如何定义自定义槽
 */

#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QString>

/**
 * @class Counter
 * @brief 一个简单的计数器类，演示自定义信号和槽
 * 
 * 该类展示了：
 * - 定义自定义信号
 * - 发射信号
 * - 定义公共槽函数
 * - 定义私有槽函数
 */
class Counter : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象
     */
    explicit Counter(QObject *parent = nullptr);
    
    /**
     * @brief 获取当前计数值
     * @return 当前的计数值
     */
    int value() const { return m_value; }
    
    /**
     * @brief 公共槽函数 - 设置计数值
     * @param value 新的计数值
     * 
     * 这是一个公共槽，可以被外部对象连接
     */
    void setValue(int value);

public slots:
    /**
     * @brief 公共槽函数 - 增加计数值
     * @param delta 增加的量，默认为1
     */
    void increment(int delta = 1);
    
    /**
     * @brief 公共槽函数 - 减少计数值
     * @param delta 减少的量，默认为1
     */
    void decrement(int delta = 1);

signals:
    /**
     * @brief 信号 - 计数值改变
     * @param newValue 新的计数值
     * 
     * 当计数值改变时发射此信号
     */
    void valueChanged(int newValue);
    
    /**
     * @brief 信号 - 计数值达到特定值
     * @param value 达到的值
     * 
     * 当计数值达到特定值时发射此信号
     */
    void valueReached(int value);
    
    /**
     * @brief 信号 - 计数值超过阈值
     * @param value 当前值
     * @param threshold 阈值
     */
    void exceededThreshold(int value, int threshold);

private slots:
    /**
     * @brief 私有槽函数 - 检查是否超过阈值
     */
    void checkThreshold();

private:
    int m_value;        ///< 当前计数值
    int m_threshold;    ///< 阈值
};

#endif // COUNTER_H
