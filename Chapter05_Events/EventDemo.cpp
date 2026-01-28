/**
 * @file EventDemo.cpp
 * @brief 第5章示例 - 事件处理演示实现
 */

#include "EventDemo.h"
#include <QApplication>
#include <QResizeEvent>
#include <QMoveEvent>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDateTime>
#include <QFocusEvent>

EventDemo::EventDemo(QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(nullptr)
    , m_clickLabel(nullptr)
    , m_mouseTracker(nullptr)
    , m_resetClickBtn(nullptr)
    , m_clearPathBtn(nullptr)
    , m_keyLineEdit(nullptr)
    , m_keyLog(nullptr)
    , m_clearKeyBtn(nullptr)
    , m_windowInfoLabel(nullptr)
    , m_timer(nullptr)
    , m_timerCount(0)
    , m_progressBar(nullptr)
    , m_timerLabel(nullptr)
    , m_intervalSpinBox(nullptr)
    , m_timerStartBtn(nullptr)
    , m_timerStopBtn(nullptr)
    , m_timerResetBtn(nullptr)
    , m_focusEdit1(nullptr)
    , m_focusEdit2(nullptr)
    , m_focusLabel(nullptr)
    , m_filteredEdit(nullptr)
    , m_filterCheckbox(nullptr)
    , m_filterLabel(nullptr)
    , m_eventLog(nullptr)
{
    setupUi();
    connectSignals();
    
    setWindowTitle("第5章：事件处理");
    resize(800, 600);
    
    // 初始化定时器
    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, &QTimer::timeout, this, &EventDemo::onTimerTimeout);
}

/**
 * @brief 设置主界面
 */
void EventDemo::setupUi()
{
    m_tabWidget = new QTabWidget(this);
    
    // 创建选项卡
    QWidget *mouseTab = new QWidget();
    QWidget *keyboardTab = new QWidget();
    QWidget *windowTab = new QWidget();
    QWidget *timerTab = new QWidget();
    QWidget *focusTab = new QWidget();
    QWidget *filterTab = new QWidget();
    
    setupMouseEventDemo(mouseTab);
    setupKeyboardEventDemo(keyboardTab);
    setupWindowEventDemo(windowTab);
    setupTimerEventDemo(timerTab);
    setupFocusEventDemo(focusTab);
    setupEventFilterDemo(filterTab);
    
    m_tabWidget->addTab(mouseTab, "鼠标事件");
    m_tabWidget->addTab(keyboardTab, "键盘事件");
    m_tabWidget->addTab(windowTab, "窗口事件");
    m_tabWidget->addTab(timerTab, "定时器事件");
    m_tabWidget->addTab(focusTab, "焦点事件");
    m_tabWidget->addTab(filterTab, "事件过滤");
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tabWidget);
}

/**
 * @brief 鼠标事件演示
 */
void EventDemo::setupMouseEventDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    // 可点击标签
    QGroupBox *clickGroup = new QGroupBox("点击计数器", parent);
    QVBoxLayout *clickLayout = new QVBoxLayout(clickGroup);
    
    m_clickLabel = new ClickLabel("点击我", clickGroup);
    m_resetClickBtn = new QPushButton("重置计数", clickGroup);
    
    clickLayout->addWidget(m_clickLabel);
    clickLayout->addWidget(m_resetClickBtn);
    
    mainLayout->addWidget(clickGroup);
    
    // 鼠标跟踪器
    QGroupBox *trackGroup = new QGroupBox("鼠标轨迹跟踪", parent);
    QVBoxLayout *trackLayout = new QVBoxLayout(trackGroup);
    
    m_mouseTracker = new MouseTracker(trackGroup);
    m_clearPathBtn = new QPushButton("清除轨迹", trackGroup);
    
    trackLayout->addWidget(m_mouseTracker);
    trackLayout->addWidget(m_clearPathBtn);
    
    mainLayout->addWidget(trackGroup);
}

/**
 * @brief 键盘事件演示
 */
void EventDemo::setupKeyboardEventDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);

    QLabel *infoLabel = new QLabel(
        "请在下方输入框中按任意键，将显示键盘事件信息。\n"
        "按ESC键可以清空日志。", parent
    );
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("background-color: #fffacd; padding: 10px; border-radius: 5px;");
    mainLayout->addWidget(infoLabel);

    m_keyLineEdit = new QLineEdit(parent);
    m_keyLineEdit->setPlaceholderText("在这里输入或按键...");
    // 为输入框安装事件过滤器，捕获键盘事件
    m_keyLineEdit->installEventFilter(this);
    mainLayout->addWidget(m_keyLineEdit);

    m_keyLog = new QTextEdit(parent);
    m_keyLog->setReadOnly(true);
    m_keyLog->setMaximumHeight(300);
    mainLayout->addWidget(m_keyLog);

    m_clearKeyBtn = new QPushButton("清空日志", parent);
    mainLayout->addWidget(m_clearKeyBtn);
}

