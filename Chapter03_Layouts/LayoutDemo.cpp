/**
 * @file LayoutDemo.cpp
 * @brief 第3章示例 - 布局管理演示实现
 */

#include "LayoutDemo.h"
#include <QDebug>

LayoutDemo::LayoutDemo(QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(nullptr)
    , m_verticalLayout(nullptr)
    , m_vAddBtn(nullptr)
    , m_vRemoveBtn(nullptr)
    , m_vClearBtn(nullptr)
    , m_horizontalLayout(nullptr)
    , m_hAddBtn(nullptr)
    , m_hRemoveBtn(nullptr)
    , m_gridLayout(nullptr)
    , m_formLayout(nullptr)
    , m_stretchSlider(nullptr)
    , m_stretchLabel(nullptr)
    , m_stretchDemoWidget(nullptr)
    , m_verticalButtonCount(0)
    , m_horizontalButtonCount(0)
{
    setupUi();
    connectSignals();
    
    setWindowTitle("第3章：布局管理");
    resize(700, 500);
}

/**
 * @brief 设置主界面
 */
void LayoutDemo::setupUi()
{
    m_tabWidget = new QTabWidget(this);
    
    // 创建六个选项卡
    QWidget *vTab = new QWidget();
    QWidget *hTab = new QWidget();
    QWidget *gridTab = new QWidget();
    QWidget *formTab = new QWidget();
    QWidget *nestedTab = new QWidget();
    QWidget *stretchTab = new QWidget();
    
    setupVerticalLayout(vTab);
    setupHorizontalLayout(hTab);
    setupGridLayout(gridTab);
    setupFormLayout(formTab);
    setupNestedLayout(nestedTab);
    setupStretchDemo(stretchTab);
    
    m_tabWidget->addTab(vTab, "垂直布局");
    m_tabWidget->addTab(hTab, "水平布局");
    m_tabWidget->addTab(gridTab, "网格布局");
    m_tabWidget->addTab(formTab, "表单布局");
    m_tabWidget->addTab(nestedTab, "嵌套布局");
    m_tabWidget->addTab(stretchTab, "拉伸因子");
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tabWidget);
}

/**
 * @brief 设置垂直布局演示
 * 
 * QVBoxLayout将部件从上到下依次排列
 * 特点：
 * - 部件垂直堆叠
 * - 可以使用addStretch()添加弹簧
 * - 可以设置spacing和margins
 */
void LayoutDemo::setupVerticalLayout(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    // 创建控制按钮区
    QHBoxLayout *controlLayout = new QHBoxLayout();
    m_vAddBtn = createStyledButton("添加按钮");
    m_vRemoveBtn = createStyledButton("移除按钮");
    m_vClearBtn = createStyledButton("清空");
    
    controlLayout->addWidget(m_vAddBtn);
    controlLayout->addWidget(m_vRemoveBtn);
    controlLayout->addWidget(m_vClearBtn);
    mainLayout->addLayout(controlLayout);
    
    // 创建垂直布局演示区
    QGroupBox *group = new QGroupBox("垂直布局演示区", parent);
    m_verticalLayout = new QVBoxLayout(group);
    
    // 添加一些初始按钮
    m_verticalLayout->addWidget(createStyledButton("顶部按钮 1"));
    m_verticalLayout->addWidget(createStyledButton("中间按钮 2"));
    m_verticalLayout->addWidget(createStyledButton("底部按钮 3"));
    
    // 使用弹簧将按钮推向顶部
    m_verticalLayout->addStretch();
    
    // 设置布局属性
    m_verticalLayout->setSpacing(10);           // 部件之间的间距
    m_verticalLayout->setContentsMargins(15, 15, 15, 15);  // 边距
    
    mainLayout->addWidget(group);
}

/**
 * @brief 设置水平布局演示
 * 
 * QHBoxLayout将部件从左到右依次排列
 */
