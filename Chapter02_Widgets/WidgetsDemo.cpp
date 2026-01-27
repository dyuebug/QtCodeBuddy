/**
 * @file WidgetsDemo.cpp
 * @brief 第2章示例 - 常用窗口部件演示实现
 */

#include "WidgetsDemo.h"
#include <QMessageBox>
#include <QTimer>
#include <QApplication>
#include <QScreen>
#include <QDialog>

WidgetsDemo::WidgetsDemo(QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(nullptr)
    , m_pushButton(nullptr)
    , m_checkBox(nullptr)
    , m_radioBtn1(nullptr)
    , m_radioBtn2(nullptr)
    , m_buttonResultLabel(nullptr)
    , m_lineEdit(nullptr)
    , m_textEdit(nullptr)
    , m_spinBox(nullptr)
    , m_doubleSpinBox(nullptr)
    , m_comboBox(nullptr)
    , m_slider(nullptr)
    , m_inputResultLabel(nullptr)
    , m_progressBar(nullptr)
    , m_progressButton(nullptr)
    , m_lcdNumber(nullptr)
    , m_displayResultLabel(nullptr)
    , m_modalBtn(nullptr)
    , m_modelessBtn(nullptr)
    , m_centerBtn(nullptr)
    , m_resizeBtn(nullptr)
    , m_windowInfoLabel(nullptr)
    , m_clickCount(0)
{
    setupUi();
    connectSignals();
    
    setWindowTitle("第2章：窗口和部件");
    resize(600, 450);
}

/**
 * @brief 设置主界面
 */
void WidgetsDemo::setupUi()
{
    // 创建选项卡部件
    m_tabWidget = new QTabWidget(this);
    
    // 创建四个选项卡
    QWidget *buttonTab = new QWidget();
    QWidget *inputTab = new QWidget();
    QWidget *displayTab = new QWidget();
    QWidget *windowTab = new QWidget();
    
    // 设置各个选项卡的内容
    setupButtonDemo(buttonTab);
    setupInputDemo(inputTab);
    setupDisplayDemo(displayTab);
    setupWindowDemo(windowTab);
    
    // 添加选项卡
    m_tabWidget->addTab(buttonTab, "按钮部件");
    m_tabWidget->addTab(inputTab, "输入部件");
    m_tabWidget->addTab(displayTab, "显示部件");
    m_tabWidget->addTab(windowTab, "窗口属性");
    
    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tabWidget);
}

/**
 * @brief 设置按钮演示界面
 */
void WidgetsDemo::setupButtonDemo(QWidget *parent)
{
    QVBoxLayout *layout = new QVBoxLayout(parent);
    
    // 1. 普通按钮（QPushButton）
    m_pushButton = new QPushButton("确定按钮", parent);
    m_pushButton->setStyleSheet("padding: 8px; font-size: 14px;");
    
    // 2. 复选框（QCheckBox）
    QGroupBox *checkGroup = new QGroupBox("复选框", parent);
    QVBoxLayout *checkLayout = new QVBoxLayout(checkGroup);
    m_checkBox = new QCheckBox("启用功能", checkGroup);
    m_checkBox->setChecked(true);  // 设置为选中状态
    checkLayout->addWidget(m_checkBox);
    
    // 3. 单选按钮（QRadioButton）
    QGroupBox *radioGroup = new QGroupBox("单选按钮", parent);
    QVBoxLayout *radioLayout = new QVBoxLayout(radioGroup);
    m_radioBtn1 = new QRadioButton("选项 A", radioGroup);
    m_radioBtn2 = new QRadioButton("选项 B", radioGroup);
    m_radioBtn1->setChecked(true);  // 默认选中第一个
    radioLayout->addWidget(m_radioBtn1);
    radioLayout->addWidget(m_radioBtn2);
    
    // 4. 结果显示标签
    m_buttonResultLabel = new QLabel("等待操作...", parent);
    m_buttonResultLabel->setAlignment(Qt::AlignCenter);
    m_buttonResultLabel->setStyleSheet("padding: 10px; background-color: #f0f0f0; border-radius: 5px;");
    
    // 添加到布局
    layout->addWidget(m_pushButton);
    layout->addWidget(checkGroup);
    layout->addWidget(radioGroup);
    layout->addWidget(m_buttonResultLabel);
    layout->addStretch();
}

