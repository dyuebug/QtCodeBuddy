/**
 * @file StatusWidget.h
 * @brief 状态显示控件
 *
 * 知识点：
 * - QLabel 文本显示
 * - 状态栏信息展示
 * - 定时器自动清除
 */

#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QTimer>

/**
 * @class StatusWidget
 * @brief 状态显示控件
 *
 * 显示笔记统计信息和临时状态消息
 */
class StatusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatusWidget(QWidget *parent = nullptr);
    ~StatusWidget() override = default;

    // 状态信息
    void setNoteCount(int count);
    void setCategoryCount(int count);
    void setWordCount(int count);
    void setCharCount(int count);

    // 临时消息
    void showMessage(const QString &message, int timeout = 3000);
    void clearMessage();

private:
    void setupUi();

private:
    QHBoxLayout *m_layout;
    QLabel *m_noteCountLabel;
    QLabel *m_categoryCountLabel;
    QLabel *m_wordCountLabel;
    QLabel *m_charCountLabel;
    QLabel *m_messageLabel;
    QTimer *m_messageTimer;
};

#endif // STATUSWIDGET_H
