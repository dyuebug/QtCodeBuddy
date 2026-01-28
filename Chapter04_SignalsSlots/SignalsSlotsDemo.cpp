/**
 * @file SignalsSlotsDemo.cpp
 * @brief 第4章示例 - 信号和槽机制演示实现
 */

#include "SignalsSlotsDemo.h"
#include <QMessageBox>
#include <QTime>
#include <QTimer>

SignalsSlotsDemo::SignalsSlotsDemo(QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(nullptr)
    , m_basicButton(nullptr)
    , m_disconnectBtn(nullptr)
    , m_checkbox(nullptr)
    , m_basicLabel(nullptr)
    , m_logTextEdit(nullptr)
    , m_spinBox(nullptr)
    , m_slider(nullptr)
    , m_lineEdit1(nullptr)
    , m_lineEdit2(nullptr)
    , m_paramLabel(nullptr)
    , m_lambdaBtn1(nullptr)
    , m_lambdaBtn2(nullptr)
    , m_lambdaLabel(nullptr)
    , m_counter(nullptr)
    , m_incBtn(nullptr)
    , m_decBtn(nullptr)
    , m_setBtn(nullptr)
    , m_counterSpinBox(nullptr)
    , m_counterLabel(nullptr)
    , m_sender1(nullptr)
    , m_sender2(nullptr)
    , m_sender3(nullptr)
    , m_commonBtn(nullptr)
    , m_multiLabel(nullptr)
    , m_clickCount(0)
{
    setupUi();
    connectSignals();
    
    setWindowTitle("第4章：信号和槽");
    resize(700, 550);
}

/**
 * @brief 设置主界面
 */
void SignalsSlotsDemo::setupUi()
{
    m_tabWidget = new QTabWidget(this);
    
    // 创建选项卡
    QWidget *basicTab = new QWidget();
    QWidget *paramTab = new QWidget();
    QWidget *lambdaTab = new QWidget();
    QWidget *customTab = new QWidget();
    QWidget *multiTab = new QWidget();
    
    setupBasicDemo(basicTab);
    setupParameterDemo(paramTab);
    setupLambdaDemo(lambdaTab);
    setupCustomSignalDemo(customTab);
    setupMultipleDemo(multiTab);
    
    m_tabWidget->addTab(basicTab, "基本连接");
    m_tabWidget->addTab(paramTab, "参数传递");
    m_tabWidget->addTab(lambdaTab, "Lambda槽");
    m_tabWidget->addTab(customTab, "自定义信号");
    m_tabWidget->addTab(multiTab, "多重连接");
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tabWidget);
}

/**
 * @brief 基本信号和槽连接演示
 */
void SignalsSlotsDemo::setupBasicDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    // 按钮演示
    QGroupBox *btnGroup = new QGroupBox("按钮信号演示", parent);
    QVBoxLayout *btnLayout = new QVBoxLayout(btnGroup);
    
    m_basicButton = new QPushButton("点击我 (发射clicked信号)", btnGroup);
    m_disconnectBtn = new QPushButton("断开连接", btnGroup);
    
    btnLayout->addWidget(m_basicButton);
    btnLayout->addWidget(m_disconnectBtn);
    
    mainLayout->addWidget(btnGroup);
    
    // 复选框演示
    QGroupBox *checkGroup = new QGroupBox("复选框信号演示", parent);
    QVBoxLayout *checkLayout = new QVBoxLayout(checkGroup);
    
    m_checkbox = new QCheckBox("启用选项", checkGroup);
    checkLayout->addWidget(m_checkbox);
    
    mainLayout->addWidget(checkGroup);
    
    // 结果显示
    m_basicLabel = new QLabel("等待操作...", parent);
    m_basicLabel->setAlignment(Qt::AlignCenter);
    m_basicLabel->setStyleSheet("padding: 15px; background-color: #e0f7fa; border-radius: 5px; font-size: 14px;");
    mainLayout->addWidget(m_basicLabel);
    
    // 日志区域
    m_logTextEdit = new QTextEdit(parent);
    m_logTextEdit->setReadOnly(true);
    m_logTextEdit->setMaximumHeight(120);
    m_logTextEdit->setPlaceholderText("信号和槽的日志将显示在这里...");
    mainLayout->addWidget(m_logTextEdit);
}

