/**
 * @file CustomWidgetDemo.cpp
 * @brief 第8章示例 - 自定义部件演示实现
 */

#include "CustomWidgetDemo.h"
#include <QMessageBox>
#include <QRandomGenerator>

CustomWidgetDemo::CustomWidgetDemo(QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(nullptr)
    , m_colorPicker(nullptr)
    , m_colorPreview(nullptr)
    , m_colorInfoLabel(nullptr)
    , m_randomColorBtn(nullptr)
    , m_progressBar(nullptr)
    , m_progressSlider(nullptr)
    , m_minSpinBox(nullptr)
    , m_maxSpinBox(nullptr)
    , m_valueSpinBox(nullptr)
    , m_animationCheckBox(nullptr)
    , m_startAnimationBtn(nullptr)
    , m_stopAnimationBtn(nullptr)
    , m_resetProgressBtn(nullptr)
    , m_progressInfoLabel(nullptr)
    , m_propertiesColorPicker(nullptr)
    , m_colorCountSpin(nullptr)
    , m_innerRadiusSpin(nullptr)
    , m_outerRadiusSpin(nullptr)
    , m_propertiesInfoLabel(nullptr)
    , m_logTextEdit(nullptr)
{
    setupUi();
    connectSignals();
    
    setWindowTitle("第8章：自定义部件");
    resize(800, 600);
}

/**
 * @brief 设置主界面
 */
void CustomWidgetDemo::setupUi()
{
    m_tabWidget = new QTabWidget(this);
    
    // 创建选项卡
    QWidget *colorTab = new QWidget();
    QWidget *progressTab = new QWidget();
    QWidget *propertiesTab = new QWidget();
    
    setupColorPickerDemo(colorTab);
    setupProgressBarDemo(progressTab);
    setupCustomPropertiesDemo(propertiesTab);
    
    m_tabWidget->addTab(colorTab, "颜色选择器");
    m_tabWidget->addTab(progressTab, "圆形进度条");
    m_tabWidget->addTab(propertiesTab, "自定义属性");
    
    // 日志区域
    QGroupBox *logGroup = new QGroupBox("操作日志", this);
    QVBoxLayout *logLayout = new QVBoxLayout(logGroup);
    
    m_logTextEdit = new QTextEdit(logGroup);
    m_logTextEdit->setReadOnly(true);
    m_logTextEdit->setMaximumHeight(150);
    m_logTextEdit->setPlaceholderText("自定义部件的日志将显示在这里...");
    logLayout->addWidget(m_logTextEdit);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tabWidget);
    mainLayout->addWidget(logGroup);
}

/**
 * @brief 颜色选择器演示
 */
void CustomWidgetDemo::setupColorPickerDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    // 颜色选择器
    QGroupBox *pickerGroup = new QGroupBox("颜色选择器", parent);
    QVBoxLayout *pickerLayout = new QVBoxLayout(pickerGroup);
    
    m_colorPicker = new ColorPickerWidget(pickerGroup);
    m_colorPicker->setMinimumHeight(250);
    pickerLayout->addWidget(m_colorPicker);
    
    mainLayout->addWidget(pickerGroup);
    
    // 颜色预览和信息
    QGroupBox *previewGroup = new QGroupBox("颜色信息", parent);
    QVBoxLayout *previewLayout = new QVBoxLayout(previewGroup);
    
    m_colorPreview = new QLabel(previewGroup);
    m_colorPreview->setMinimumHeight(50);
    m_colorPreview->setStyleSheet("border: 2px solid #333; border-radius: 5px;");
    previewLayout->addWidget(m_colorPreview);
    
    m_colorInfoLabel = new QLabel("选择一个颜色", previewGroup);
    m_colorInfoLabel->setWordWrap(true);
    m_colorInfoLabel->setStyleSheet("padding: 10px; background-color: #f5f5f5; border-radius: 5px;");
    previewLayout->addWidget(m_colorInfoLabel);
    
    m_randomColorBtn = new QPushButton("随机颜色", previewGroup);
    previewLayout->addWidget(m_randomColorBtn);
    
    mainLayout->addWidget(previewGroup);
}

/**
 * @brief 进度条演示
 */
