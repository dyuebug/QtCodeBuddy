/**
 * @file FileIODemo.cpp
 * @brief 第10章示例 - 文件操作演示实现
 */

#include "FileIODemo.h"
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QDir>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QStandardPaths>

FileIODemo::FileIODemo(QWidget *parent)
    : QWidget(parent)
    , m_tabWidget(nullptr)
    , m_textEdit(nullptr)
    , m_filePathEdit(nullptr)
    , m_writeBtn(nullptr)
    , m_readBtn(nullptr)
    , m_appendBtn(nullptr)
    , m_nameEdit(nullptr)
    , m_ageEdit(nullptr)
    , m_binaryPathEdit(nullptr)
    , m_writeBinaryBtn(nullptr)
    , m_readBinaryBtn(nullptr)
    , m_binaryResultLabel(nullptr)
    , m_dirPathEdit(nullptr)
    , m_browseDirBtn(nullptr)
    , m_createDirBtn(nullptr)
    , m_listFilesBtn(nullptr)
    , m_fileListWidget(nullptr)
    , m_logTextEdit(nullptr)
{
    setupUi();
    connectSignals();

    setWindowTitle("第10章：文件操作");
    resize(750, 600);
}

void FileIODemo::setupUi()
{
    m_tabWidget = new QTabWidget(this);

    QWidget *textTab = new QWidget();
    QWidget *binaryTab = new QWidget();
    QWidget *dirTab = new QWidget();

    setupTextFileDemo(textTab);
    setupBinaryFileDemo(binaryTab);
    setupDirDemo(dirTab);

    m_tabWidget->addTab(textTab, "文本文件");
    m_tabWidget->addTab(binaryTab, "二进制文件");
    m_tabWidget->addTab(dirTab, "目录操作");

    // 日志区域
    m_logTextEdit = new QTextEdit(this);
    m_logTextEdit->setReadOnly(true);
    m_logTextEdit->setMaximumHeight(120);
    m_logTextEdit->setPlaceholderText("操作日志...");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tabWidget);
    mainLayout->addWidget(new QLabel("操作日志:", this));
    mainLayout->addWidget(m_logTextEdit);
}

/**
 * @brief 设置文本文件演示界面
 */
void FileIODemo::setupTextFileDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);

    // 文件路径
    QGroupBox *pathGroup = new QGroupBox("文件路径", parent);
    QHBoxLayout *pathLayout = new QHBoxLayout(pathGroup);
    m_filePathEdit = new QLineEdit(pathGroup);
    m_filePathEdit->setText(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/test.txt");
    pathLayout->addWidget(m_filePathEdit);
    mainLayout->addWidget(pathGroup);

    // 文本编辑区
    QGroupBox *editGroup = new QGroupBox("文本内容", parent);
    QVBoxLayout *editLayout = new QVBoxLayout(editGroup);
    m_textEdit = new QTextEdit(editGroup);
    m_textEdit->setPlaceholderText("在此输入要写入文件的内容...");
    editLayout->addWidget(m_textEdit);
    mainLayout->addWidget(editGroup);

    // 操作按钮
    QHBoxLayout *btnLayout = new QHBoxLayout();
    m_writeBtn = new QPushButton("写入文件", parent);
    m_readBtn = new QPushButton("读取文件", parent);
    m_appendBtn = new QPushButton("追加内容", parent);
    btnLayout->addWidget(m_writeBtn);
    btnLayout->addWidget(m_readBtn);
    btnLayout->addWidget(m_appendBtn);
    mainLayout->addLayout(btnLayout);
}

/**
 * @brief 设置二进制文件演示界面
 */
void FileIODemo::setupBinaryFileDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);

    // 文件路径
    QGroupBox *pathGroup = new QGroupBox("二进制文件路径", parent);
    QHBoxLayout *pathLayout = new QHBoxLayout(pathGroup);
    m_binaryPathEdit = new QLineEdit(pathGroup);
    m_binaryPathEdit->setText(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/data.bin");
    pathLayout->addWidget(m_binaryPathEdit);
    mainLayout->addWidget(pathGroup);

    // 数据输入
    QGroupBox *dataGroup = new QGroupBox("数据输入", parent);
    QFormLayout *formLayout = new QFormLayout(dataGroup);
    m_nameEdit = new QLineEdit(dataGroup);
    m_nameEdit->setPlaceholderText("输入姓名");
    m_ageEdit = new QLineEdit(dataGroup);
    m_ageEdit->setPlaceholderText("输入年龄");
    formLayout->addRow("姓名:", m_nameEdit);
    formLayout->addRow("年龄:", m_ageEdit);
    mainLayout->addWidget(dataGroup);

    // 操作按钮
    QHBoxLayout *btnLayout = new QHBoxLayout();
    m_writeBinaryBtn = new QPushButton("写入二进制", parent);
    m_readBinaryBtn = new QPushButton("读取二进制", parent);
    btnLayout->addWidget(m_writeBinaryBtn);
    btnLayout->addWidget(m_readBinaryBtn);
    mainLayout->addLayout(btnLayout);

    // 结果显示
    m_binaryResultLabel = new QLabel("读取结果将显示在这里", parent);
    m_binaryResultLabel->setStyleSheet("padding: 10px; background: #f0f0f0; border-radius: 5px;");
    mainLayout->addWidget(m_binaryResultLabel);
}

/**
 * @brief 设置目录操作演示界面
 */
