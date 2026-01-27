/**
 * @file ClickLabel.cpp
 * @brief 可点击标签实现
 */

#include "ClickLabel.h"

ClickLabel::ClickLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent)
    , m_leftClickCount(0)
    , m_rightClickCount(0)
    , m_isPressed(false)
{
    // 设置标签样式
    setAlignment(Qt::AlignCenter);
    setStyleSheet(
        "QLabel {"
        "    background-color: #e0e0e0;"
        "    border: 2px solid #999;"
        "    border-radius: 10px;"
        "    padding: 20px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
    );
    setMinimumSize(200, 100);
}

/**
 * @brief 重置点击次数
 */
void ClickLabel::resetCounts()
{
    m_leftClickCount = 0;
    m_rightClickCount = 0;
    update();  // 触发重绘
}

/**
 * @brief 鼠标按下事件处理
 */
void ClickLabel::mousePressEvent(QMouseEvent *event)
{
    m_isPressed = true;
    
    if (event->button() == Qt::LeftButton) {
        m_leftClickCount++;
        emit leftClicked();
        
        // 更新文本显示
        setText(QString("左键点击: %1\n右键点击: %2").arg(m_leftClickCount).arg(m_rightClickCount));
        
        // 改变样式
        setStyleSheet(
            "QLabel {"
            "    background-color: #ffcccb;"
            "    border: 2px solid #ff0000;"
            "    border-radius: 10px;"
            "    padding: 20px;"
            "    font-size: 16px;"
            "    font-weight: bold;"
            "}"
        );
        
    } else if (event->button() == Qt::RightButton) {
        m_rightClickCount++;
        emit rightClicked();
        
        setText(QString("左键点击: %1\n右键点击: %2").arg(m_leftClickCount).arg(m_rightClickCount));
        
        setStyleSheet(
            "QLabel {"
            "    background-color: #87ceeb;"
            "    border: 2px solid #0000ff;"
            "    border-radius: 10px;"
            "    padding: 20px;"
            "    font-size: 16px;"
            "    font-weight: bold;"
            "}"
        );
    }
    
    // 调用基类的事件处理（可选）
    // QLabel::mousePressEvent(event);
}

/**
 * @brief 鼠标双击事件处理
 */
void ClickLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit doubleClicked();
        
        setText(QString("双击了！\n左键点击: %1\n右键点击: %2")
            .arg(m_leftClickCount).arg(m_rightClickCount));
        
        setStyleSheet(
            "QLabel {"
            "    background-color: #90ee90;"
            "    border: 2px solid #008000;"
            "    border-radius: 10px;"
            "    padding: 20px;"
            "    font-size: 16px;"
            "    font-weight: bold;"
            "}"
        );
    }
}

/**
 * @brief 鼠标释放事件处理
 */
void ClickLabel::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    
    // 恢复默认样式
    setStyleSheet(
        "QLabel {"
        "    background-color: #e0e0e0;"
        "    border: 2px solid #999;"
        "    border-radius: 10px;"
        "    padding: 20px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
    );
    
    QLabel::mouseReleaseEvent(event);
}

/**
 * @brief 鼠标进入事件处理
 */
void ClickLabel::enterEvent(QEnterEvent *event)
{
    setStyleSheet(
        "QLabel {"
        "    background-color: #fffacd;"
        "    border: 2px solid #ffd700;"
        "    border-radius: 10px;"
        "    padding: 20px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
    );
    
    QLabel::enterEvent(event);
}

/**
 * @brief 鼠标离开事件处理
 */
void ClickLabel::leaveEvent(QEvent *event)
{
    if (!m_isPressed) {
        setStyleSheet(
            "QLabel {"
            "    background-color: #e0e0e0;"
            "    border: 2px solid #999;"
            "    border-radius: 10px;"
            "    padding: 20px;"
            "    font-size: 16px;"
            "    font-weight: bold;"
            "}"
        );
    }
    
    QLabel::leaveEvent(event);
}