/**
 * @brief 窗口事件演示
 */
void EventDemo::setupWindowEventDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QLabel *infoLabel = new QLabel(
        "调整窗口大小或移动窗口位置，将显示窗口事件信息。", parent
    );
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("background-color: #e0f7fa; padding: 10px; border-radius: 5px;");
    mainLayout->addWidget(infoLabel);
    
    m_windowInfoLabel = new QLabel("等待窗口事件...", parent);
    m_windowInfoLabel->setAlignment(Qt::AlignCenter);
    m_windowInfoLabel->setStyleSheet(
        "padding: 20px; background-color: #f5f5f5; border-radius: 10px; font-size: 14px;"
    );
    mainLayout->addWidget(m_windowInfoLabel);
}

/**
 * @brief 定时器事件演示
 */
void EventDemo::setupTimerEventDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    // 控制区
    QGroupBox *controlGroup = new QGroupBox("定时器控制", parent);
    QHBoxLayout *controlLayout = new QHBoxLayout(controlGroup);
    
    controlLayout->addWidget(new QLabel("间隔:"));
    m_intervalSpinBox = new QSpinBox(parent);
    m_intervalSpinBox->setRange(10, 5000);
    m_intervalSpinBox->setValue(100);
    m_intervalSpinBox->setSuffix(" ms");
    controlLayout->addWidget(m_intervalSpinBox);
    
    m_timerStartBtn = new QPushButton("开始", parent);
    m_timerStopBtn = new QPushButton("停止", parent);
    m_timerResetBtn = new QPushButton("重置", parent);
    
    controlLayout->addWidget(m_timerStartBtn);
    controlLayout->addWidget(m_timerStopBtn);
    controlLayout->addWidget(m_timerResetBtn);
    
    mainLayout->addWidget(controlGroup);
    
    // 显示区
    QGroupBox *displayGroup = new QGroupBox("定时器显示", parent);
    QVBoxLayout *displayLayout = new QVBoxLayout(displayGroup);
    
    m_timerLabel = new QLabel("计数: 0", displayGroup);
    m_timerLabel->setAlignment(Qt::AlignCenter);
    m_timerLabel->setStyleSheet("font-size: 24px; font-weight: bold; padding: 10px;");
    displayLayout->addWidget(m_timerLabel);
    
    m_progressBar = new QProgressBar(displayGroup);
    m_progressBar->setRange(0, 100);
    m_progressBar->setValue(0);
    displayLayout->addWidget(m_progressBar);
    
    mainLayout->addWidget(displayGroup);
}

/**
 * @brief 焦点事件演示
 */
void EventDemo::setupFocusEventDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QLabel *infoLabel = new QLabel(
        "点击不同的输入框，观察焦点变化。", parent
    );
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("background-color: #f3e5f5; padding: 10px; border-radius: 5px;");
    mainLayout->addWidget(infoLabel);
    
    QGroupBox *editGroup = new QGroupBox("输入框", parent);
    QVBoxLayout *editLayout = new QVBoxLayout(editGroup);
    
    m_focusEdit1 = new QLineEdit(editGroup);
    m_focusEdit1->setPlaceholderText("输入框 1");
    editLayout->addWidget(m_focusEdit1);
    
    m_focusEdit2 = new QLineEdit(editGroup);
    m_focusEdit2->setPlaceholderText("输入框 2");
    editLayout->addWidget(m_focusEdit2);
    
    mainLayout->addWidget(editGroup);
    
    m_focusLabel = new QLabel("等待焦点事件...", parent);
    m_focusLabel->setAlignment(Qt::AlignCenter);
    m_focusLabel->setStyleSheet("padding: 15px; background-color: #e8f5e9; border-radius: 5px; font-size: 14px;");
    mainLayout->addWidget(m_focusLabel);
}

/**
 * @brief 事件过滤演示
 */
