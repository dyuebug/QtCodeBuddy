/**
 * @file DialogDemo.cpp
 * @brief 第6章示例 - 对话框演示实现
 */

#include "DialogDemo.h"
#include "CustomDialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QProgressDialog>
#include <QTimer>
#include <QApplication>

DialogDemo::DialogDemo(QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(nullptr)
    , m_infoBtn(nullptr)
    , m_questionBtn(nullptr)
    , m_warningBtn(nullptr)
    , m_criticalBtn(nullptr)
    , m_aboutBtn(nullptr)
    , m_openFileBtn(nullptr)
    , m_saveFileBtn(nullptr)
    , m_selectDirBtn(nullptr)
    , m_selectMultipleBtn(nullptr)
    , m_filePathLabel(nullptr)
    , m_selectColorBtn(nullptr)
    , m_selectFontBtn(nullptr)
    , m_colorFontLabel(nullptr)
    , m_colorEdit(nullptr)
    , m_fontEdit(nullptr)
    , m_getTextBtn(nullptr)
    , m_getIntBtn(nullptr)
    , m_getDoubleBtn(nullptr)
    , m_getItemBtn(nullptr)
    , m_inputResultLabel(nullptr)
    , m_startProgressBtn(nullptr)
    , m_progressStatusLabel(nullptr)
    , m_showCustomBtn(nullptr)
    , m_showModalBtn(nullptr)
    , m_showModelessBtn(nullptr)
    , m_customDialogResult(nullptr)
    , m_logTextEdit(nullptr)
{
    setupUi();
    connectSignals();
    
    setWindowTitle("第6章：对话框");
    resize(750, 550);
}

/**
 * @brief 设置主界面
 */
void DialogDemo::setupUi()
{
    m_tabWidget = new QTabWidget(this);
    
    // 创建选项卡
    QWidget *messageTab = new QWidget();
    QWidget *fileTab = new QWidget();
    QWidget *colorFontTab = new QWidget();
    QWidget *inputTab = new QWidget();
    QWidget *progressTab = new QWidget();
    QWidget *customTab = new QWidget();
    
    setupMessageDialogDemo(messageTab);
    setupFileDialogDemo(fileTab);
    setupColorFontDialogDemo(colorFontTab);
    setupInputDialogDemo(inputTab);
    setupProgressDialogDemo(progressTab);
    setupCustomDialogDemo(customTab);
    
    m_tabWidget->addTab(messageTab, "消息对话框");
    m_tabWidget->addTab(fileTab, "文件对话框");
    m_tabWidget->addTab(colorFontTab, "颜色字体");
    m_tabWidget->addTab(inputTab, "输入对话框");
    m_tabWidget->addTab(progressTab, "进度对话框");
    m_tabWidget->addTab(customTab, "自定义对话框");
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tabWidget);
}

/**
 * @brief 消息对话框演示
 */
void DialogDemo::setupMessageDialogDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QGroupBox *group = new QGroupBox("QMessageBox 演示", parent);
    QVBoxLayout *groupLayout = new QVBoxLayout(group);
    
    // 创建各种消息按钮
    m_infoBtn = new QPushButton("信息对话框", group);
    m_questionBtn = new QPushButton("提问对话框", group);
    m_warningBtn = new QPushButton("警告对话框", group);
    m_criticalBtn = new QPushButton("错误对话框", group);
    m_aboutBtn = new QPushButton("关于对话框", group);
    
    groupLayout->addWidget(m_infoBtn);
    groupLayout->addWidget(m_questionBtn);
    groupLayout->addWidget(m_warningBtn);
    groupLayout->addWidget(m_criticalBtn);
    groupLayout->addWidget(m_aboutBtn);
    
    mainLayout->addWidget(group);
    
    // 说明
    QLabel *infoLabel = new QLabel(
        "QMessageBox 提供了几种标准的消息对话框：\n"
        "- information(): 显示信息\n"
        "- question(): 提问用户\n"
        "- warning(): 显示警告\n"
        "- critical(): 显示严重错误\n"
        "- about(): 显示关于信息",
        parent
    );
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("background-color: #e3f2fd; padding: 10px; border-radius: 5px;");
    mainLayout->addWidget(infoLabel);
}

