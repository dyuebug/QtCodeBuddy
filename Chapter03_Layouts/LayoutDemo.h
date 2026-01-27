/**
 * @file LayoutDemo.h
 * @brief 第3章示例 - 布局管理演示
 * 
 * 本章学习要点：
 * 1. QVBoxLayout（垂直布局）：部件从上到下排列
 * 2. QHBoxLayout（水平布局）：部件从左到右排列
 * 3. QGridLayout（网格布局）：部件按行列网格排列
 * 4. QFormLayout（表单布局）：标签和字段的成对排列
 * 5. 布局的嵌套使用
 * 6. 弹簧（QSpacerItem）的使用
 * 7. 布局的拉伸因子（stretch factor）
 */

#ifndef LAYOUTDEMO_H
#define LAYOUTDEMO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QSpacerItem>
#include <QSlider>

/**
 * @class LayoutDemo
 * @brief 演示各种布局管理器的类
 */
class LayoutDemo : public QWidget
{
    Q_OBJECT

public:
    explicit LayoutDemo(QWidget *parent = nullptr);

private:
    void setupUi();
    void setupVerticalLayout(QWidget *parent);
    void setupHorizontalLayout(QWidget *parent);
    void setupGridLayout(QWidget *parent);
    void setupFormLayout(QWidget *parent);
    void setupNestedLayout(QWidget *parent);
    void setupStretchDemo(QWidget *parent);
    void connectSignals();

    // 辅助函数：创建样式化的按钮
    QPushButton* createStyledButton(const QString &text);
    
private slots:
    void onDynamicAddClicked();
    void onDynamicRemoveClicked();
    void onStretchChanged(int value);

private:
    QTabWidget *m_tabWidget;
    
    // 垂直布局演示部件
    QVBoxLayout *m_verticalLayout;
    QPushButton *m_vAddBtn;
    QPushButton *m_vRemoveBtn;
    QPushButton *m_vClearBtn;
    
    // 水平布局演示部件
    QHBoxLayout *m_horizontalLayout;
    QPushButton *m_hAddBtn;
    QPushButton *m_hRemoveBtn;
    
    // 网格布局演示部件
    QGridLayout *m_gridLayout;
    
    // 表单布局演示部件
    QFormLayout *m_formLayout;
    
    // 嵌套布局演示部件
    
    // 拉伸因子演示部件
    QSlider *m_stretchSlider;
    QLabel *m_stretchLabel;
    QWidget *m_stretchDemoWidget;
    
    // 动态添加部件的计数
    int m_verticalButtonCount;
    int m_horizontalButtonCount;
};

#endif // LAYOUTDEMO_H