void EventDemo::setupEventFilterDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QLabel *infoLabel = new QLabel(
        "勾选复选框后，输入框将过滤数字键。", parent
    );
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("background-color: #fff3e0; padding: 10px; border-radius: 5px;");
    mainLayout->addWidget(infoLabel);
    
    m_filterCheckbox = new QCheckBox("过滤数字键 (0-9)", parent);
    mainLayout->addWidget(m_filterCheckbox);
    
    m_filteredEdit = new QLineEdit(parent);
    m_filteredEdit->setPlaceholderText("在这里输入，勾选后数字键将不起作用");
    mainLayout->addWidget(m_filteredEdit);
    
    m_filterLabel = new QLabel("等待输入...", parent);
    m_filterLabel->setWordWrap(true);
    m_filterLabel->setStyleSheet("padding: 15px; background-color: #fce4ec; border-radius: 5px; font-size: 14px;");
    mainLayout->addWidget(m_filterLabel);
}

/**
 * @brief 连接信号和槽
 */
void EventDemo::connectSignals()
{
    // 鼠标事件
    connect(m_resetClickBtn, &QPushButton::clicked, this, &EventDemo::onResetClickCounts);
    connect(m_clearPathBtn, &QPushButton::clicked, this, &EventDemo::onClearMousePath);
    
    connect(m_clickLabel, &ClickLabel::leftClicked, [this]() {
        addLog("ClickLabel: 左键被点击");
    });
    
    connect(m_clickLabel, &ClickLabel::rightClicked, [this]() {
        addLog("ClickLabel: 右键被点击");
    });
    
    connect(m_clickLabel, &ClickLabel::doubleClicked, [this]() {
        addLog("ClickLabel: 双击被触发");
    });
    
    // 键盘事件
    connect(m_clearKeyBtn, &QPushButton::clicked, [this]() {
        m_keyLog->clear();
    });
    
    // 定时器事件
    connect(m_timerStartBtn, &QPushButton::clicked, this, &EventDemo::onTimerStart);
    connect(m_timerStopBtn, &QPushButton::clicked, this, &EventDemo::onTimerStop);
    connect(m_timerResetBtn, &QPushButton::clicked, this, &EventDemo::onTimerReset);
    
    // 事件过滤
    connect(m_filterCheckbox, &QCheckBox::stateChanged, this, &EventDemo::onFilterCheckboxChanged);
    
    // 为输入框安装事件过滤器
    m_filteredEdit->installEventFilter(this);
}

/**
 * @brief 添加日志
 */
void EventDemo::addLog(const QString &message)
{
    QString timestamp = QTime::currentTime().toString("hh:mm:ss.zzz");
    
    // 根据当前选项卡选择不同的日志输出
    int currentIndex = m_tabWidget->currentIndex();
    
    switch (currentIndex) {
        case 0: // 鼠标事件 - 无专用日志
            break;
        case 1: // 键盘事件
            m_keyLog->append(QString("[%1] %2").arg(timestamp, message));
            break;
        default:
            break;
    }
}

// ========== 重写的事件处理函数 ==========

/**
 * @brief 窗口大小改变事件
 */
void EventDemo::resizeEvent(QResizeEvent *event)
{
    if (m_tabWidget->currentIndex() == 2) {  // 窗口事件选项卡
        QString info = QString("窗口大小改变事件\n"
                               "旧大小: %1 x %2\n"
                               "新大小: %3 x %4")
            .arg(event->oldSize().width())
            .arg(event->oldSize().height())
            .arg(event->size().width())
            .arg(event->size().height());
        
        m_windowInfoLabel->setText(info);
    }
    
    QWidget::resizeEvent(event);
}

/**
 * @brief 窗口移动事件
 */
void EventDemo::moveEvent(QMoveEvent *event)
{
    if (m_tabWidget->currentIndex() == 2) {
        QString info = QString("窗口移动事件\n"
                               "旧位置: (%1, %2)\n"
                               "新位置: (%3, %4)")
            .arg(event->oldPos().x())
            .arg(event->oldPos().y())
            .arg(event->pos().x())
            .arg(event->pos().y());
        
        m_windowInfoLabel->setText(info);
    }
    
    QWidget::moveEvent(event);
}

/**
 * @brief 窗口关闭事件
 */
void EventDemo::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "确认关闭",
        "确定要关闭窗口吗？",
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        event->accept();  // 接受关闭事件
    } else {
        event->ignore();  // 忽略关闭事件
    }
}

/**
 * @brief 键盘按下事件
 */
