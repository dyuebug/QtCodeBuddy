/**
 * @file SettingsDemo.h
 * @brief 第11章示例 - QSettings 配置存储演示
 *
 * 本章学习要点：
 * 1. QSettings 基本用法
 * 2. 保存和读取各种数据类型
 * 3. 分组管理配置
 * 4. 窗口状态保存和恢复
 */

#ifndef SETTINGSDEMO_H
#define SETTINGSDEMO_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

class SettingsDemo : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsDemo(QWidget *parent = nullptr);
    ~SettingsDemo();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setupUi();
    void connectSignals();
    void loadSettings();
    void saveSettings();

private slots:
    void onSaveSettings();
    void onLoadSettings();
    void onClearSettings();
    void onShowSettingsPath();

private:
    // 用户设置部件
    QLineEdit *m_usernameEdit;
    QSpinBox *m_ageSpin;
    QComboBox *m_themeCombo;
    QCheckBox *m_rememberCheck;
    QCheckBox *m_autoSaveCheck;

    // 操作按钮
    QPushButton *m_saveBtn;
    QPushButton *m_loadBtn;
    QPushButton *m_clearBtn;
    QPushButton *m_pathBtn;

    // 状态显示
    QLabel *m_statusLabel;
};

#endif // SETTINGSDEMO_H