void LayoutDemo::setupHorizontalLayout(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    // 创建控制按钮
    QHBoxLayout *controlLayout = new QHBoxLayout();
    m_hAddBtn = createStyledButton("添加按钮");
    m_hRemoveBtn = createStyledButton("移除按钮");
    
    controlLayout->addWidget(m_hAddBtn);
    controlLayout->addWidget(m_hRemoveBtn);
    controlLayout->addStretch();  // 将按钮推向左侧
    mainLayout->addLayout(controlLayout);
    
    // 创建水平布局演示区
    QGroupBox *group = new QGroupBox("水平布局演示区", parent);
    m_horizontalLayout = new QHBoxLayout(group);
    
    // 添加一些初始按钮
    m_horizontalLayout->addWidget(createStyledButton("左"));
    m_horizontalLayout->addWidget(createStyledButton("中"));
    m_horizontalLayout->addWidget(createStyledButton("右"));
    
    // 使用弹簧将按钮推向左侧
    m_horizontalLayout->addStretch();
    
    // 设置布局属性
    m_horizontalLayout->setSpacing(15);
    m_horizontalLayout->setContentsMargins(20, 20, 20, 20);
    
    mainLayout->addWidget(group);
}

/**
 * @brief 设置网格布局演示
 * 
 * QGridLayout将部件按行列网格排列
 * 可以跨行或跨列放置部件
 */
void LayoutDemo::setupGridLayout(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QGroupBox *group = new QGroupBox("网格布局演示", parent);
    m_gridLayout = new QGridLayout(group);
    
    // 创建3x4的网格
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) {
            QPushButton *btn = new QPushButton(QString("(%1,%2)").arg(row).arg(col));
            m_gridLayout->addWidget(btn, row, col);
        }
    }
    
    // 添加跨列的按钮
    QPushButton *spanBtn = new QPushButton("跨列按钮 (占据2列)");
    m_gridLayout->addWidget(spanBtn, 3, 0, 1, 2);  // 第4行，第1-2列
    
    // 添加跨行的按钮
    QPushButton *rowSpanBtn = new QPushButton("跨行按钮\n(占据2行)");
    m_gridLayout->addWidget(rowSpanBtn, 0, 4, 2, 1);  // 第1-2行，第5列
    
    // 设置列拉伸因子（让最后一列可以拉伸）
    m_gridLayout->setColumnStretch(0, 1);
    m_gridLayout->setColumnStretch(1, 1);
    m_gridLayout->setColumnStretch(2, 1);
    m_gridLayout->setColumnStretch(3, 1);
    m_gridLayout->setColumnStretch(4, 2);  // 第5列拉伸更多
    
    // 设置网格间距
    m_gridLayout->setSpacing(8);
    m_gridLayout->setContentsMargins(15, 15, 15, 15);
    
    mainLayout->addWidget(group);
    
    // 添加说明标签
    QLabel *infoLabel = new QLabel(
        "网格布局特点：\n"
        "- 部件按行列网格排列\n"
        "- 可以跨行或跨列 (addWidget(widget, row, column, rowSpan, columnSpan))\n"
        "- 可以单独设置行和列的拉伸因子",
        parent
    );
    infoLabel->setStyleSheet("background-color: #f0f8ff; padding: 10px; border-radius: 5px;");
    mainLayout->addWidget(infoLabel);
}

/**
 * @brief 设置表单布局演示
 * 
 * QFormLayout专门用于表单界面
 * 自动管理标签和字段的成对排列
 */
void LayoutDemo::setupFormLayout(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QGroupBox *group = new QGroupBox("表单布局演示", parent);
    m_formLayout = new QFormLayout(group);
    
    // 添加表单项（标签 + 部件）
    m_formLayout->addRow("姓名：", new QLineEdit("张三"));
    m_formLayout->addRow("年龄：", new QSpinBox());
    m_formLayout->addRow("邮箱：", new QLineEdit());
    m_formLayout->addRow("地址：", new QLineEdit());
    
    // 添加多行文本框
    m_formLayout->addRow("备注：", new QTextEdit());
    
    // 添加复选框（标签为空字符串）
    m_formLayout->addRow("", new QCheckBox("同意服务条款"));
    
    // 添加按钮（跨两列）
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(new QPushButton("提交"));
    btnLayout->addWidget(new QPushButton("重置"));
    m_formLayout->addRow(btnLayout);
    
    // 设置表单布局属性
    m_formLayout->setSpacing(12);
    m_formLayout->setContentsMargins(20, 20, 20, 20);
    m_formLayout->setLabelAlignment(Qt::AlignRight);  // 标签右对齐
    
    mainLayout->addWidget(group);
    
    // 添加说明
    QLabel *infoLabel = new QLabel(
        "表单布局特点：\n"
        "- 专门用于表单界面\n"
        "- 自动管理标签和字段的成对排列\n"
        "- 标签默认右对齐\n"
        "- 适合创建设置对话框、注册表单等",
        parent
    );
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("background-color: #f0fff0; padding: 10px; border-radius: 5px;");
    mainLayout->addWidget(infoLabel);
}