/**
 * @brief 设置输入部件演示界面
 */
void WidgetsDemo::setupInputDemo(QWidget *parent)
{
    QGridLayout *layout = new QGridLayout(parent);
    
    // 1. 单行文本输入（QLineEdit）
    layout->addWidget(new QLabel("单行输入:"), 0, 0);
    m_lineEdit = new QLineEdit(parent);
    m_lineEdit->setPlaceholderText("请输入文字...");  // 设置占位符文本
    layout->addWidget(m_lineEdit, 0, 1);
    
    // 2. 多行文本输入（QTextEdit）
    layout->addWidget(new QLabel("多行输入:"), 1, 0);
    m_textEdit = new QTextEdit(parent);
    m_textEdit->setPlaceholderText("请输入多行文字...");
    m_textEdit->setMaximumHeight(80);
    layout->addWidget(m_textEdit, 1, 1);
    
    // 3. 整数旋转框（QSpinBox）
    layout->addWidget(new QLabel("整数选择:"), 2, 0);
    m_spinBox = new QSpinBox(parent);
    m_spinBox->setRange(0, 100);      // 设置范围
    m_spinBox->setValue(50);          // 设置初始值
    m_spinBox->setSuffix(" 个");      // 设置后缀
    layout->addWidget(m_spinBox, 2, 1);
    
    // 4. 浮点数旋转框（QDoubleSpinBox）
    layout->addWidget(new QLabel("浮点数:"), 3, 0);
    m_doubleSpinBox = new QDoubleSpinBox(parent);
    m_doubleSpinBox->setRange(0.0, 10.0);
    m_doubleSpinBox->setValue(5.5);
    m_doubleSpinBox->setDecimals(2);   // 设置小数位数
    m_doubleSpinBox->setSingleStep(0.1);  // 设置步进值
    layout->addWidget(m_doubleSpinBox, 3, 1);
    
    // 5. 下拉组合框（QComboBox）
    layout->addWidget(new QLabel("下拉选择:"), 4, 0);
    m_comboBox = new QComboBox(parent);
    m_comboBox->addItem("苹果");
    m_comboBox->addItem("香蕉");
    m_comboBox->addItem("橘子");
    m_comboBox->addItem("葡萄");
    m_comboBox->setCurrentIndex(0);
    layout->addWidget(m_comboBox, 4, 1);
    
    // 6. 滑动条（QSlider）
    layout->addWidget(new QLabel("滑动条:"), 5, 0);
    m_slider = new QSlider(Qt::Horizontal, parent);
    m_slider->setRange(0, 100);
    m_slider->setValue(50);
    layout->addWidget(m_slider, 5, 1);
    
    // 7. 结果显示标签
    m_inputResultLabel = new QLabel("输入信息将显示在这里", parent);
    m_inputResultLabel->setWordWrap(true);
    m_inputResultLabel->setStyleSheet("padding: 10px; background-color: #e8f4f8; border-radius: 5px;");
    layout->addWidget(m_inputResultLabel, 6, 0, 1, 2);
}

/**
 * @brief 设置显示部件演示界面
 */
