/**
 * @file TextEditWidget.h
 * @brief 简单的文本编辑部件
 * 
 * 学习要点：
 * 1. 如何创建一个可重用的文本编辑部件
 * 2. 文本编辑的基本功能
 */

#ifndef TEXTEDITWIDGET_H
#define TEXTEDITWIDGET_H

#include <QTextEdit>
#include <QFont>
#include <QAction>

/**
 * @class TextEditWidget
 * @brief 一个简单的文本编辑器部件
 */
class TextEditWidget : public QTextEdit
{
    Q_OBJECT

public:
    explicit TextEditWidget(QWidget *parent = nullptr);
    
    /**
     * @brief 获取字体
     */
    QFont currentFont() const;
    
    /**
     * @brief 设置字体
     */
    void setCurrentFont(const QFont &font);
    
    /**
     * @brief 获取字体大小
     */
    int fontSize() const;
    
    /**
     * @brief 设置字体大小
     */
    void setFontSize(int size);

public slots:
    void boldText(bool bold);
    void italicText(bool italic);
    void underlineText(bool underline);
    void increaseFontSize();
    void decreaseFontSize();
    void clearFormatting();

private:
    QFont m_currentFont;
};

#endif // TEXTEDITWIDGET_H