/**
 * @brief 设置嵌套布局演示
 * 
 * 演示如何将不同类型的布局组合使用
 */
void LayoutDemo::setupNestedLayout(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QGroupBox *group = new QGroupBox("嵌套布局演示", parent);
    
    // 创建一个主水平布局
    QHBoxLayout *hLayout = new QHBoxLayout(group);
    
    // 左侧：垂直布局
    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(new QLabel("左侧垂直布局"));
    leftLayout->addWidget(new QPushButton("按钮 1"));
    leftLayout->addWidget(new QPushButton("按钮 2"));
    leftLayout->addWidget(new QPushButton("按钮 3"));
    leftLayout->addStretch();
    
    // 右侧：网格布局
    QGridLayout *rightLayout = new QGridLayout();
    rightLayout->addWidget(new QLabel("姓名:"), 0, 0);
    rightLayout->addWidget(new QLineEdit(), 0, 1);
    rightLayout->addWidget(new QLabel("年龄:"), 1, 0);
    rightLayout->addWidget(new QSpinBox(), 1, 1);
    rightLayout->addWidget(new QPushButton("确认"), 2, 0, 1, 2);
    
    // 将两个子布局添加到主水平布局
    hLayout->addLayout(leftLayout, 1);    // 拉伸因子为1
    hLayout->addSpacing(20);               // 添加固定间距
    hLayout->addLayout(rightLayout, 2);   // 拉伸因子为2，占据更多空间
    
    mainLayout->addWidget(group);
    
    // 添加说明
    QLabel *infoLabel = new QLabel(
        "嵌套布局要点：\n"
        "- 使用addLayout()将子布局添加到父布局中\n"
        "- 可以设置拉伸因子控制各区域的比例\n"
        "- 使用addSpacing()添加固定间距\n"
        "- 嵌套布局可以创建复杂的界面结构",
        parent
    );
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("background-color: #fff5ee; padding: 10px; border-radius: 5px;");
    mainLayout->addWidget(infoLabel);
}

/**
 * @brief 设置拉伸因子演示
 * 
 * 演示如何使用拉伸因子控制部件大小比例
 */
void LayoutDemo::setupStretchDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    // 控制区
    QGroupBox *controlGroup = new QGroupBox("拉伸控制", parent);
    QHBoxLayout *controlLayout = new QHBoxLayout(controlGroup);
    
    controlLayout->addWidget(new QLabel("顶部拉伸因子:"));
    m_stretchSlider = new QSlider(Qt::Horizontal, parent);
    m_stretchSlider->setRange(1, 10);
    m_stretchSlider->setValue(1);
    controlLayout->addWidget(m_stretchSlider);
    
    m_stretchLabel = new QLabel("1 : 1");
    controlLayout->addWidget(m_stretchLabel);
    
    mainLayout->addWidget(controlGroup);
    
    // 演示区
    m_stretchDemoWidget = new QWidget(parent);
    QVBoxLayout *demoLayout = new QVBoxLayout(m_stretchDemoWidget);
    
    QPushButton *topBtn = new QPushButton("顶部区域");
    topBtn->setStyleSheet("background-color: #87ceeb; padding: 30px; font-weight: bold;");
    
    QPushButton *bottomBtn = new QPushButton("底部区域");
    bottomBtn->setStyleSheet("background-color: #ffa07a; padding: 30px; font-weight: bold;");
    
    // 设置初始拉伸因子
    demoLayout->addWidget(topBtn, 1);    // 拉伸因子1
    demoLayout->addWidget(bottomBtn, 1); // 拉伸因子1
    
    m_stretchDemoWidget->setStyleSheet("border: 2px solid #333; border-radius: 5px;");
    mainLayout->addWidget(m_stretchDemoWidget);
    
    // 添加说明
    QLabel *infoLabel = new QLabel(
        "拉伸因子（Stretch Factor）：\n"
        "- 通过addWidget(widget, stretch)设置拉伸因子\n"
        "- 拉伸因子决定了部件在可用空间中的分配比例\n"
        "- 例如：stretch(1)和stretch(2)的比例是1:2\n"
        "- 滑动滑块查看不同拉伸比例的效果",
        parent
    );
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("background-color: #e6e6fa; padding: 10px; border-radius: 5px;");
    mainLayout->addWidget(infoLabel);
}

