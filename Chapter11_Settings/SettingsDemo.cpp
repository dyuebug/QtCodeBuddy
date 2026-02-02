/**
 * @file SettingsDemo.cpp
 * @brief 第11章示例 - QSettings 配置存储演示实现
 */

#include "SettingsDemo.h"
#include <QSettings>
#include <QMessageBox>
#include <QCloseEvent>

SettingsDemo::SettingsDemo(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
    connectSignals();
    loadSettings();

    setWindowTitle("第11章：QSettings 配置存储");
    resize(450, 350);
}

SettingsDemo::~SettingsDemo()
{
}

void SettingsDemo::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 用户设置组
    QGroupBox *settingsGroup = new QGroupBox("用户设置", this);
    QFormLayout *formLayout = new QFormLayout(settingsGroup);

    m_usernameEdit = new QLineEdit(settingsGroup);
    m_usernameEdit->setPlaceholderText("输入用户名");
    formLayout->addRow("用户名:", m_usernameEdit);

    m_ageSpin = new QSpinBox(settingsGroup);
    m_ageSpin->setRange(1, 120);
    m_ageSpin->setValue(18);
    formLayout->addRow("年龄:", m_ageSpin);

    m_themeCombo = new QComboBox(settingsGroup);
    m_themeCombo->addItems({"浅色主题", "深色主题", "系统默认"});
    formLayout->addRow("主题:", m_themeCombo);

    m_rememberCheck = new QCheckBox("记住用户名", settingsGroup);
    formLayout->addRow("", m_rememberCheck);

    m_autoSaveCheck = new QCheckBox("自动保存设置", settingsGroup);
    formLayout->addRow("", m_autoSaveCheck);

    mainLayout->addWidget(settingsGroup);

    // 操作按钮
    QHBoxLayout *btnLayout = new QHBoxLayout();
    m_saveBtn = new QPushButton("保存设置", this);
    m_loadBtn = new QPushButton("加载设置", this);
    m_clearBtn = new QPushButton("清除设置", this);
    m_pathBtn = new QPushButton("显示路径", this);

    btnLayout->addWidget(m_saveBtn);
    btnLayout->addWidget(m_loadBtn);
    btnLayout->addWidget(m_clearBtn);
    btnLayout->addWidget(m_pathBtn);
    mainLayout->addLayout(btnLayout);

    // 状态显示
    m_statusLabel = new QLabel("就绪", this);
    m_statusLabel->setStyleSheet("padding: 10px; background: #e8f5e9; border-radius: 5px;");
    mainLayout->addWidget(m_statusLabel);
}

void SettingsDemo::connectSignals()
{
    connect(m_saveBtn, &QPushButton::clicked, this, &SettingsDemo::onSaveSettings);
    connect(m_loadBtn, &QPushButton::clicked, this, &SettingsDemo::onLoadSettings);
    connect(m_clearBtn, &QPushButton::clicked, this, &SettingsDemo::onClearSettings);
    connect(m_pathBtn, &QPushButton::clicked, this, &SettingsDemo::onShowSettingsPath);
}

void SettingsDemo::loadSettings()
{
    QSettings settings("MyCompany", "SettingsDemo");

    // 读取用户设置
    settings.beginGroup("User");
    m_usernameEdit->setText(settings.value("username", "").toString());
    m_ageSpin->setValue(settings.value("age", 18).toInt());
    settings.endGroup();

    // 读取界面设置
    settings.beginGroup("UI");
    m_themeCombo->setCurrentIndex(settings.value("theme", 0).toInt());
    m_rememberCheck->setChecked(settings.value("remember", false).toBool());
    m_autoSaveCheck->setChecked(settings.value("autoSave", false).toBool());
    settings.endGroup();

    // 恢复窗口状态
    settings.beginGroup("Window");
    if (settings.contains("geometry")) {
        restoreGeometry(settings.value("geometry").toByteArray());
    }
    settings.endGroup();

    m_statusLabel->setText("设置已加载");
}

void SettingsDemo::saveSettings()
{
    QSettings settings("MyCompany", "SettingsDemo");

    // 保存用户设置
    settings.beginGroup("User");
    settings.setValue("username", m_usernameEdit->text());
    settings.setValue("age", m_ageSpin->value());
    settings.endGroup();

    // 保存界面设置
    settings.beginGroup("UI");
    settings.setValue("theme", m_themeCombo->currentIndex());
    settings.setValue("remember", m_rememberCheck->isChecked());
    settings.setValue("autoSave", m_autoSaveCheck->isChecked());
    settings.endGroup();

    // 保存窗口状态
    settings.beginGroup("Window");
    settings.setValue("geometry", saveGeometry());
    settings.endGroup();
}

void SettingsDemo::onSaveSettings()
{
    saveSettings();
    m_statusLabel->setText("设置已保存");
}

void SettingsDemo::onLoadSettings()
{
    loadSettings();
}

void SettingsDemo::onClearSettings()
{
    QSettings settings("MyCompany", "SettingsDemo");
    settings.clear();

    m_usernameEdit->clear();
    m_ageSpin->setValue(18);
    m_themeCombo->setCurrentIndex(0);
    m_rememberCheck->setChecked(false);
    m_autoSaveCheck->setChecked(false);

    m_statusLabel->setText("设置已清除");
}

void SettingsDemo::onShowSettingsPath()
{
    QSettings settings("MyCompany", "SettingsDemo");
    QString path = settings.fileName();
    QMessageBox::information(this, "配置文件路径", path);
}

void SettingsDemo::closeEvent(QCloseEvent *event)
{
    if (m_autoSaveCheck->isChecked()) {
        saveSettings();
    }
    event->accept();
}