void CustomWidgetDemo::setupProgressBarDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    // 进度条显示
    QGroupBox *progressGroup = new QGroupBox("圆形进度条", parent);
    QHBoxLayout *progressLayout = new QHBoxLayout(progressGroup);
    
    m_progressBar = new CircularProgressBar(progressGroup);
    m_progressBar->setFixedSize(200, 200);
    progressLayout->addWidget(m_progressBar);
    
    mainLayout->addWidget(progressGroup);
    
    // 控制区
    QGroupBox *controlGroup = new QGroupBox("控制", parent);
    QVBoxLayout *controlLayout = new QVBoxLayout(controlGroup);
    
    // 滑块控制
    QHBoxLayout *sliderLayout = new QHBoxLayout();
    sliderLayout->addWidget(new QLabel("进度值:"));
    m_progressSlider = new QSlider(Qt::Horizontal, controlGroup);
    m_progressSlider->setRange(0, 100);
    m_progressSlider->setValue(0);
    sliderLayout->addWidget(m_progressSlider);
    controlLayout->addLayout(sliderLayout);
    
    // 数值输入
    QGridLayout *inputLayout = new QGridLayout();
    
    inputLayout->addWidget(new QLabel("最小值:"), 0, 0);
    m_minSpinBox = new QSpinBox(controlGroup);
    m_minSpinBox->setRange(0, 1000);
    m_minSpinBox->setValue(0);
    inputLayout->addWidget(m_minSpinBox, 0, 1);
    
    inputLayout->addWidget(new QLabel("最大值:"), 1, 0);
    m_maxSpinBox = new QSpinBox(controlGroup);
    m_maxSpinBox->setRange(1, 10000);
    m_maxSpinBox->setValue(100);
    inputLayout->addWidget(m_maxSpinBox, 1, 1);
    
    inputLayout->addWidget(new QLabel("当前值:"), 2, 0);
    m_valueSpinBox = new QSpinBox(controlGroup);
    m_valueSpinBox->setRange(0, 10000);
    m_valueSpinBox->setValue(0);
    inputLayout->addWidget(m_valueSpinBox, 2, 1);
    
    controlLayout->addLayout(inputLayout);
    
    // 动画控制
    m_animationCheckBox = new QCheckBox("启用动画", controlGroup);
    controlLayout->addWidget(m_animationCheckBox);
    
    QHBoxLayout *btnLayout = new QHBoxLayout();
    m_startAnimationBtn = new QPushButton("开始动画", controlGroup);
    m_stopAnimationBtn = new QPushButton("停止动画", controlGroup);
    m_resetProgressBtn = new QPushButton("重置", controlGroup);
    
    btnLayout->addWidget(m_startAnimationBtn);
    btnLayout->addWidget(m_stopAnimationBtn);
    btnLayout->addWidget(m_resetProgressBtn);
    
    controlLayout->addLayout(btnLayout);
    
    mainLayout->addWidget(controlGroup);
    
    // 信息标签
    m_progressInfoLabel = new QLabel("进度: 0% (0/100)", parent);
    m_progressInfoLabel->setAlignment(Qt::AlignCenter);
    m_progressInfoLabel->setStyleSheet("padding: 10px; background-color: #e0f7fa; border-radius: 5px;");
    mainLayout->addWidget(m_progressInfoLabel);
}

/**
 * @brief 自定义属性演示
 */