void WidgetsDemo::setupDisplayDemo(QWidget *parent)
{
    QVBoxLayout *layout = new QVBoxLayout(parent);
    
    // 1. 进度条（QProgressBar）
    QGroupBox *progressGroup = new QGroupBox("进度条", parent);
    QVBoxLayout *progressLayout = new QVBoxLayout(progressGroup);
    
    m_progressBar = new QProgressBar(progressGroup);
    m_progressBar->setRange(0, 100);
    m_progressBar->setValue(30);
    m_progressBar->setFormat("%p%");  // 设置显示格式（百分比）
    progressLayout->addWidget(m_progressBar);
    
    m_progressButton = new QPushButton("开始进度", progressGroup);
    progressLayout->addWidget(m_progressButton);
    
    layout->addWidget(progressGroup);
    
    // 2. LCD数字显示（QLCDNumber）
    QGroupBox *lcdGroup = new QGroupBox("LCD数字", parent);
    QVBoxLayout *lcdLayout = new QVBoxLayout(lcdGroup);
    
    m_lcdNumber = new QLCDNumber(lcdGroup);
    m_lcdNumber->setDigitCount(5);  // 设置显示位数
    m_lcdNumber->display(12345);    // 显示数字
    m_lcdNumber->setSegmentStyle(QLCDNumber::Flat);  // 设置显示风格
    lcdLayout->addWidget(m_lcdNumber);
    
    layout->addWidget(lcdGroup);
    
    // 3. 结果显示标签
    m_displayResultLabel = new QLabel("显示部件演示区域", parent);
    m_displayResultLabel->setAlignment(Qt::AlignCenter);
    m_displayResultLabel->setStyleSheet("padding: 15px; background-color: #fff3cd; border-radius: 5px; font-size: 14px;");
    layout->addWidget(m_displayResultLabel);
    
    layout->addStretch();
}

/**
 * @brief 设置窗口属性演示界面
 */
void WidgetsDemo::setupWindowDemo(QWidget *parent)
{
    QVBoxLayout *layout = new QVBoxLayout(parent);
    
    // 1. 模态窗口按钮
    m_modalBtn = new QPushButton("打开模态窗口", parent);
    m_modalBtn->setToolTip("模态窗口会阻塞父窗口");  // 设置工具提示
    layout->addWidget(m_modalBtn);
    
    // 2. 非模态窗口按钮
    m_modelessBtn = new QPushButton("打开非模态窗口", parent);
    m_modelessBtn->setToolTip("非模态窗口不会阻塞父窗口");
    layout->addWidget(m_modelessBtn);
    
    // 3. 居中窗口按钮
    m_centerBtn = new QPushButton("窗口居中", parent);
    layout->addWidget(m_centerBtn);
    
    // 4. 调整窗口大小按钮
    m_resizeBtn = new QPushButton("调整窗口大小", parent);
    layout->addWidget(m_resizeBtn);
    
    // 5. 窗口信息显示
    m_windowInfoLabel = new QLabel(parent);
    m_windowInfoLabel->setWordWrap(true);
    updateWindowInfo();
    layout->addWidget(m_windowInfoLabel);
    
    layout->addStretch();
}

/**
 * @brief 更新窗口信息显示
 */
void WidgetsDemo::updateWindowInfo()
{
    QString info = QString("窗口大小: %1 x %2\n位置: (%3, %4)\n标题: %5")
        .arg(width())
        .arg(height())
        .arg(pos().x())
        .arg(pos().y())
        .arg(windowTitle());
    m_windowInfoLabel->setText(info);
}

/**
 * @brief 连接信号和槽
 */
void WidgetsDemo::connectSignals()
{
    // 按钮相关
    connect(m_pushButton, &QPushButton::clicked, this, &WidgetsDemo::onOkButtonClicked);
    
    // 复选框和单选按钮
    connect(m_checkBox, &QCheckBox::checkStateChanged, [this](Qt::CheckState state) {
        QString status = (state == Qt::Checked) ? "已选中" : "未选中";
        m_buttonResultLabel->setText(QString("复选框状态: %1").arg(status));
    });
    
    connect(m_radioBtn1, &QRadioButton::toggled, [this](bool checked) {
        if (checked) m_buttonResultLabel->setText("选择了单选按钮 A");
    });
    
    connect(m_radioBtn2, &QRadioButton::toggled, [this](bool checked) {
        if (checked) m_buttonResultLabel->setText("选择了单选按钮 B");
    });
    
    // 输入部件相关
    connect(m_lineEdit, &QLineEdit::textChanged, this, &WidgetsDemo::onTextChanged);
    connect(m_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this](int value) {
        m_inputResultLabel->setText(QString("整数选择: %1").arg(value));
    });
    connect(m_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
        m_inputResultLabel->setText(QString("选择了: %1").arg(m_comboBox->itemText(index)));
    });
    connect(m_slider, &QSlider::valueChanged, this, &WidgetsDemo::onSliderChanged);
    
    // 显示部件相关
    connect(m_progressButton, &QPushButton::clicked, this, &WidgetsDemo::onProgressBarButtonClicked);
    
    // 窗口相关
    connect(m_modalBtn, &QPushButton::clicked, this, &WidgetsDemo::onOpenModalWindow);
    connect(m_modelessBtn, &QPushButton::clicked, this, &WidgetsDemo::onOpenModelessWindow);
    connect(m_centerBtn, &QPushButton::clicked, this, &WidgetsDemo::onCenterButtonClicked);
    connect(m_resizeBtn, &QPushButton::clicked, [this]() {
        resize(800, 600);
        updateWindowInfo();
    });
}