/**
 * @brief 参数传递演示
 */
void SignalsSlotsDemo::setupParameterDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    // SpinBox和Slider同步
    QGroupBox *syncGroup = new QGroupBox("SpinBox和Slider同步", parent);
    QHBoxLayout *syncLayout = new QHBoxLayout(syncGroup);
    
    m_spinBox = new QSpinBox(syncGroup);
    m_spinBox->setRange(0, 100);
    m_spinBox->setValue(50);
    
    m_slider = new QSlider(Qt::Horizontal, syncGroup);
    m_slider->setRange(0, 100);
    m_slider->setValue(50);
    
    syncLayout->addWidget(new QLabel("SpinBox:"));
    syncLayout->addWidget(m_spinBox);
    syncLayout->addWidget(new QLabel("Slider:"));
    syncLayout->addWidget(m_slider);
    
    mainLayout->addWidget(syncGroup);
    
    // 文本框同步
    QGroupBox *textGroup = new QGroupBox("文本框同步", parent);
    QVBoxLayout *textLayout = new QVBoxLayout(textGroup);
    
    m_lineEdit1 = new QLineEdit(textGroup);
    m_lineEdit1->setPlaceholderText("输入文本框1");
    
    m_lineEdit2 = new QLineEdit(textGroup);
    m_lineEdit2->setPlaceholderText("输入文本框2");
    
    textLayout->addWidget(m_lineEdit1);
    textLayout->addWidget(m_lineEdit2);
    
    mainLayout->addWidget(textGroup);
    
    // 结果显示
    m_paramLabel = new QLabel("参数传递演示区域", parent);
    m_paramLabel->setAlignment(Qt::AlignCenter);
    m_paramLabel->setStyleSheet("padding: 15px; background-color: #fff3e0; border-radius: 5px; font-size: 14px;");
    mainLayout->addWidget(m_paramLabel);
    
    // 说明
    QLabel *infoLabel = new QLabel(
        "演示要点：\n"
        "- SpinBox的valueChanged信号连接到Slider的setValue槽\n"
        "- Slider的valueChanged信号连接到SpinBox的setValue槽\n"
        "- 这样两者就实现了双向同步\n"
        "- 同样的方式应用到两个文本框",
        parent
    );
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("background-color: #f5f5f5; padding: 10px; border-radius: 5px;");
    mainLayout->addWidget(infoLabel);
}

/**
 * @brief Lambda表达式作为槽演示
 */
void SignalsSlotsDemo::setupLambdaDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QGroupBox *group = new QGroupBox("Lambda槽演示", parent);
    QVBoxLayout *layout = new QVBoxLayout(group);
    
    m_lambdaBtn1 = new QPushButton("使用Lambda (捕获this)", group);
    m_lambdaBtn2 = new QPushButton("使用Lambda (捕获计数器)", group);
    
    layout->addWidget(m_lambdaBtn1);
    layout->addWidget(m_lambdaBtn2);
    
    mainLayout->addWidget(group);
    
    m_lambdaLabel = new QLabel("等待操作...", parent);
    m_lambdaLabel->setAlignment(Qt::AlignCenter);
    m_lambdaLabel->setStyleSheet("padding: 15px; background-color: #f3e5f5; border-radius: 5px; font-size: 14px;");
    mainLayout->addWidget(m_lambdaLabel);
    
    // 说明
    QLabel *infoLabel = new QLabel(
        "Lambda表达式的优势：\n"
        "- 可以内联定义槽函数，无需单独声明\n"
        "- 可以捕获外部变量（值捕获或引用捕获）\n"
        "- 代码更简洁，逻辑更集中\n"
        "- 适合简单的操作",
        parent
    );
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("background-color: #f5f5f5; padding: 10px; border-radius: 5px;");
    mainLayout->addWidget(infoLabel);
}

/**
 * @brief 自定义信号演示
 */
