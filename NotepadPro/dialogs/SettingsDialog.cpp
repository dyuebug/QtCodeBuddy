/**
 * @file SettingsDialog.cpp
 * @brief 设置对话框实现
 */

#include "SettingsDialog.h"

#include <QFontDatabase>
#include <QSettings>
#include <QGroupBox>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("设置"));
    setMinimumSize(400, 300);
    setupUi();
    connectSignals();
    loadSettings();
}

void SettingsDialog::setupUi()
{
    m_mainLayout = new QVBoxLayout(this);

    m_tabWidget = new QTabWidget(this);
    createGeneralTab();
    createEditorTab();

    m_buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    m_mainLayout->addWidget(m_tabWidget);
    m_mainLayout->addWidget(m_buttonBox);
}

void SettingsDialog::createGeneralTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);

    QGroupBox *autoSaveGroup = new QGroupBox(tr("自动保存"), tab);
    QFormLayout *formLayout = new QFormLayout(autoSaveGroup);

    m_autoSaveCheck = new QCheckBox(tr("启用自动保存"), autoSaveGroup);
    m_autoSaveIntervalSpin = new QSpinBox(autoSaveGroup);
    m_autoSaveIntervalSpin->setRange(1, 60);
    m_autoSaveIntervalSpin->setSuffix(tr(" 分钟"));

    formLayout->addRow(m_autoSaveCheck);
    formLayout->addRow(tr("保存间隔:"), m_autoSaveIntervalSpin);

    layout->addWidget(autoSaveGroup);
    layout->addStretch();

    m_tabWidget->addTab(tab, tr("常规"));
}

void SettingsDialog::createEditorTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);

    QGroupBox *fontGroup = new QGroupBox(tr("字体"), tab);
    QFormLayout *formLayout = new QFormLayout(fontGroup);

    m_fontFamilyCombo = new QComboBox(fontGroup);
    QFontDatabase fontDb;
    m_fontFamilyCombo->addItems(fontDb.families());

    m_fontSizeSpin = new QSpinBox(fontGroup);
    m_fontSizeSpin->setRange(8, 48);

    m_wordWrapCheck = new QCheckBox(tr("自动换行"), fontGroup);

    formLayout->addRow(tr("字体:"), m_fontFamilyCombo);
    formLayout->addRow(tr("字号:"), m_fontSizeSpin);
    formLayout->addRow(m_wordWrapCheck);

    layout->addWidget(fontGroup);
    layout->addStretch();

    m_tabWidget->addTab(tab, tr("编辑器"));
}

void SettingsDialog::connectSignals()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted,
            this, &SettingsDialog::onAccepted);
    connect(m_buttonBox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
}

void SettingsDialog::loadSettings()
{
    QSettings settings;

    // 常规设置
    m_autoSaveCheck->setChecked(settings.value("autoSave/enabled", false).toBool());
    m_autoSaveIntervalSpin->setValue(settings.value("autoSave/interval", 5).toInt());

    // 编辑器设置
    m_fontFamilyCombo->setCurrentText(settings.value("editor/fontFamily", "Microsoft YaHei").toString());
    m_fontSizeSpin->setValue(settings.value("editor/fontSize", 12).toInt());
    m_wordWrapCheck->setChecked(settings.value("editor/wordWrap", true).toBool());
}

void SettingsDialog::saveSettings()
{
    QSettings settings;

    // 常规设置
    settings.setValue("autoSave/enabled", m_autoSaveCheck->isChecked());
    settings.setValue("autoSave/interval", m_autoSaveIntervalSpin->value());

    // 编辑器设置
    settings.setValue("editor/fontFamily", m_fontFamilyCombo->currentText());
    settings.setValue("editor/fontSize", m_fontSizeSpin->value());
    settings.setValue("editor/wordWrap", m_wordWrapCheck->isChecked());
}

void SettingsDialog::onAccepted()
{
    saveSettings();
    accept();
}