/**
 * @brief 确定按钮点击槽函数
 */
void WidgetsDemo::onOkButtonClicked()
{
    QString checkStatus = m_checkBox->isChecked() ? "已选中" : "未选中";
    QString radioText = m_radioBtn1->isChecked() ? "A" : "B";

    m_buttonResultLabel->setText(QString("按钮被点击！\n复选框: %1\n单选: %2")
        .arg(checkStatus, radioText));
}

/**
 * @brief 文本改变槽函数
 */
void WidgetsDemo::onTextChanged(const QString &text)
{
    m_inputResultLabel->setText(QString("单行输入: %1\n长度: %2 字符")
        .arg(text).arg(text.length()));
}

/**
 * @brief 滑动条改变槽函数
 */
void WidgetsDemo::onSliderChanged(int value)
{
    m_lcdNumber->display(value);
    m_inputResultLabel->setText(QString("滑动条值: %1").arg(value));
}

/**
 * @brief 进度条按钮点击槽函数
 */
void WidgetsDemo::onProgressBarButtonClicked()
{
    m_progressBar->setValue(0);
    m_clickCount++;
    m_displayResultLabel->setText(QString("开始第 %1 次进度演示").arg(m_clickCount));
    
    // 使用定时器模拟进度
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this, timer]() {
        int value = m_progressBar->value();
        if (value < 100) {
            m_progressBar->setValue(value + 5);
        } else {
            timer->stop();
            m_displayResultLabel->setText("进度完成！");
        }
    });
    timer->start(100);  // 每100毫秒触发一次
}

/**
 * @brief 打开模态窗口
 */
void WidgetsDemo::onOpenModalWindow()
{
    // 创建模态对话框（QDialog才有exec方法）
    QDialog *modalDialog = new QDialog(this);
    modalDialog->setWindowTitle("模态窗口");
    modalDialog->setWindowModality(Qt::ApplicationModal);  // 设置为应用级模态

    QVBoxLayout *layout = new QVBoxLayout(modalDialog);
    layout->addWidget(new QLabel("这是一个模态窗口\n你必须关闭它才能操作其他窗口"));

    QPushButton *closeBtn = new QPushButton("关闭", modalDialog);
    connect(closeBtn, &QPushButton::clicked, modalDialog, &QDialog::accept);
    layout->addWidget(closeBtn);

    modalDialog->exec();  // exec()会阻塞，直到窗口关闭
    delete modalDialog;  // 关闭后手动删除
}

/**
 * @brief 打开非模态窗口
 */
void WidgetsDemo::onOpenModelessWindow()
{
    // 创建非模态窗口
    QWidget *modelessDialog = new QWidget(this);
    modelessDialog->setAttribute(Qt::WA_DeleteOnClose);  // 关闭时自动删除
    modelessDialog->setWindowTitle("非模态窗口");
    
    QVBoxLayout *layout = new QVBoxLayout(modelessDialog);
    layout->addWidget(new QLabel("这是一个非模态窗口\n你可以同时操作其他窗口"));
    
    QPushButton *closeBtn = new QPushButton("关闭", modelessDialog);
    connect(closeBtn, &QPushButton::clicked, modelessDialog, &QWidget::close);
    layout->addWidget(closeBtn);
    
    modelessDialog->show();  // show()不会阻塞
}

/**
 * @brief 窗口居中
 */
void WidgetsDemo::onCenterButtonClicked()
{
    // 获取屏幕信息
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    
    // 计算居中位置
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    
    move(x, y);
    updateWindowInfo();
}
