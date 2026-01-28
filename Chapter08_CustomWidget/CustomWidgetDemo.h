/**
 * @file CustomWidgetDemo.h
 * @brief 第8章示例 - 自定义部件演示
 * 
 * 本章学习要点：
 * 1. 自定义部件的基本概念
 * 2. 重写绘制事件（paintEvent）
 * 3. 重写鼠标和键盘事件
 * 4. 自定义属性的创建和使用
 * 5. 自定义信号和槽
 * 6. 样式表（QSS）的应用
 * 7. 动画效果的实现
 * 8. 在Qt Designer中使用自定义部件
 */

#ifndef CUSTOMWIDGETDEMO_H
#define CUSTOMWIDGETDEMO_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTextEdit>

#include "ColorPickerWidget.h"
#include "CircularProgressBar.h"

/**
 * @class CustomWidgetDemo
 * @brief 演示自定义部件的使用
 */
class CustomWidgetDemo : public QWidget
{
    Q_OBJECT

public:
    explicit CustomWidgetDemo(QWidget *parent = nullptr);

private:
    void setupUi();
    void setupColorPickerDemo(QWidget *parent);
    void setupProgressBarDemo(QWidget *parent);
    void setupCustomPropertiesDemo(QWidget *parent);
    void connectSignals();
    
    // 辅助函数：添加日志
    void addLog(const QString &message);

private slots:
    void onColorChanged(const QColor &color);
    void onColorSelected(const QColor &color);
    void onProgressValueChanged(double value);
    void onProgressFinished();
    void onStartProgressAnimation();
    void onStopProgressAnimation();
    void onResetProgress();
    void onProgressValueSliderChanged(int value);
    void onProgressRangeChanged();
    void onAnimationEnabledChanged(Qt::CheckState state);
    void onCustomPropertiesChanged();

private:
    QTabWidget *m_tabWidget;
    
    // 颜色选择器演示部件
    ColorPickerWidget *m_colorPicker;
    QLabel *m_colorPreview;
    QLabel *m_colorInfoLabel;
    QPushButton *m_randomColorBtn;
    
    // 进度条演示部件
    CircularProgressBar *m_progressBar;
    QSlider *m_progressSlider;
    QSpinBox *m_minSpinBox;
    QSpinBox *m_maxSpinBox;
    QSpinBox *m_valueSpinBox;
    QCheckBox *m_animationCheckBox;
    QPushButton *m_startAnimationBtn;
    QPushButton *m_stopAnimationBtn;
    QPushButton *m_resetProgressBtn;
    QLabel *m_progressInfoLabel;
    
    // 自定义属性演示部件
    ColorPickerWidget *m_propertiesColorPicker;
    QSpinBox *m_colorCountSpin;
    QSpinBox *m_innerRadiusSpin;
    QSpinBox *m_outerRadiusSpin;
    QLabel *m_propertiesInfoLabel;
    
    // 日志输出
    QTextEdit *m_logTextEdit;
};

#endif // CUSTOMWIDGETDEMO_H