/**
 * @brief 连接信号和槽
 */
void LayoutDemo::connectSignals()
{
    // 垂直布局控制
    connect(m_vAddBtn, &QPushButton::clicked, this, &LayoutDemo::onDynamicAddClicked);
    connect(m_vRemoveBtn, &QPushButton::clicked, this, &LayoutDemo::onDynamicRemoveClicked);
    connect(m_vClearBtn, &QPushButton::clicked, [this]() {
        // 清除所有按钮（保留弹簧）
        while (m_verticalLayout->count() > 1) {  // 保留最后一个stretch
            QLayoutItem *item = m_verticalLayout->takeAt(0);
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
        m_verticalButtonCount = 0;
    });
    
    // 水平布局控制
    connect(m_hAddBtn, &QPushButton::clicked, [this]() {
        m_horizontalButtonCount++;
        m_horizontalLayout->insertWidget(
            m_horizontalLayout->count() - 1,  // 在stretch之前插入
            createStyledButton(QString("按钮 %1").arg(m_horizontalButtonCount))
        );
    });
    
    connect(m_hRemoveBtn, &QPushButton::clicked, [this]() {
        if (m_horizontalLayout->count() > 2) {  // 至少保留一个按钮和stretch
            QLayoutItem *item = m_horizontalLayout->takeAt(0);
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
    });
    
    // 拉伸因子控制
    connect(m_stretchSlider, &QSlider::valueChanged, this, &LayoutDemo::onStretchChanged);
}

/**
 * @brief 动态添加按钮（垂直布局）
 */
void LayoutDemo::onDynamicAddClicked()
{
    m_verticalButtonCount++;
    QPushButton *btn = createStyledButton(QString("动态按钮 %1").arg(m_verticalButtonCount));
    // 在最后一个项目（stretch）之前插入
    m_verticalLayout->insertWidget(m_verticalLayout->count() - 1, btn);
}

/**
 * @brief 动态移除按钮（垂直布局）
 */
void LayoutDemo::onDynamicRemoveClicked()
{
    if (m_verticalLayout->count() > 2) {  // 至少保留一个按钮和stretch
        QLayoutItem *item = m_verticalLayout->takeAt(0);
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

/**
 * @brief 拉伸因子改变
 */
void LayoutDemo::onStretchChanged(int value)
{
    m_stretchLabel->setText(QString("%1 : 1").arg(value));
    
    // 更新演示区的拉伸因子
    QVBoxLayout *demoLayout = qobject_cast<QVBoxLayout*>(m_stretchDemoWidget->layout());
    if (demoLayout && demoLayout->count() >= 2) {
        demoLayout->setStretch(0, value);   // 顶部按钮拉伸因子
        demoLayout->setStretch(1, 1);      // 底部按钮拉伸因子
    }
}

/**
 * @brief 创建样式化的按钮
 */
QPushButton* LayoutDemo::createStyledButton(const QString &text)
{
    QPushButton *btn = new QPushButton(text);
    btn->setMinimumHeight(35);
    btn->setStyleSheet(
        "QPushButton {"
        "    background-color: #4a90e2;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 5px 15px;"
        "    font-size: 12px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #357abd;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #2a5f8f;"
        "}"
    );
    return btn;
}