/**
 * @brief 文件对话框演示
 */
void DialogDemo::setupFileDialogDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QGroupBox *group = new QGroupBox("QFileDialog 演示", parent);
    QVBoxLayout *groupLayout = new QVBoxLayout(group);
    
    m_openFileBtn = new QPushButton("打开文件", group);
    m_saveFileBtn = new QPushButton("保存文件", group);
    m_selectDirBtn = new QPushButton("选择目录", group);
    m_selectMultipleBtn = new QPushButton("选择多个文件", group);
    
    groupLayout->addWidget(m_openFileBtn);
    groupLayout->addWidget(m_saveFileBtn);
    groupLayout->addWidget(m_selectDirBtn);
    groupLayout->addWidget(m_selectMultipleBtn);
    
    mainLayout->addWidget(group);
    
    m_filePathLabel = new QLabel("选择的文件/目录将显示在这里", parent);
    m_filePathLabel->setWordWrap(true);
    m_filePathLabel->setStyleSheet("padding: 10px; background-color: #f5f5f5; border-radius: 5px;");
    mainLayout->addWidget(m_filePathLabel);
}

/**
 * @brief 颜色和字体对话框演示
 */
void DialogDemo::setupColorFontDialogDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QGroupBox *group = new QGroupBox("QColorDialog & QFontDialog 演示", parent);
    QVBoxLayout *groupLayout = new QVBoxLayout(group);
    
    m_selectColorBtn = new QPushButton("选择颜色", group);
    m_selectFontBtn = new QPushButton("选择字体", group);
    
    groupLayout->addWidget(m_selectColorBtn);
    groupLayout->addWidget(m_selectFontBtn);
    
    mainLayout->addWidget(group);
    
    // 颜色和字体显示区
    QGroupBox *displayGroup = new QGroupBox("选择结果", parent);
    QVBoxLayout *displayLayout = new QVBoxLayout(displayGroup);
    
    displayLayout->addWidget(new QLabel("颜色:", parent));
    m_colorEdit = new QLineEdit(parent);
    m_colorEdit->setReadOnly(true);
    displayLayout->addWidget(m_colorEdit);
    
    displayLayout->addWidget(new QLabel("字体:", parent));
    m_fontEdit = new QLineEdit(parent);
    m_fontEdit->setReadOnly(true);
    displayLayout->addWidget(m_fontEdit);
    
    mainLayout->addWidget(displayGroup);
    
    m_colorFontLabel = new QLabel(parent);
    m_colorFontLabel->setMinimumHeight(60);
    m_colorFontLabel->setAlignment(Qt::AlignCenter);
    m_colorFontLabel->setText("预览文本");
    m_colorFontLabel->setStyleSheet("border: 2px solid #333; padding: 10px;");
    mainLayout->addWidget(m_colorFontLabel);
}

/**
 * @brief 输入对话框演示
 */
void DialogDemo::setupInputDialogDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QGroupBox *group = new QGroupBox("QInputDialog 演示", parent);
    QVBoxLayout *groupLayout = new QVBoxLayout(group);
    
    m_getTextBtn = new QPushButton("获取文本输入", group);
    m_getIntBtn = new QPushButton("获取整数输入", group);
    m_getDoubleBtn = new QPushButton("获取浮点数输入", group);
    m_getItemBtn = new QPushButton("从列表中选择", group);
    
    groupLayout->addWidget(m_getTextBtn);
    groupLayout->addWidget(m_getIntBtn);
    groupLayout->addWidget(m_getDoubleBtn);
    groupLayout->addWidget(m_getItemBtn);
    
    mainLayout->addWidget(group);
    
    m_inputResultLabel = new QLabel("等待输入...", parent);
    m_inputResultLabel->setAlignment(Qt::AlignCenter);
    m_inputResultLabel->setStyleSheet("padding: 15px; background-color: #f0f0f0; border-radius: 5px;");
    mainLayout->addWidget(m_inputResultLabel);
}

/**
 * @brief 进度对话框演示
 */
