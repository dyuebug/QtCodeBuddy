/**
 * @file SettingsDialog.h
 * @brief 设置对话框
 *
 * 知识点：
 * - QSettings 配置存储
 * - QTabWidget 选项卡
 * - 应用程序设置管理
 */

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QFormLayout>

/**
 * @class SettingsDialog
 * @brief 设置对话框
 *
 * 管理应用程序的各项设置
 */
class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog() override = default;

private:
    void setupUi();
    void createGeneralTab();
    void createEditorTab();
    void connectSignals();
    void loadSettings();
    void saveSettings();

private slots:
    void onAccepted();

private:
    QVBoxLayout *m_mainLayout;
    QTabWidget *m_tabWidget;
    QDialogButtonBox *m_buttonBox;

    // 常规设置
    QCheckBox *m_autoSaveCheck;
    QSpinBox *m_autoSaveIntervalSpin;

    // 编辑器设置
    QComboBox *m_fontFamilyCombo;
    QSpinBox *m_fontSizeSpin;
    QCheckBox *m_wordWrapCheck;
};

#endif // SETTINGSDIALOG_H