void SignalsSlotsDemo::setupCustomSignalDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    // 创建自定义计数器对象
    m_counter = new Counter(this);
    
    // 控制区
    QGroupBox *controlGroup = new QGroupBox("计数器控制", parent);
    QHBoxLayout *controlLayout = new QHBoxLayout(controlGroup);
    
    m_incBtn = new QPushButton("增加", controlGroup);
    m_decBtn = new QPushButton("减少", controlGroup);
    
    controlLayout->addWidget(m_incBtn);
    controlLayout->addWidget(m_decBtn);

    // 设置值
    QHBoxLayout *setValueLayout = new QHBoxLayout();
    m_counterSpinBox = new QSpinBox(parent);
    m_counterSpinBox->setRange(-100, 100);
    m_counterSpinBox->setValue(0);
    m_setBtn = new QPushButton("设置值", parent);

    setValueLayout->addWidget(new QLabel("设置值为:"));
    setValueLayout->addWidget(m_counterSpinBox);
    setValueLayout->addWidget(m_setBtn);

    mainLayout->addWidget(controlGroup);
    mainLayout->addLayout(setValueLayout);
    
    // 显示区
    QGroupBox *displayGroup = new QGroupBox("计数器显示", parent);
    QVBoxLayout *displayLayout = new QVBoxLayout(displayGroup);
    
    m_counterLabel = new QLabel("当前值: 0", displayGroup);
    m_counterLabel->setAlignment(Qt::AlignCenter);
    m_counterLabel->setStyleSheet("font-size: 24px; font-weight: bold; padding: 20px;");
    
    displayLayout->addWidget(m_counterLabel);
    
    mainLayout->addWidget(displayGroup);
    
    // 说明
    QLabel *infoLabel = new QLabel(
        "自定义信号演示：\n"
        "- Counter类定义了三个自定义信号\n"
        "- valueChanged：值改变时发射\n"
        "- valueReached：值达到5的倍数时发射\n"
        "- exceededThreshold：值超过10时发射\n"
        "- 每个信号都连接到不同的槽函数",
        parent
    );
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("background-color: #f5f5f5; padding: 10px; border-radius: 5px;");
    mainLayout->addWidget(infoLabel);
}

/**
 * @brief 多重连接演示
 */
void SignalsSlotsDemo::setupMultipleDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QGroupBox *group = new QGroupBox("多重连接演示", parent);
    QVBoxLayout *layout = new QVBoxLayout(group);
    
    // 三个发送者连接到同一个槽
    layout->addWidget(new QLabel("三个按钮都连接到同一个槽函数："));
    
    m_sender1 = new QPushButton("发送者 1", group);
    m_sender2 = new QPushButton("发送者 2", group);
    m_sender3 = new QPushButton("发送者 3", group);
    
    layout->addWidget(m_sender1);
    layout->addWidget(m_sender2);
    layout->addWidget(m_sender3);
    
    layout->addSpacing(20);
    
    // 一个按钮连接到多个槽
    layout->addWidget(new QLabel("一个按钮触发多个操作："));
    m_commonBtn = new QPushButton("点击我 (触发多个槽)", group);
    layout->addWidget(m_commonBtn);
    
    mainLayout->addWidget(group);
    
    m_multiLabel = new QLabel("等待操作...", parent);
    m_multiLabel->setAlignment(Qt::AlignCenter);
    m_multiLabel->setStyleSheet("padding: 15px; background-color: #e8f5e9; border-radius: 5px; font-size: 14px;");
    mainLayout->addWidget(m_multiLabel);
}

/**
 * @brief 连接所有信号和槽
 */