void EventDemo::keyPressEvent(QKeyEvent *event)
{
    // 如果焦点在keyLineEdit上，显示按键信息
    if (QApplication::focusWidget() == m_keyLineEdit) {
        QString keyText = event->text();
        int keyCode = event->key();
        QString keyName = QKeySequence(keyCode).toString();
        
        QString modifiers;
        if (event->modifiers() & Qt::ControlModifier) modifiers += "Ctrl+";
        if (event->modifiers() & Qt::AltModifier) modifiers += "Alt+";
        if (event->modifiers() & Qt::ShiftModifier) modifiers += "Shift+";
        
        QString message = QString("按键: %1%2 | 键码: %3 | 文本: '%4'")
            .arg(modifiers).arg(keyName).arg(keyCode).arg(keyText);
        
        addLog(message);
        
        // ESC键清空日志
        if (keyCode == Qt::Key_Escape) {
            m_keyLog->clear();
        }
    }
    
    QWidget::keyPressEvent(event);
}

/**
 * @brief 重置点击计数
 */
void EventDemo::onResetClickCounts()
{
    m_clickLabel->resetCounts();
    addLog("重置点击计数");
}

/**
 * @brief 清除鼠标轨迹
 */
void EventDemo::onClearMousePath()
{
    m_mouseTracker->clearPath();
    addLog("清除鼠标轨迹");
}

/**
 * @brief 开始定时器
 */
void EventDemo::onTimerStart()
{
    m_timer->setInterval(m_intervalSpinBox->value());
    m_timer->start();
    addLog(QString("定时器开始，间隔: %1 ms").arg(m_timer->interval()));
}

/**
 * @brief 停止定时器
 */
void EventDemo::onTimerStop()
{
    m_timer->stop();
    addLog("定时器停止");
}

/**
 * @brief 重置定时器
 */
void EventDemo::onTimerReset()
{
    m_timer->stop();
    m_timerCount = 0;
    m_timerLabel->setText("计数: 0");
    m_progressBar->setValue(0);
    addLog("定时器重置");
}

/**
 * @brief 定时器超时槽函数
 */
void EventDemo::onTimerTimeout()
{
    m_timerCount++;
    m_timerLabel->setText(QString("计数: %1").arg(m_timerCount));
    
    // 更新进度条
    int progress = m_timerCount % 101;
    m_progressBar->setValue(progress);
    
    addLog(QString("定时器超时: %1").arg(m_timerCount));
}

/**
 * @brief 过滤复选框状态改变
 */
void EventDemo::onFilterCheckboxChanged(int state)
{
    if (state == Qt::Checked) {
        m_filterLabel->setText("数字键过滤已启用，尝试输入数字将不会显示");
    } else {
        m_filterLabel->setText("数字键过滤已关闭，所有按键正常工作");
    }
}

/**
 * @brief 事件过滤器
 */
bool EventDemo::eventFilter(QObject *watched, QEvent *event)
{
    // 处理keyLineEdit的键盘事件（用于键盘事件演示）
    if (watched == m_keyLineEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        QString keyText = keyEvent->text();
        int keyCode = keyEvent->key();
        QString keyName = QKeySequence(keyCode).toString();

        QString modifiers;
        if (keyEvent->modifiers() & Qt::ControlModifier) modifiers += "Ctrl+";
        if (keyEvent->modifiers() & Qt::AltModifier) modifiers += "Alt+";
        if (keyEvent->modifiers() & Qt::ShiftModifier) modifiers += "Shift+";

        QString message = QString("按键: %1%2 | 键码: %3 | 文本: '%4'")
            .arg(modifiers).arg(keyName).arg(keyCode).arg(keyText);

        addLog(message);

        // ESC键清空日志
        if (keyCode == Qt::Key_Escape) {
            m_keyLog->clear();
        }

        // 让事件继续传递，以便QLineEdit正常处理
        return QWidget::eventFilter(watched, event);
    }

    // 过滤filteredEdit的键盘事件
    if (watched == m_filteredEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        // 如果勾选了过滤，且按下的是数字键
        if (m_filterCheckbox->isChecked()) {
            if (keyEvent->key() >= Qt::Key_0 && keyEvent->key() <= Qt::Key_9) {
                QString keyText = keyEvent->text();
                m_filterLabel->setText(QString("已过滤数字键: '%1'").arg(keyText));
                return true;  // 返回true表示事件已被处理，不再传递
            }
        }

        m_filterLabel->setText(QString("按键: %1 (未被过滤)").arg(keyEvent->text()));
    }

    // 调用基类的事件过滤器
    return QWidget::eventFilter(watched, event);
}