void CustomWidgetDemo::setupCustomPropertiesDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    // 颜色选择器
    QGroupBox *pickerGroup = new QGroupBox("颜色选择器", parent);
    QVBoxLayout *pickerLayout = new QVBoxLayout(pickerGroup);
    
    m_propertiesColorPicker = new ColorPickerWidget(pickerGroup);
    m_propertiesColorPicker->setMinimumHeight(250);
    pickerLayout->addWidget(m_propertiesColorPicker);
    
    mainLayout->addWidget(pickerGroup);
    
    // 属性控制
    QGroupBox *propGroup = new QGroupBox("属性控制", parent);
    QVBoxLayout *propLayout = new QVBoxLayout(propGroup);
    
    QHBoxLayout *colorCountLayout = new QHBoxLayout();
    colorCountLayout->addWidget(new QLabel("颜色数量:"));
    m_colorCountSpin = new QSpinBox(propGroup);
    m_colorCountSpin->setRange(6, 48);
    m_colorCountSpin->setValue(24);
    colorCountLayout->addWidget(m_colorCountSpin);
    propLayout->addLayout(colorCountLayout);
    
    QHBoxLayout *innerRadiusLayout = new QHBoxLayout();
    innerRadiusLayout->addWidget(new QLabel("内半径:"));
    m_innerRadiusSpin = new QSpinBox(propGroup);
    m_innerRadiusSpin->setRange(10, 50);
    m_innerRadiusSpin->setValue(20);
    innerRadiusLayout->addWidget(m_innerRadiusSpin);
    propLayout->addLayout(innerRadiusLayout);
    
    QHBoxLayout *outerRadiusLayout = new QHBoxLayout();
    outerRadiusLayout->addWidget(new QLabel("外半径:"));
    m_outerRadiusSpin = new QSpinBox(propGroup);
    m_outerRadiusSpin->setRange(50, 120);
    m_outerRadiusSpin->setValue(80);
    outerRadiusLayout->addWidget(m_outerRadiusSpin);
    propLayout->addLayout(outerRadiusLayout);
    
    mainLayout->addWidget(propGroup);
    
    // 信息标签
    m_propertiesInfoLabel = new QLabel("自定义属性信息将显示在这里", parent);
    m_propertiesInfoLabel->setWordWrap(true);
    m_propertiesInfoLabel->setStyleSheet("padding: 10px; background-color: #f3e5f5; border-radius: 5px;");
    mainLayout->addWidget(m_propertiesInfoLabel);
}

/**
 * @brief 连接信号和槽
 */
void CustomWidgetDemo::connectSignals()
{
    // 颜色选择器
    connect(m_colorPicker, &ColorPickerWidget::colorChanged, this, &CustomWidgetDemo::onColorChanged);
    connect(m_colorPicker, &ColorPickerWidget::colorSelected, this, &CustomWidgetDemo::onColorSelected);
    connect(m_randomColorBtn, &QPushButton::clicked, [this]() {
        // 生成随机颜色
        int hue = QRandomGenerator::global()->bounded(360);
        QColor randomColor = QColor::fromHsv(hue, 255, 255);
        m_colorPicker->setSelectedColor(randomColor);
        addLog(QString("设置随机颜色: %1").arg(randomColor.name()));
    });
    
    // 进度条
    connect(m_progressSlider, &QSlider::valueChanged, this, &CustomWidgetDemo::onProgressValueSliderChanged);
    connect(m_minSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &CustomWidgetDemo::onProgressRangeChanged);
    connect(m_maxSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &CustomWidgetDemo::onProgressRangeChanged);
    connect(m_valueSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this](int value) {
        m_progressBar->setValue(value);
        m_progressSlider->setValue(value);
    });
    
    connect(m_animationCheckBox, &QCheckBox::stateChanged, this, &CustomWidgetDemo::onAnimationEnabledChanged);
    connect(m_startAnimationBtn, &QPushButton::clicked, this, &CustomWidgetDemo::onStartProgressAnimation);
    connect(m_stopAnimationBtn, &QPushButton::clicked, this, &CustomWidgetDemo::onStopProgressAnimation);
    connect(m_resetProgressBtn, &QPushButton::clicked, this, &CustomWidgetDemo::onResetProgress);
    
    connect(m_progressBar, &CircularProgressBar::valueChanged, this, &CustomWidgetDemo::onProgressValueChanged);
    connect(m_progressBar, &CircularProgressBar::finished, this, &CustomWidgetDemo::onProgressFinished);
    
    // 自定义属性
    connect(m_colorCountSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &CustomWidgetDemo::onCustomPropertiesChanged);
    connect(m_innerRadiusSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &CustomWidgetDemo::onCustomPropertiesChanged);
    connect(m_outerRadiusSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &CustomWidgetDemo::onCustomPropertiesChanged);
    connect(m_propertiesColorPicker, &ColorPickerWidget::colorChanged, [this](const QColor &color) {
        m_propertiesInfoLabel->setText(QString("选中的颜色: %1\nRGB: (%2, %3, %4)")
            .arg(color.name())
            .arg(color.red())
            .arg(color.green())
            .arg(color.blue()));
    });
}

/**
 * @brief 颜色改变
 */