void SignalsSlotsDemo::connectSignals()
{
    // ========== 基本演示 ==========
    connect(m_basicButton, &QPushButton::clicked, this, &SignalsSlotsDemo::onBasicButtonClicked);
    connect(m_checkbox, &QCheckBox::checkStateChanged, this, &SignalsSlotsDemo::onCheckboxStateChanged);
    
    connect(m_disconnectBtn, &QPushButton::clicked, [this]() {
        // 断开连接的示例
        bool disconnected = disconnect(m_basicButton, &QPushButton::clicked, 
                                        this, &SignalsSlotsDemo::onBasicButtonClicked);
        if (disconnected) {
            m_basicLabel->setText("连接已断开！按钮点击将不再触发槽函数。");
            addLog("断开了按钮的clicked信号与槽的连接");
        }
    });
    
    // ========== 参数传递演示 ==========
    // SpinBox和Slider双向同步
    connect(m_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
            this, &SignalsSlotsDemo::onSpinBoxChanged);
    connect(m_slider, &QSlider::valueChanged, 
            this, &SignalsSlotsDemo::onSliderChanged);
    
    // 两个文本框双向同步
    connect(m_lineEdit1, &QLineEdit::textChanged, 
            this, &SignalsSlotsDemo::onTextChanged);
    connect(m_lineEdit2, &QLineEdit::textChanged, 
            this, &SignalsSlotsDemo::onTextChanged2);
    
    // ========== Lambda演示 ==========
    // Lambda捕获this
    connect(m_lambdaBtn1, &QPushButton::clicked, this, [this]() {
        m_clickCount++;
        m_lambdaLabel->setText(QString("Lambda (捕获this) - 已点击 %1 次").arg(m_clickCount));
    });
    
    // Lambda捕获计数器
    connect(m_lambdaBtn2, &QPushButton::clicked, [this]() {
        static int count = 0;
        count++;
        m_lambdaLabel->setText(QString("Lambda (静态变量) - 已点击 %1 次").arg(count));
    });
    
    // ========== 自定义信号演示 ==========
    connect(m_counter, &Counter::valueChanged, 
            this, &SignalsSlotsDemo::onCounterValueChanged);
    connect(m_counter, &Counter::valueReached, 
            this, &SignalsSlotsDemo::onCounterValueReached);
    connect(m_counter, &Counter::exceededThreshold, 
            this, &SignalsSlotsDemo::onCounterExceededThreshold);
    
    connect(m_incBtn, &QPushButton::clicked, [this]() {
        m_counter->increment();
    });
    
    connect(m_decBtn, &QPushButton::clicked, [this]() {
        m_counter->decrement();
    });
    
    connect(m_setBtn, &QPushButton::clicked, [this]() {
        m_counter->setValue(m_counterSpinBox->value());
    });
    
    // ========== 多重连接演示 ==========
    // 三个发送者都连接到同一个公共槽（演示多个信号连接一个槽）
    connect(m_sender1, &QPushButton::clicked, this, &SignalsSlotsDemo::onCommonSlotClicked);
    connect(m_sender2, &QPushButton::clicked, this, &SignalsSlotsDemo::onCommonSlotClicked);
    connect(m_sender3, &QPushButton::clicked, this, &SignalsSlotsDemo::onCommonSlotClicked);

    // 一个信号连接到多个槽（使用Lambda）
    connect(m_commonBtn, &QPushButton::clicked, [this]() {
        m_multiLabel->setText("槽1: 按钮被点击了！");
        addLog("执行槽1: 显示消息");
    });

    connect(m_commonBtn, &QPushButton::clicked, [this]() {
        QMessageBox::information(this, "提示", "这是槽2弹出的对话框！");
        addLog("执行槽2: 弹出对话框");
    });

    connect(m_commonBtn, &QPushButton::clicked, [this]() {
        m_commonBtn->setText("再次点击");
        addLog("执行槽3: 修改按钮文本");
    });
}

/**
 * @brief 添加日志
 */
void SignalsSlotsDemo::addLog(const QString &message)
{
    QString timestamp = QTime::currentTime().toString("hh:mm:ss.zzz");
    m_logTextEdit->append(QString("[%1] %2").arg(timestamp, message));
}

/**
 * @brief 基本按钮点击槽
 */
void SignalsSlotsDemo::onBasicButtonClicked()
{
    m_basicLabel->setText("按钮被点击了！信号和槽机制工作正常。");
    addLog("收到按钮clicked信号，执行槽函数");
}

/**
 * @brief 复选框状态改变槽
 */
