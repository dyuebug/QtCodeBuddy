/**
 * @file AboutDialog.h
 * @brief 关于对话框
 *
 * 知识点：
 * - QDialog 简单对话框
 * - QLabel 富文本显示
 * - 应用程序信息展示
 */

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

/**
 * @class AboutDialog
 * @brief 关于对话框
 *
 * 显示应用程序的版本和版权信息
 */
class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog() override = default;

private:
    void setupUi();

private:
    QVBoxLayout *m_layout;
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_versionLabel;
    QLabel *m_descriptionLabel;
    QLabel *m_copyrightLabel;
    QPushButton *m_closeButton;
};

#endif // ABOUTDIALOG_H
