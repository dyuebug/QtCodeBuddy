/**
 * @file SignalsSlotsDemo.h
 * @brief 第4章示例 - 信号和槽机制演示
 * 
 * 本章学习要点：
 * 1. 信号和槽的基本概念
 * 2. Qt6的connect语法（函数指针语法）
 * 3. 信号的发射
 * 4. 槽函数的定义和使用
 * 5. 自定义信号和槽
 * 6. 信号和槽的参数传递
 * 7. Lambda表达式作为槽
 * 8. 信号和槽的断开连接
 * 9. 信号连接多个槽
 * 10. 槽连接多个信号
 */

#ifndef SIGNALSSLOTSDEMO_H
#define SIGNALSSLOTSDEMO_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QSlider>
#include <QTextEdit>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTabWidget>
#include <QCheckBox>

#include "Counter.h"

/**
 * @class SignalsSlotsDemo
 * @brief 演示信号和槽机制的各种用法
 */
class SignalsSlotsDemo : public QWidget
{
    Q_OBJECT

public:
    explicit SignalsSlotsDemo(QWidget *parent = nullptr);

private:
    void setupUi();
    void setupBasicDemo(QWidget *parent);
    void setupParameterDemo(QWidget *parent);
    void setupLambdaDemo(QWidget *parent);
    void setupCustomSignalDemo(QWidget *parent);
    void setupMultipleDemo(QWidget *parent);
    void connectSignals();

    // 辅助函数：添加日志
    void addLog(const QString &message);

public slots:
    // 基本演示槽函数
    void onBasicButtonClicked();
    void onCheckboxStateChanged(Qt::CheckState state);

    // 参数传递演示槽函数
    void onSpinBoxChanged(int value);
    void onSliderChanged(int value);
    void onTextChanged(const QString &text);
    void onTextChanged2(const QString &text);

    // 自定义信号演示槽函数
    void onCounterValueChanged(int value);
    void onCounterValueReached(int value);
    void onCounterExceededThreshold(int value, int threshold);

    // 多重连接演示槽函数
    void onSender1Clicked();
    void onSender2Clicked();
    void onSender3Clicked();
    void onCommonSlotClicked();  // 公共槽函数，多个发送者连接到此槽

private:
    QTabWidget *m_tabWidget;
    
    // 基本演示部件
    QPushButton *m_basicButton;
    QPushButton *m_disconnectBtn;
    QCheckBox *m_checkbox;
    QLabel *m_basicLabel;
    QTextEdit *m_logTextEdit;
    
    // 参数传递演示部件
    QSpinBox *m_spinBox;
    QSlider *m_slider;
    QLineEdit *m_lineEdit1;
    QLineEdit *m_lineEdit2;
    QLabel *m_paramLabel;
    
    // Lambda演示部件
    QPushButton *m_lambdaBtn1;
    QPushButton *m_lambdaBtn2;
    QLabel *m_lambdaLabel;
    
    // 自定义信号演示部件
    Counter *m_counter;
    QPushButton *m_incBtn;
    QPushButton *m_decBtn;
    QPushButton *m_setBtn;
    QSpinBox *m_counterSpinBox;
    QLabel *m_counterLabel;
    
    // 多重连接演示部件
    QPushButton *m_sender1;
    QPushButton *m_sender2;
    QPushButton *m_sender3;
    QPushButton *m_commonBtn;
    QLabel *m_multiLabel;
    
    // 用于记录点击次数
    int m_clickCount;
};

#endif // SIGNALSSLOTSDEMO_H
