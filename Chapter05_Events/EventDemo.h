/**
 * @file EventDemo.h
 * @brief 第5章示例 - 事件处理演示
 * 
 * 本章学习要点：
 * 1. 事件系统概述
 * 2. 鼠标事件（mousePressEvent, mouseReleaseEvent, mouseMoveEvent等）
 * 3. 键盘事件（keyPressEvent, keyReleaseEvent）
 * 4. 焦点事件（focusInEvent, focusOutEvent）
 * 5. 窗口事件（resizeEvent, moveEvent, closeEvent）
 * 6. 绘制事件（paintEvent）
 * 7. 定时器事件（timerEvent）
 * 8. 事件过滤
 * 9. 自定义事件
 */

#ifndef EVENTDEMO_H
#define EVENTDEMO_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QProgressBar>
#include <QSpinBox>
#include <QCheckBox>

#include "ClickLabel.h"
#include "MouseTracker.h"

/**
 * @class EventDemo
 * @brief 演示各种事件处理机制
 */
class EventDemo : public QWidget
{
    Q_OBJECT

public:
    explicit EventDemo(QWidget *parent = nullptr);

protected:
    // 窗口事件
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    // 键盘事件
    void keyPressEvent(QKeyEvent *event) override;

    // 事件过滤器
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void setupUi();
    void setupMouseEventDemo(QWidget *parent);
    void setupKeyboardEventDemo(QWidget *parent);
    void setupWindowEventDemo(QWidget *parent);
    void setupTimerEventDemo(QWidget *parent);
    void setupFocusEventDemo(QWidget *parent);
    void setupEventFilterDemo(QWidget *parent);
    void connectSignals();
    
    // 辅助函数：添加日志
    void addLog(const QString &message);

private slots:
    void onResetClickCounts();
    void onClearMousePath();
    void onTimerStart();
    void onTimerStop();
    void onTimerReset();
    void onFilterCheckboxChanged(int state);
    
    // 定时器槽
    void onTimerTimeout();

private:
    QTabWidget *m_tabWidget;
    
    // 鼠标事件演示部件
    ClickLabel *m_clickLabel;
    MouseTracker *m_mouseTracker;
    QPushButton *m_resetClickBtn;
    QPushButton *m_clearPathBtn;
    
    // 键盘事件演示部件
    QLineEdit *m_keyLineEdit;
    QTextEdit *m_keyLog;
    QPushButton *m_clearKeyBtn;
    
    // 窗口事件演示部件
    QLabel *m_windowInfoLabel;
    
    // 定时器事件演示部件
    QTimer *m_timer;
    int m_timerCount;
    QProgressBar *m_progressBar;
    QLabel *m_timerLabel;
    QSpinBox *m_intervalSpinBox;
    QPushButton *m_timerStartBtn;
    QPushButton *m_timerStopBtn;
    QPushButton *m_timerResetBtn;
    
    // 焦点事件演示部件
    QLineEdit *m_focusEdit1;
    QLineEdit *m_focusEdit2;
    QLabel *m_focusLabel;
    
    // 事件过滤演示部件
    QLineEdit *m_filteredEdit;
    QCheckBox *m_filterCheckbox;
    QLabel *m_filterLabel;
    
    // 事件日志
    QTextEdit *m_eventLog;
};

#endif // EVENTDEMO_H
