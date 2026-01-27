/**
 * @file ClickLabel.h
 * @brief 可点击的标签部件 - 演示鼠标事件处理
 * 
 * 学习要点：
 * 1. 如何重写鼠标事件处理函数
 * 2. 如何跟踪鼠标点击次数
 * 3. 自定义绘制
 */

#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

/**
 * @class ClickLabel
 * @brief 一个可点击的标签，支持左键和右键点击
 * 
 * 通过重写鼠标事件处理函数实现
 */
class ClickLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickLabel(const QString &text, QWidget *parent = nullptr);
    
    int leftClickCount() const { return m_leftClickCount; }
    int rightClickCount() const { return m_rightClickCount; }
    
    void resetCounts();

signals:
    void leftClicked();
    void rightClicked();
    void doubleClicked();

protected:
    /**
     * @brief 重写鼠标按下事件
     * @param event 鼠标事件对象
     */
    void mousePressEvent(QMouseEvent *event) override;
    
    /**
     * @brief 重写鼠标双击事件
     * @param event 鼠标事件对象
     */
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    
    /**
     * @brief 重写鼠标释放事件
     * @param event 鼠标事件对象
     */
    void mouseReleaseEvent(QMouseEvent *event) override;
    
    /**
     * @brief 重写鼠标进入事件
     * @param event 事件对象
     */
    void enterEvent(QEnterEvent *event) override;
    
    /**
     * @brief 重写鼠标离开事件
     * @param event 事件对象
     */
    void leaveEvent(QEvent *event) override;

private:
    int m_leftClickCount;   ///< 左键点击次数
    int m_rightClickCount;   ///< 右键点击次数
    bool m_isPressed;        ///< 鼠标是否按下
};

#endif // CLICKLABEL_H
