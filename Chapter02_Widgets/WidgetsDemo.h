/**
 * @file WidgetsDemo.h
 * @brief 第2章示例 - 常用窗口部件演示
 * 
 * 本章学习要点：
 * 1. 各种常用按钮部件（QPushButton, QCheckBox, QRadioButton等）
 * 2. 输入部件（QLineEdit, QTextEdit, QSpinBox等）
 * 3. 显示部件（QLabel, QProgressBar, QLCDNumber等）
 * 4. 窗口属性设置（标题、大小、图标等）
 * 5. 窗口模态性
 */

#ifndef WIDGETSDEMO_H
#define WIDGETSDEMO_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QSlider>
#include <QProgressBar>
#include <QLCDNumber>
#include <QGroupBox>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStackedWidget>

/**
 * @class WidgetsDemo
 * @brief 演示各种常用窗口部件的类
 * 
 * 使用选项卡组织不同类型的部件演示
 */
class WidgetsDemo : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetsDemo(QWidget *parent = nullptr);

private:
    void setupUi();
    void setupButtonDemo(QWidget *parent);
    void setupInputDemo(QWidget *parent);
    void setupDisplayDemo(QWidget *parent);
    void setupWindowDemo(QWidget *parent);
    void updateWindowInfo();
    void connectSignals();

private slots:
    void onOkButtonClicked();
    void onTextChanged(const QString &text);
    void onSliderChanged(int value);
    void onProgressBarButtonClicked();
    void onOpenModalWindow();
    void onOpenModelessWindow();
    void onCenterButtonClicked();

private:
    // 主界面部件
    QTabWidget *m_tabWidget;      ///< 选项卡部件
    
    // 按钮演示部件
    QPushButton *m_pushButton;
    QCheckBox *m_checkBox;
    QRadioButton *m_radioBtn1;
    QRadioButton *m_radioBtn2;
    QLabel *m_buttonResultLabel;
    
    // 输入演示部件
    QLineEdit *m_lineEdit;
    QTextEdit *m_textEdit;
    QSpinBox *m_spinBox;
    QDoubleSpinBox *m_doubleSpinBox;
    QComboBox *m_comboBox;
    QSlider *m_slider;
    QLabel *m_inputResultLabel;
    
    // 显示演示部件
    QProgressBar *m_progressBar;
    QPushButton *m_progressButton;
    QLCDNumber *m_lcdNumber;
    QLabel *m_displayResultLabel;
    
    // 窗口属性演示部件
    QPushButton *m_modalBtn;
    QPushButton *m_modelessBtn;
    QPushButton *m_centerBtn;
    QPushButton *m_resizeBtn;
    QLabel *m_windowInfoLabel;
    
    // 用于非模态窗口的计数
    int m_clickCount;
};

#endif // WIDGETSDEMO_H
