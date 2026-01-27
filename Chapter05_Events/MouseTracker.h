/**
 * @file MouseTracker.h
 * @brief 鼠标跟踪部件 - 演示鼠标移动事件
 * 
 * 学习要点：
 * 1. 如何跟踪鼠标位置
 * 2. 如何处理鼠标移动事件
 * 3. 自定义绘制
 */

#ifndef MOUSETRACKER_H
#define MOUSETRACKER_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QVector>
#include <QTimer>

/**
 * @class MouseTracker
 * @brief 跟踪鼠标移动并显示轨迹
 */
class MouseTracker : public QWidget
{
    Q_OBJECT

public:
    explicit MouseTracker(QWidget *parent = nullptr);
    
    void clearPath();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateInfo();

private:
    QVector<QPoint> m_mousePath;   ///< 鼠标轨迹点
    QPoint m_currentPos;           ///< 当前鼠标位置
    bool m_tracking;               ///< 是否正在跟踪
    QTimer *m_updateTimer;         ///< 定时器，用于更新信息
};

#endif // MOUSETRACKER_H
