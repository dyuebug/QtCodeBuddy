/**
 * @file CircularProgressBar.h
 * @brief 圆形进度条自定义部件
 * 
 * 学习要点：
 * 1. 如何创建动画效果的自定义部件
 * 2. 如何使用定时器更新UI
 * 3. 如何自定义绘制动画效果
 */

#ifndef CIRCULARPROGRESSBAR_H
#define CIRCULARPROGRESSBAR_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>

/**
 * @class CircularProgressBar
 * @brief 一个圆形进度条，支持进度显示和动画效果
 */
class CircularProgressBar : public QWidget
{
    Q_OBJECT
    
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(QColor progressColor READ progressColor WRITE setProgressColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(bool animationEnabled READ animationEnabled WRITE setAnimationEnabled)

public:
    explicit CircularProgressBar(QWidget *parent = nullptr);
    
    /**
     * @brief 获取当前值
     */
    double value() const { return m_value; }
    
    /**
     * @brief 设置当前值
     */
    void setValue(double value);
    
    /**
     * @brief 获取最小值
     */
    double minimum() const { return m_minimum; }
    
    /**
     * @brief 设置最小值
     */
    void setMinimum(double minimum);
    
    /**
     * @brief 获取最大值
     */
    double maximum() const { return m_maximum; }
    
    /**
     * @brief 设置最大值
     */
    void setMaximum(double maximum);
    
    /**
     * @brief 设置范围
     */
    void setRange(double minimum, double maximum);
    
    /**
     * @brief 获取线宽
     */
    int lineWidth() const { return m_lineWidth; }
    
    /**
     * @brief 设置线宽
     */
    void setLineWidth(int width);
    
    /**
     * @brief 获取进度条颜色
     */
    QColor progressColor() const { return m_progressColor; }
    
    /**
     * @brief 设置进度条颜色
     */
    void setProgressColor(const QColor &color);
    
    /**
     * @brief 获取背景颜色
     */
    QColor backgroundColor() const { return m_backgroundColor; }
    
    /**
     * @brief 设置背景颜色
     */
    void setBackgroundColor(const QColor &color);
    
    /**
     * @brief 获取动画是否启用
     */
    bool animationEnabled() const { return m_animationEnabled; }
    
    /**
     * @brief 设置动画是否启用
     */
    void setAnimationEnabled(bool enabled);
    
    /**
     * @brief 获取推荐大小
     */
    QSize sizeHint() const override;
    
    /**
     * @brief 重置进度条
     */
    void reset();

signals:
    /**
     * @brief 值改变信号
     */
    void valueChanged(double value);
    
    /**
     * @brief 达到最大值信号
     */
    void finished();

public slots:
    /**
     * @brief 启动动画
     */
    void startAnimation();
    
    /**
     * @brief 停止动画
     */
    void stopAnimation();

protected:
    /**
     * @brief 重写绘制事件
     */
    void paintEvent(QPaintEvent *event) override;

private slots:
    /**
     * @brief 动画更新槽函数
     */
    void updateAnimation();

private:
    /**
     * @brief 绘制进度条
     */
    void drawProgressBar(QPainter *painter);
    
    /**
     * @brief 绘制文本
     */
    void drawText(QPainter *painter);
    
    /**
     * @brief 计算角度
     */
    double calculateAngle(double value) const;

private:
    double m_value;               ///< 当前值
    double m_minimum;             ///< 最小值
    double m_maximum;             ///< 最大值
    int m_lineWidth;              ///< 线宽
    QColor m_progressColor;       ///< 进度条颜色
    QColor m_backgroundColor;     ///< 背景颜色
    bool m_animationEnabled;      ///< 是否启用动画
    
    QTimer *m_animationTimer;     ///< 动画定时器
    double m_animationValue;      ///< 动画当前值
    double m_animationTarget;     ///< 动画目标值
    int m_animationStep;          ///< 动画步进方向
};

#endif // CIRCULARPROGRESSBAR_H