void CustomWidgetDemo::onColorChanged(const QColor &color)
{
    m_colorPreview->setStyleSheet(QString("background-color: %1; border: 2px solid #333; border-radius: 5px;").arg(color.name()));
    m_colorInfoLabel->setText(QString("颜色已改变:\n名称: %1\nRGB: (%2, %3, %4)\nHSV: (%5°, %6%, %7%)")
        .arg(color.name())
        .arg(color.red())
        .arg(color.green())
        .arg(color.blue())
        .arg(color.hue())
        .arg(color.saturation())
        .arg(color.value()));
    
    addLog(QString("颜色改变: %1").arg(color.name()));
}

/**
 * @brief 颜色选择
 */
void CustomWidgetDemo::onColorSelected(const QColor &color)
{
    addLog(QString("颜色选择: %1 (用户点击选择)").arg(color.name()));
}

/**
 * @brief 进度值改变
 */
void CustomWidgetDemo::onProgressValueChanged(double value)
{
    double percentage = (value - m_progressBar->minimum()) / 
                        (m_progressBar->maximum() - m_progressBar->minimum()) * 100.0;
    
    m_progressInfoLabel->setText(QString("进度: %1% (%2/%3)")
        .arg(qRound(percentage))
        .arg(value, 0, 'f', 0)
        .arg(m_progressBar->maximum(), 0, 'f', 0));
    
    m_valueSpinBox->setValue(value);
    m_progressSlider->setValue(value);
}

/**
 * @brief 进度完成
 */
void CustomWidgetDemo::onProgressFinished()
{
    addLog("进度条达到100%！");
    QMessageBox::information(this, "完成", "进度条已完成！");
}

/**
 * @brief 开始进度动画
 */
void CustomWidgetDemo::onStartProgressAnimation()
{
    m_progressBar->startAnimation();
    addLog("开始进度动画");
}

/**
 * @brief 停止进度动画
 */
void CustomWidgetDemo::onStopProgressAnimation()
{
    m_progressBar->stopAnimation();
    addLog("停止进度动画");
}

/**
 * @brief 重置进度
 */
void CustomWidgetDemo::onResetProgress()
{
    m_progressBar->reset();
    m_progressSlider->setValue(0);
    m_valueSpinBox->setValue(0);
    addLog("重置进度条");
}

/**
 * @brief 进度滑块值改变
 */
void CustomWidgetDemo::onProgressValueSliderChanged(int value)
{
    m_progressBar->setValue(value);
    m_valueSpinBox->setValue(value);
}

/**
 * @brief 进度范围改变
 */
void CustomWidgetDemo::onProgressRangeChanged()
{
    int min = m_minSpinBox->value();
    int max = m_maxSpinBox->value();
    
    if (min < max) {
        m_progressBar->setRange(min, max);
        m_progressSlider->setRange(min, max);
        m_valueSpinBox->setRange(min, max);
        
        addLog(QString("进度范围改变: %1 - %2").arg(min).arg(max));
    }
}

/**
 * @brief 动画启用状态改变
 */
void CustomWidgetDemo::onAnimationEnabledChanged(int state)
{
    bool enabled = (state == Qt::Checked);
    m_progressBar->setAnimationEnabled(enabled);
    m_startAnimationBtn->setEnabled(enabled);
    m_stopAnimationBtn->setEnabled(enabled);
    
    addLog(QString("动画%1").arg(enabled ? "启用" : "禁用"));
}

/**
 * @brief 自定义属性改变
 */
void CustomWidgetDemo::onCustomPropertiesChanged()
{
    int colorCount = m_colorCountSpin->value();
    int innerRadius = m_innerRadiusSpin->value();
    int outerRadius = m_outerRadiusSpin->value();
    
    m_propertiesColorPicker->setColorCount(colorCount);
    m_propertiesColorPicker->setInnerRadius(innerRadius);
    m_propertiesColorPicker->setOuterRadius(outerRadius);
    
    m_propertiesInfoLabel->setText(QString(
        "自定义属性已更新:\n"
        "颜色数量: %1\n"
        "内半径: %2\n"
        "外半径: %3"
    ).arg(colorCount).arg(innerRadius).arg(outerRadius));
    
    addLog(QString("自定义属性更新: 颜色=%1, 内半径=%2, 外半径=%3")
        .arg(colorCount).arg(innerRadius).arg(outerRadius));
}

/**
 * @brief 添加日志
 */
void CustomWidgetDemo::addLog(const QString &message)
{
    QString timestamp = QTime::currentTime().toString("hh:mm:ss.zzz");
    m_logTextEdit->append(QString("[%1] %2").arg(timestamp, message));
}
