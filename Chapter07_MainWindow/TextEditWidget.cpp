/**
 * @file TextEditWidget.cpp
 * @brief 简单的文本编辑部件实现
 */

#include "TextEditWidget.h"

TextEditWidget::TextEditWidget(QWidget *parent)
    : QTextEdit(parent)
    , m_currentFont("Arial", 12)
{
    setFont(m_currentFont);
    setPlaceholderText("在这里输入文本...");
}

/**
 * @brief 获取字体
 */
QFont TextEditWidget::currentFont() const
{
    return m_currentFont;
}

/**
 * @brief 设置字体
 */
void TextEditWidget::setCurrentFont(const QFont &font)
{
    m_currentFont = font;
    QTextEdit::setCurrentFont(font);
}

/**
 * @brief 获取字体大小
 */
int TextEditWidget::fontSize() const
{
    return m_currentFont.pointSize();
}

/**
 * @brief 设置字体大小
 */
void TextEditWidget::setFontSize(int size)
{
    m_currentFont.setPointSize(size);
    QTextEdit::setFontPointSize(size);
}

/**
 * @brief 粗体
 */
void TextEditWidget::boldText(bool bold)
{
    m_currentFont.setBold(bold);
    QTextEdit::setFontWeight(bold ? QFont::Bold : QFont::Normal);
}

/**
 * @brief 斜体
 */
void TextEditWidget::italicText(bool italic)
{
    m_currentFont.setItalic(italic);
    QTextEdit::setFontItalic(italic);
}

/**
 * @brief 下划线
 */
void TextEditWidget::underlineText(bool underline)
{
    m_currentFont.setUnderline(underline);
    QTextEdit::setFontUnderline(underline);
}

/**
 * @brief 增大字体
 */
void TextEditWidget::increaseFontSize()
{
    int newSize = fontSize() + 2;
    setFontSize(newSize);
}

/**
 * @brief 减小字体
 */
void TextEditWidget::decreaseFontSize()
{
    int newSize = fontSize() - 2;
    if (newSize >= 6) {
        setFontSize(newSize);
    }
}

/**
 * @brief 清除格式
 */
void TextEditWidget::clearFormatting()
{
    m_currentFont = QFont("Arial", 12);
    setTextCursor(textCursor());
    selectAll();
    setCurrentCharFormat(QTextCharFormat());
    moveCursor(QTextCursor::End);
}