void FileIODemo::setupDirDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);

    // 目录路径
    QGroupBox *pathGroup = new QGroupBox("目录路径", parent);
    QHBoxLayout *pathLayout = new QHBoxLayout(pathGroup);
    m_dirPathEdit = new QLineEdit(pathGroup);
    m_dirPathEdit->setText(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    m_browseDirBtn = new QPushButton("浏览...", pathGroup);
    pathLayout->addWidget(m_dirPathEdit);
    pathLayout->addWidget(m_browseDirBtn);
    mainLayout->addWidget(pathGroup);

    // 操作按钮
    QHBoxLayout *btnLayout = new QHBoxLayout();
    m_createDirBtn = new QPushButton("创建子目录", parent);
    m_listFilesBtn = new QPushButton("列出文件", parent);
    btnLayout->addWidget(m_createDirBtn);
    btnLayout->addWidget(m_listFilesBtn);
    mainLayout->addLayout(btnLayout);

    // 文件列表
    QGroupBox *listGroup = new QGroupBox("文件列表", parent);
    QVBoxLayout *listLayout = new QVBoxLayout(listGroup);
    m_fileListWidget = new QListWidget(listGroup);
    listLayout->addWidget(m_fileListWidget);
    mainLayout->addWidget(listGroup);
}

/**
 * @brief 连接信号和槽
 */
void FileIODemo::connectSignals()
{
    // 文本文件操作
    connect(m_writeBtn, &QPushButton::clicked, this, &FileIODemo::onWriteTextFile);
    connect(m_readBtn, &QPushButton::clicked, this, &FileIODemo::onReadTextFile);
    connect(m_appendBtn, &QPushButton::clicked, this, &FileIODemo::onAppendTextFile);

    // 二进制文件操作
    connect(m_writeBinaryBtn, &QPushButton::clicked, this, &FileIODemo::onWriteBinaryFile);
    connect(m_readBinaryBtn, &QPushButton::clicked, this, &FileIODemo::onReadBinaryFile);

    // 目录操作
    connect(m_browseDirBtn, &QPushButton::clicked, this, &FileIODemo::onBrowseDir);
    connect(m_createDirBtn, &QPushButton::clicked, this, &FileIODemo::onCreateDir);
    connect(m_listFilesBtn, &QPushButton::clicked, this, &FileIODemo::onListFiles);
}

/**
 * @brief 添加日志
 */
void FileIODemo::addLog(const QString &message)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    m_logTextEdit->append(QString("[%1] %2").arg(timestamp, message));
}

/**
 * @brief 写入文本文件
 *
 * 使用 QFile + QTextStream 写入文本
 */
void FileIODemo::onWriteTextFile()
{
    QString filePath = m_filePathEdit->text();
    QString content = m_textEdit->toPlainText();

    if (content.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入要写入的内容");
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        addLog("无法打开文件: " + file.errorString());
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    out << content;
    file.close();

    addLog("文件写入成功: " + filePath);
}

/**
 * @brief 读取文本文件
 */
void FileIODemo::onReadTextFile()
{
    QString filePath = m_filePathEdit->text();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        addLog("无法打开文件: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);
    QString content = in.readAll();
    file.close();

    m_textEdit->setText(content);
    addLog("文件读取成功: " + filePath);
}

/**
 * @brief 追加文本到文件
 */
void FileIODemo::onAppendTextFile()
{
    QString filePath = m_filePathEdit->text();
    QString content = m_textEdit->toPlainText();

    if (content.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入要追加的内容");
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        addLog("无法打开文件: " + file.errorString());
        return;
    }

    QTextStream out(&file);
    out << "\n" << content;
    file.close();

    addLog("内容追加成功: " + filePath);
}

/**
 * @brief 写入二进制文件
 */
void FileIODemo::onWriteBinaryFile()
{
    QString filePath = m_binaryPathEdit->text();
    QString name = m_nameEdit->text();
    int age = m_ageEdit->text().toInt();

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        addLog("无法打开文件: " + file.errorString());
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_0);
    out << name << age;
    file.close();

    addLog("二进制写入成功: " + filePath);
}

/**
 * @brief 读取二进制文件
 */
void FileIODemo::onReadBinaryFile()
{
    QString filePath = m_binaryPathEdit->text();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        addLog("无法打开文件: " + file.errorString());
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_0);

    QString name;
    int age;
    in >> name >> age;
    file.close();

    m_binaryResultLabel->setText(QString("姓名: %1, 年龄: %2").arg(name).arg(age));
    addLog("二进制读取成功");
}

/**
 * @brief 浏览目录
 */
void FileIODemo::onBrowseDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, "选择目录", m_dirPathEdit->text());
    if (!dir.isEmpty()) {
        m_dirPathEdit->setText(dir);
        addLog("选择目录: " + dir);
    }
}

/**
 * @brief 创建子目录
 */
void FileIODemo::onCreateDir()
{
    QString parentPath = m_dirPathEdit->text();
    QDir dir(parentPath);

    QString newDirName = "NewFolder_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

    if (dir.mkdir(newDirName)) {
        addLog("创建目录成功: " + newDirName);
        onListFiles();
    } else {
        addLog("创建目录失败");
    }
}

/**
 * @brief 列出目录中的文件
 */
void FileIODemo::onListFiles()
{
    QString dirPath = m_dirPathEdit->text();
    QDir dir(dirPath);

    if (!dir.exists()) {
        addLog("目录不存在: " + dirPath);
        return;
    }

    m_fileListWidget->clear();

    QFileInfoList fileList = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
    for (const QFileInfo &info : fileList) {
        QString itemText;
        if (info.isDir()) {
            itemText = "[目录] " + info.fileName();
        } else {
            itemText = info.fileName() + " (" + QString::number(info.size()) + " bytes)";
        }
        m_fileListWidget->addItem(itemText);
    }

    addLog(QString("列出 %1 个项目").arg(fileList.size()));
}
