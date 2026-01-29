/**
 * @file StatusWidget.cpp
 * @brief 状态显示控件实现
 */

#include "StatusWidget.h"

StatusWidget::StatusWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void StatusWidget::setupUi()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(4, 2, 4, 2);

    m_noteCountLabel = new QLabel(tr("笔记: 0"), this);
    m_categoryCountLabel = new QLabel(tr("分类: 0"), this);
    m_wordCountLabel = new QLabel(tr("字数: 0"), this);
    m_charCountLabel = new QLabel(tr("字符: 0"), this);
    m_messageLabel = new QLabel(this);

    m_layout->addWidget(m_noteCountLabel);
    m_layout->addWidget(m_categoryCountLabel);
    m_layout->addStretch();
    m_layout->addWidget(m_wordCountLabel);
    m_layout->addWidget(m_charCountLabel);
    m_layout->addStretch();
    m_layout->addWidget(m_messageLabel);

    // 消息定时器
    m_messageTimer = new QTimer(this);
    m_messageTimer->setSingleShot(true);
    connect(m_messageTimer, &QTimer::timeout,
            this, &StatusWidget::clearMessage);
}

void StatusWidget::setNoteCount(int count)
{
    m_noteCountLabel->setText(tr("笔记: %1").arg(count));
}

void StatusWidget::setCategoryCount(int count)
{
    m_categoryCountLabel->setText(tr("分类: %1").arg(count));
}

void StatusWidget::setWordCount(int count)
{
    m_wordCountLabel->setText(tr("字数: %1").arg(count));
}

void StatusWidget::setCharCount(int count)
{
    m_charCountLabel->setText(tr("字符: %1").arg(count));
}

void StatusWidget::showMessage(const QString &message, int timeout)
{
    m_messageLabel->setText(message);
    if (timeout > 0) {
        m_messageTimer->start(timeout);
    }
}

void StatusWidget::clearMessage()
{
    m_messageLabel->clear();
}