void DialogDemo::setupProgressDialogDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QGroupBox *group = new QGroupBox("QProgressDialog 演示", parent);
    QVBoxLayout *groupLayout = new QVBoxLayout(group);
    
    m_startProgressBtn = new QPushButton("开始进度演示", group);
    groupLayout->addWidget(m_startProgressBtn);
    
    mainLayout->addWidget(group);
    
    m_progressStatusLabel = new QLabel("点击按钮开始进度演示", parent);
    m_progressStatusLabel->setAlignment(Qt::AlignCenter);
    m_progressStatusLabel->setStyleSheet("padding: 15px; background-color: #fff3e0; border-radius: 5px;");
    mainLayout->addWidget(m_progressStatusLabel);
}

/**
 * @brief 自定义对话框演示
 */
void DialogDemo::setupCustomDialogDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);
    
    QGroupBox *group = new QGroupBox("自定义对话框演示", parent);
    QVBoxLayout *groupLayout = new QVBoxLayout(group);
    
    m_showCustomBtn = new QPushButton("使用静态方法显示", group);
    m_showModalBtn = new QPushButton("模态对话框", group);
    m_showModelessBtn = new QPushButton("非模态对话框", group);
    
    groupLayout->addWidget(m_showCustomBtn);
    groupLayout->addWidget(m_showModalBtn);
    groupLayout->addWidget(m_showModelessBtn);
    
    mainLayout->addWidget(group);
    
    m_customDialogResult = new QLabel("自定义对话框结果将显示在这里", parent);
    m_customDialogResult->setWordWrap(true);
    m_customDialogResult->setStyleSheet("padding: 15px; background-color: #e8f5e9; border-radius: 5px;");
    mainLayout->addWidget(m_customDialogResult);
}

/**
 * @brief 连接信号和槽
 */
void DialogDemo::connectSignals()
{
    // 消息对话框
    connect(m_infoBtn, &QPushButton::clicked, this, &DialogDemo::onInformationButton);
    connect(m_questionBtn, &QPushButton::clicked, this, &DialogDemo::onQuestionButton);
    connect(m_warningBtn, &QPushButton::clicked, this, &DialogDemo::onWarningButton);
    connect(m_criticalBtn, &QPushButton::clicked, this, &DialogDemo::onCriticalButton);
    connect(m_aboutBtn, &QPushButton::clicked, this, &DialogDemo::onAboutButton);
    
    // 文件对话框
    connect(m_openFileBtn, &QPushButton::clicked, this, &DialogDemo::onOpenFile);
    connect(m_saveFileBtn, &QPushButton::clicked, this, &DialogDemo::onSaveFile);
    connect(m_selectDirBtn, &QPushButton::clicked, this, &DialogDemo::onSelectDirectory);
    connect(m_selectMultipleBtn, &QPushButton::clicked, this, &DialogDemo::onSelectMultipleFiles);
    
    // 颜色和字体对话框
    connect(m_selectColorBtn, &QPushButton::clicked, this, &DialogDemo::onSelectColor);
    connect(m_selectFontBtn, &QPushButton::clicked, this, &DialogDemo::onSelectFont);
    
    // 输入对话框
    connect(m_getTextBtn, &QPushButton::clicked, this, &DialogDemo::onGetText);
    connect(m_getIntBtn, &QPushButton::clicked, this, &DialogDemo::onGetInt);
    connect(m_getDoubleBtn, &QPushButton::clicked, this, &DialogDemo::onGetDouble);
    connect(m_getItemBtn, &QPushButton::clicked, this, &DialogDemo::onGetItem);
    
    // 进度对话框
    connect(m_startProgressBtn, &QPushButton::clicked, this, &DialogDemo::onStartProgress);
    
    // 自定义对话框
    connect(m_showCustomBtn, &QPushButton::clicked, this, &DialogDemo::onShowCustomDialog);
    connect(m_showModalBtn, &QPushButton::clicked, this, &DialogDemo::onShowCustomDialogModal);
    connect(m_showModelessBtn, &QPushButton::clicked, this, &DialogDemo::onShowCustomDialogModeless);
}

