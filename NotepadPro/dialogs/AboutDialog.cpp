/**
 * @file AboutDialog.cpp
 * @brief 关于对话框实现
 */

#include "AboutDialog.h"

#include <QApplication>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("关于 NotepadPro"));
    setFixedSize(350, 250);
    setupUi();
}

void AboutDialog::setupUi()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setAlignment(Qt::AlignCenter);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setPixmap(QApplication::windowIcon().pixmap(64, 64));
    m_iconLabel->setAlignment(Qt::AlignCenter);

    m_titleLabel = new QLabel(tr("<h2>NotepadPro</h2>"), this);
    m_titleLabel->setAlignment(Qt::AlignCenter);

    m_versionLabel = new QLabel(tr("版本 1.0.0"), this);
    m_versionLabel->setAlignment(Qt::AlignCenter);

    m_descriptionLabel = new QLabel(
        tr("一个功能完整的个人笔记本应用\n"
           "Qt6 综合学习项目"), this);
    m_descriptionLabel->setAlignment(Qt::AlignCenter);

    m_copyrightLabel = new QLabel(
        tr("Copyright © 2024"), this);
    m_copyrightLabel->setAlignment(Qt::AlignCenter);

    m_closeButton = new QPushButton(tr("关闭"), this);
    connect(m_closeButton, &QPushButton::clicked,
            this, &QDialog::accept);

    m_layout->addWidget(m_iconLabel);
    m_layout->addWidget(m_titleLabel);
    m_layout->addWidget(m_versionLabel);
    m_layout->addSpacing(10);
    m_layout->addWidget(m_descriptionLabel);
    m_layout->addWidget(m_copyrightLabel);
    m_layout->addSpacing(10);
    m_layout->addWidget(m_closeButton);
}