void SignalsSlotsDemo::onCheckboxStateChanged(Qt::CheckState state)
{
    QString status = (state == Qt::Checked) ? "已选中" : "未选中";
    m_basicLabel->setText(QString("复选框状态: %1").arg(status));
    addLog(QString("复选框状态改变: %1").arg(status));
}

/**
 * @brief SpinBox值改变槽
 */
void SignalsSlotsDemo::onSpinBoxChanged(int value)
{
    // 阻止信号循环：设置值前先断开连接，设置后再重新连接
    m_slider->blockSignals(true);
    m_slider->setValue(value);
    m_slider->blockSignals(false);
    
    m_paramLabel->setText(QString("SpinBox改变: %1").arg(value));
}

/**
 * @brief Slider值改变槽
 */
void SignalsSlotsDemo::onSliderChanged(int value)
{
    // 阻止信号循环
    m_spinBox->blockSignals(true);
    m_spinBox->setValue(value);
    m_spinBox->blockSignals(false);
    
    m_paramLabel->setText(QString("Slider改变: %1").arg(value));
}

/**
 * @brief 文本框1文本改变槽
 */
void SignalsSlotsDemo::onTextChanged(const QString &text)
{
    m_lineEdit2->blockSignals(true);
    m_lineEdit2->setText(text);
    m_lineEdit2->blockSignals(false);
    
    m_paramLabel->setText(QString("文本框1: %1 (长度: %2)").arg(text).arg(text.length()));
}

/**
 * @brief 文本框2文本改变槽
 */
void SignalsSlotsDemo::onTextChanged2(const QString &text)
{
    m_lineEdit1->blockSignals(true);
    m_lineEdit1->setText(text);
    m_lineEdit1->blockSignals(false);
    
    m_paramLabel->setText(QString("文本框2: %1 (长度: %2)").arg(text).arg(text.length()));
}

/**
 * @brief 计数器值改变槽
 */
void SignalsSlotsDemo::onCounterValueChanged(int value)
{
    m_counterLabel->setText(QString("当前值: %1").arg(value));
    addLog(QString("计数器值改变: %1").arg(value));
}

/**
 * @brief 计数器值达到特定值槽
 */
void SignalsSlotsDemo::onCounterValueReached(int value)
{
    m_counterLabel->setStyleSheet(
        "font-size: 24px; font-weight: bold; padding: 20px; color: red; background-color: #ffebee;"
    );
    addLog(QString("计数器达到 %1 (5的倍数)!").arg(value));
    
    // 1秒后恢复样式
    QTimer::singleShot(1000, this, [this]() {
        m_counterLabel->setStyleSheet("font-size: 24px; font-weight: bold; padding: 20px;");
    });
}

/**
 * @brief 计数器超过阈值槽
 */
void SignalsSlotsDemo::onCounterExceededThreshold(int value, int threshold)
{
    QMessageBox::warning(this, "警告", 
        QString("计数器值 %1 已超过阈值 %2！").arg(value).arg(threshold));
    addLog(QString("警告: 计数器值 %1 超过阈值 %2").arg(value).arg(threshold));
}

/**
 * @brief 发送者1点击槽
 */
void SignalsSlotsDemo::onSender1Clicked()
{
    m_multiLabel->setText("发送者1被点击了");
    addLog("收到sender1的clicked信号");
}

/**
 * @brief 发送者2点击槽
 */
void SignalsSlotsDemo::onSender2Clicked()
{
    m_multiLabel->setText("发送者2被点击了");
    addLog("收到sender2的clicked信号");
}

/**
 * @brief 发送者3点击槽
 */
void SignalsSlotsDemo::onSender3Clicked()
{
    m_multiLabel->setText("发送者3被点击了");
    addLog("收到sender3的clicked信号");
}

/**
 * @brief 公共槽函数 - 多个发送者连接到此槽
 */
void SignalsSlotsDemo::onCommonSlotClicked()
{
    // 获取发送者对象
    QPushButton *senderBtn = qobject_cast<QPushButton*>(sender());
    if (senderBtn) {
        QString senderName = senderBtn->text();
        m_multiLabel->setText(QString("%1 触发了公共槽函数").arg(senderName));
        addLog(QString("公共槽函数被 %1 触发").arg(senderName));
    }
}