// ========== 消息对话框槽函数 ==========

void DialogDemo::onInformationButton()
{
    QMessageBox::information(this, "信息", "这是一个信息对话框");
    addLog("显示了信息对话框");
}

void DialogDemo::onQuestionButton()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "提问",
        "你确定要继续吗？",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
    );
    
    QString result;
    switch (reply) {
        case QMessageBox::Yes:
            result = "用户选择了：是";
            break;
        case QMessageBox::No:
            result = "用户选择了：否";
            break;
        case QMessageBox::Cancel:
            result = "用户选择了：取消";
            break;
        default:
            result = "用户关闭了对话框";
    }
    
    QMessageBox::information(this, "结果", result);
    addLog(result);
}

void DialogDemo::onWarningButton()
{
    QMessageBox::warning(this, "警告", "这是一个警告对话框");
    addLog("显示了警告对话框");
}

void DialogDemo::onCriticalButton()
{
    QMessageBox::critical(this, "错误", "这是一个错误对话框");
    addLog("显示了错误对话框");
}

void DialogDemo::onAboutButton()
{
    QMessageBox::about(
        this,
        "关于",
        "Qt6对话框演示程序\n"
        "版本：1.0.0\n"
        "作者：Qt学习者\n\n"
        "本程序展示了Qt6中各种对话框的使用方法。"
    );
    addLog("显示了关于对话框");
}

// ========== 文件对话框槽函数 ==========

void DialogDemo::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "打开文件",
        "",
        "文本文件 (*.txt);;所有文件 (*.*)"
    );
    
    if (!fileName.isEmpty()) {
        m_filePathLabel->setText(QString("打开的文件：%1").arg(fileName));
        addLog(QString("打开文件：%1").arg(fileName));
    }
}

void DialogDemo::onSaveFile()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "保存文件",
        "",
        "文本文件 (*.txt);;所有文件 (*.*)"
    );
    
    if (!fileName.isEmpty()) {
        m_filePathLabel->setText(QString("保存的文件：%1").arg(fileName));
        addLog(QString("保存文件：%1").arg(fileName));
    }
}

void DialogDemo::onSelectDirectory()
{
    QString dir = QFileDialog::getExistingDirectory(
        this,
        "选择目录",
        ""
    );
    
    if (!dir.isEmpty()) {
        m_filePathLabel->setText(QString("选择的目录：%1").arg(dir));
        addLog(QString("选择目录：%1").arg(dir));
    }
}

void DialogDemo::onSelectMultipleFiles()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(
        this,
        "选择多个文件",
        "",
        "文本文件 (*.txt);;所有文件 (*.*)"
    );
    
    if (!fileNames.isEmpty()) {
        m_filePathLabel->setText(QString("选择了 %1 个文件：\n%2")
            .arg(fileNames.size())
            .arg(fileNames.join("\n")));
        addLog(QString("选择了 %1 个文件").arg(fileNames.size()));
    }
}

// ========== 颜色和字体对话框槽函数 ==========

void DialogDemo::onSelectColor()
{
    QColor color = QColorDialog::getColor(Qt::blue, this, "选择颜色");
    
    if (color.isValid()) {
        m_colorEdit->setText(color.name());
        m_colorFontLabel->setStyleSheet(QString(
            "border: 2px solid %1; padding: 10px; background-color: %2;"
        ).arg(color.name(), color.name()));
        addLog(QString("选择颜色：%1").arg(color.name()));
    }
}

void DialogDemo::onSelectFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Arial", 12), this, "选择字体");
    
    if (ok) {
        m_fontEdit->setText(QString("%1, %2pt").arg(font.family()).arg(font.pointSize()));
        m_colorFontLabel->setFont(font);
        m_colorFontLabel->setText("预览文本");
        addLog(QString("选择字体：%1, %2pt").arg(font.family()).arg(font.pointSize()));
    }
}

// ========== 输入对话框槽函数 ==========

void DialogDemo::onGetText()
{
    bool ok;
    QString text = QInputDialog::getText(
        this,
        "输入文本",
        "请输入你的名字：",
        QLineEdit::Normal,
        "",
        &ok
    );
    
    if (ok && !text.isEmpty()) {
        m_inputResultLabel->setText(QString("你输入的名字是：%1").arg(text));
        addLog(QString("文本输入：%1").arg(text));
    }
}

void DialogDemo::onGetInt()
{
    bool ok;
    int value = QInputDialog::getInt(
        this,
        "输入整数",
        "请输入一个整数：",
        0,
        -100,
        100,
        1,
        &ok
    );
    
    if (ok) {
        m_inputResultLabel->setText(QString("你输入的整数是：%1").arg(value));
        addLog(QString("整数输入：%1").arg(value));
    }
}

void DialogDemo::onGetDouble()
{
    bool ok;
    double value = QInputDialog::getDouble(
        this,
        "输入浮点数",
        "请输入一个浮点数：",
        0.0,
        -100.0,
        100.0,
        2,
        &ok
    );
    
    if (ok) {
        m_inputResultLabel->setText(QString("你输入的浮点数是：%1").arg(value));
        addLog(QString("浮点数输入：%1").arg(value));
    }
}

void DialogDemo::onGetItem()
{
    QStringList items;
    items << "苹果" << "香蕉" << "橘子" << "葡萄" << "西瓜";
    
    bool ok;
    QString item = QInputDialog::getItem(
        this,
        "选择水果",
        "请选择一种水果：",
        items,
        0,
        false,
        &ok
    );
    
    if (ok && !item.isEmpty()) {
        m_inputResultLabel->setText(QString("你选择的水果是：%1").arg(item));
        addLog(QString("列表选择：%1").arg(item));
    }
}

// ========== 进度对话框槽函数 ==========

void DialogDemo::onStartProgress()
{
    QProgressDialog progress("正在处理...", "取消", 0, 100, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setWindowTitle("进度");
    
    for (int i = 0; i <= 100; i++) {
        progress.setValue(i);
        m_progressStatusLabel->setText(QString("处理进度：%1%").arg(i));
        addLog(QString("进度：%1%").arg(i));
        
        if (progress.wasCanceled()) {
            m_progressStatusLabel->setText("进度已取消");
            addLog("进度已取消");
            return;
        }
        
        // 模拟耗时操作
        QThread::msleep(50);
    }
    
    m_progressStatusLabel->setText("处理完成！");
    addLog("处理完成");
}

// ========== 自定义对话框槽函数 ==========

void DialogDemo::onShowCustomDialog()
{
    QDialog::DialogCode result = CustomDialog::showModal(this);
    
    if (result == QDialog::Accepted) {
        m_customDialogResult->setText("用户点击了确定按钮");
        addLog("自定义对话框：用户点击确定");
    } else {
        m_customDialogResult->setText("用户点击了取消按钮");
        addLog("自定义对话框：用户点击取消");
    }
}

void DialogDemo::onShowCustomDialogModal()
{
    CustomDialog dialog(this);
    
    if (dialog.exec() == QDialog::Accepted) {
        QString info = QString(
            "用户信息：\n"
            "用户名：%1\n"
            "年龄：%2\n"
            "职业：%3\n"
            "备注：%4"
        ).arg(dialog.username())
         .arg(dialog.age())
         .arg(dialog.profession())
         .arg(dialog.notes());
        
        m_customDialogResult->setText(info);
        addLog("模态对话框：用户确认");
    } else {
        m_customDialogResult->setText("用户取消了对话框");
        addLog("模态对话框：用户取消");
    }
}

void DialogDemo::onShowCustomDialogModeless()
{
    CustomDialog *dialog = new CustomDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);  // 关闭时自动删除
    dialog->show();  // 非模态显示
    
    m_customDialogResult->setText("已打开非模态对话框，可以同时操作其他窗口");
    addLog("非模态对话框：已打开");
}

/**
 * @brief 添加日志
 */
void DialogDemo::addLog(const QString &message)
{
    QString timestamp = QTime::currentTime().toString("hh:mm:ss.zzz");
    m_logTextEdit->append(QString("[%1] %2").arg(timestamp, message));
}
