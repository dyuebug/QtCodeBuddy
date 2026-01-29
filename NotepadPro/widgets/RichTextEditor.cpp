/**
 * @file RichTextEditor.cpp
 * @brief 富文本编辑器控件实现
 */

#include "RichTextEditor.h"

#include <QColorDialog>
#include <QFontDatabase>
#include <QFrame>
#include <QPushButton>

RichTextEditor::RichTextEditor(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
    createToolBar();
    connectSignals();
}

void RichTextEditor::setupUi()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    m_textEdit = new QTextEdit(this);
    m_textEdit->setAcceptRichText(true);
}

/**
 * @brief 创建格式工具栏
 *
 * 使用 QWidget + QHBoxLayout 代替 QToolBar，
 * 避免被 QMainWindow 自动吸收到主工具栏区域
 */
void RichTextEditor::createToolBar()
{
    // 创建工具栏容器（使用 QWidget 而非 QToolBar）
    m_toolBarWidget = new QWidget(this);
    m_toolBarLayout = new QHBoxLayout(m_toolBarWidget);
    m_toolBarLayout->setContentsMargins(2, 2, 2, 2);
    m_toolBarLayout->setSpacing(2);

    // 字体选择
    m_fontFamilyCombo = new QComboBox(m_toolBarWidget);
    m_fontFamilyCombo->setMaximumWidth(150);
    QFontDatabase fontDb;
    m_fontFamilyCombo->addItems(fontDb.families());
    m_fontFamilyCombo->setCurrentText(m_textEdit->font().family());
    m_toolBarLayout->addWidget(m_fontFamilyCombo);

    // 字号选择
    m_fontSizeSpin = new QSpinBox(m_toolBarWidget);
    m_fontSizeSpin->setRange(6, 72);
    m_fontSizeSpin->setValue(12);
    m_toolBarLayout->addWidget(m_fontSizeSpin);

    // 分隔符
    QFrame *sep1 = new QFrame(m_toolBarWidget);
    sep1->setFrameShape(QFrame::VLine);
    m_toolBarLayout->addWidget(sep1);

    // 粗体
    m_boldAction = new QAction(tr("粗体"), this);
    m_boldAction->setCheckable(true);
    m_boldAction->setShortcut(QKeySequence::Bold);
    m_boldBtn = new QPushButton(tr("B"), m_toolBarWidget);
    m_boldBtn->setCheckable(true);
    m_boldBtn->setMaximumWidth(30);
    m_boldBtn->setFont(QFont("", -1, QFont::Bold));
    // 点击按钮时触发 Action
    connect(m_boldBtn, &QPushButton::clicked, m_boldAction, &QAction::trigger);
    m_toolBarLayout->addWidget(m_boldBtn);

    // 斜体
    m_italicAction = new QAction(tr("斜体"), this);
    m_italicAction->setCheckable(true);
    m_italicAction->setShortcut(QKeySequence::Italic);
    m_italicBtn = new QPushButton(tr("I"), m_toolBarWidget);
    m_italicBtn->setCheckable(true);
    m_italicBtn->setMaximumWidth(30);
    m_italicBtn->setFont(QFont("", -1, -1, true));
    connect(m_italicBtn, &QPushButton::clicked, m_italicAction, &QAction::trigger);
    m_toolBarLayout->addWidget(m_italicBtn);

    // 下划线
    m_underlineAction = new QAction(tr("下划线"), this);
    m_underlineAction->setCheckable(true);
    m_underlineAction->setShortcut(QKeySequence::Underline);
    m_underlineBtn = new QPushButton(tr("U"), m_toolBarWidget);
    m_underlineBtn->setCheckable(true);
    m_underlineBtn->setMaximumWidth(30);
    connect(m_underlineBtn, &QPushButton::clicked, m_underlineAction, &QAction::trigger);
    m_toolBarLayout->addWidget(m_underlineBtn);

    // 删除线
    m_strikethroughAction = new QAction(tr("删除线"), this);
    m_strikethroughAction->setCheckable(true);
    m_strikeBtn = new QPushButton(tr("S"), m_toolBarWidget);
    m_strikeBtn->setCheckable(true);
    m_strikeBtn->setMaximumWidth(30);
    connect(m_strikeBtn, &QPushButton::clicked, m_strikethroughAction, &QAction::trigger);
    m_toolBarLayout->addWidget(m_strikeBtn);

    // 分隔符
    QFrame *sep2 = new QFrame(m_toolBarWidget);
    sep2->setFrameShape(QFrame::VLine);
    m_toolBarLayout->addWidget(sep2);

    // 文字颜色
    m_textColorAction = new QAction(tr("文字颜色"), this);
    QPushButton *textColorBtn = new QPushButton(tr("A"), m_toolBarWidget);
    textColorBtn->setMaximumWidth(30);
    textColorBtn->setToolTip(tr("文字颜色"));
    connect(textColorBtn, &QPushButton::clicked, m_textColorAction, &QAction::trigger);
    m_toolBarLayout->addWidget(textColorBtn);

    // 背景颜色
    m_bgColorAction = new QAction(tr("背景颜色"), this);
    QPushButton *bgColorBtn = new QPushButton(tr("背景"), m_toolBarWidget);
    bgColorBtn->setMaximumWidth(40);
    bgColorBtn->setToolTip(tr("背景颜色"));
    connect(bgColorBtn, &QPushButton::clicked, m_bgColorAction, &QAction::trigger);
    m_toolBarLayout->addWidget(bgColorBtn);

    // 分隔符
    QFrame *sep3 = new QFrame(m_toolBarWidget);
    sep3->setFrameShape(QFrame::VLine);
    m_toolBarLayout->addWidget(sep3);

    // 对齐方式
    m_alignLeftAction = new QAction(tr("左对齐"), this);
    QPushButton *alignLeftBtn = new QPushButton(tr("左"), m_toolBarWidget);
    alignLeftBtn->setMaximumWidth(30);
    connect(alignLeftBtn, &QPushButton::clicked, m_alignLeftAction, &QAction::trigger);
    m_toolBarLayout->addWidget(alignLeftBtn);

    m_alignCenterAction = new QAction(tr("居中"), this);
    QPushButton *alignCenterBtn = new QPushButton(tr("中"), m_toolBarWidget);
    alignCenterBtn->setMaximumWidth(30);
    connect(alignCenterBtn, &QPushButton::clicked, m_alignCenterAction, &QAction::trigger);
    m_toolBarLayout->addWidget(alignCenterBtn);

    m_alignRightAction = new QAction(tr("右对齐"), this);
    QPushButton *alignRightBtn = new QPushButton(tr("右"), m_toolBarWidget);
    alignRightBtn->setMaximumWidth(30);
    connect(alignRightBtn, &QPushButton::clicked, m_alignRightAction, &QAction::trigger);
    m_toolBarLayout->addWidget(alignRightBtn);

    m_alignJustifyAction = new QAction(tr("两端对齐"), this);
    QPushButton *alignJustifyBtn = new QPushButton(tr("齐"), m_toolBarWidget);
    alignJustifyBtn->setMaximumWidth(30);
    connect(alignJustifyBtn, &QPushButton::clicked, m_alignJustifyAction, &QAction::trigger);
    m_toolBarLayout->addWidget(alignJustifyBtn);

    // 分隔符
    QFrame *sep4 = new QFrame(m_toolBarWidget);
    sep4->setFrameShape(QFrame::VLine);
    m_toolBarLayout->addWidget(sep4);

    // 清除格式
    m_clearFormatAction = new QAction(tr("清除格式"), this);
    QPushButton *clearBtn = new QPushButton(tr("清除"), m_toolBarWidget);
    clearBtn->setMaximumWidth(50);
    connect(clearBtn, &QPushButton::clicked, m_clearFormatAction, &QAction::trigger);
    m_toolBarLayout->addWidget(clearBtn);

    // 添加弹簧，让按钮靠左
    m_toolBarLayout->addStretch();

    // 添加到主布局
    m_layout->addWidget(m_toolBarWidget);
    m_layout->addWidget(m_textEdit);
}

void RichTextEditor::connectSignals()
{
    // 文本变化
    connect(m_textEdit, &QTextEdit::textChanged,
            this, &RichTextEditor::textChanged);
    connect(m_textEdit->document(), &QTextDocument::modificationChanged,
            this, &RichTextEditor::modificationChanged);
    connect(m_textEdit, &QTextEdit::cursorPositionChanged,
            this, &RichTextEditor::cursorPositionChanged);

    // 格式变化
    connect(m_textEdit, &QTextEdit::currentCharFormatChanged,
            this, &RichTextEditor::onCurrentCharFormatChanged);

    // 工具栏动作
    connect(m_boldAction, &QAction::triggered,
            this, &RichTextEditor::onBold);
    connect(m_italicAction, &QAction::triggered,
            this, &RichTextEditor::onItalic);
    connect(m_underlineAction, &QAction::triggered,
            this, &RichTextEditor::onUnderline);
    connect(m_strikethroughAction, &QAction::triggered,
            this, &RichTextEditor::onStrikethrough);

    // 字体和字号
    connect(m_fontFamilyCombo, &QComboBox::currentTextChanged,
            this, &RichTextEditor::onFontFamilyChanged);
    connect(m_fontSizeSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &RichTextEditor::onFontSizeChanged);

    // 颜色
    connect(m_textColorAction, &QAction::triggered,
            this, &RichTextEditor::onTextColorClicked);
    connect(m_bgColorAction, &QAction::triggered,
            this, &RichTextEditor::onBackgroundColorClicked);

    // 对齐
    connect(m_alignLeftAction, &QAction::triggered,
            this, &RichTextEditor::onAlignLeft);
    connect(m_alignCenterAction, &QAction::triggered,
            this, &RichTextEditor::onAlignCenter);
    connect(m_alignRightAction, &QAction::triggered,
            this, &RichTextEditor::onAlignRight);
    connect(m_alignJustifyAction, &QAction::triggered,
            this, &RichTextEditor::onAlignJustify);

    // 清除格式
    connect(m_clearFormatAction, &QAction::triggered,
            this, &RichTextEditor::onClearFormat);
}

QString RichTextEditor::toHtml() const
{
    return m_textEdit->toHtml();
}

QString RichTextEditor::toPlainText() const
{
    return m_textEdit->toPlainText();
}

void RichTextEditor::setHtml(const QString &html)
{
    m_textEdit->setHtml(html);
}

void RichTextEditor::setPlainText(const QString &text)
{
    m_textEdit->setPlainText(text);
}

void RichTextEditor::clear()
{
    m_textEdit->clear();
}

bool RichTextEditor::isModified() const
{
    return m_textEdit->document()->isModified();
}

void RichTextEditor::setModified(bool modified)
{
    m_textEdit->document()->setModified(modified);
}

QTextEdit* RichTextEditor::textEdit() const
{
    return m_textEdit;
}

void RichTextEditor::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = m_textEdit->textCursor();
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    m_textEdit->mergeCurrentCharFormat(format);
}

void RichTextEditor::setTextColor(const QColor &color)
{
    QTextCharFormat format;
    format.setForeground(color);
    mergeFormatOnWordOrSelection(format);
}

void RichTextEditor::setBackgroundColor(const QColor &color)
{
    QTextCharFormat format;
    format.setBackground(color);
    mergeFormatOnWordOrSelection(format);
}

void RichTextEditor::onBold(bool checked)
{
    QTextCharFormat format;
    format.setFontWeight(checked ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(format);
}

void RichTextEditor::onItalic(bool checked)
{
    QTextCharFormat format;
    format.setFontItalic(checked);
    mergeFormatOnWordOrSelection(format);
}

void RichTextEditor::onUnderline(bool checked)
{
    QTextCharFormat format;
    format.setFontUnderline(checked);
    mergeFormatOnWordOrSelection(format);
}

void RichTextEditor::onStrikethrough(bool checked)
{
    QTextCharFormat format;
    format.setFontStrikeOut(checked);
    mergeFormatOnWordOrSelection(format);
}

void RichTextEditor::onFontFamilyChanged(const QString &family)
{
    QTextCharFormat format;
    format.setFontFamilies({family});
    mergeFormatOnWordOrSelection(format);
}

void RichTextEditor::onFontSizeChanged(int size)
{
    QTextCharFormat format;
    format.setFontPointSize(size);
    mergeFormatOnWordOrSelection(format);
}

void RichTextEditor::onTextColorClicked()
{
    QColor color = QColorDialog::getColor(m_textEdit->textColor(), this);
    if (color.isValid()) {
        setTextColor(color);
    }
}

void RichTextEditor::onBackgroundColorClicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if (color.isValid()) {
        setBackgroundColor(color);
    }
}

void RichTextEditor::onAlignLeft()
{
    m_textEdit->setAlignment(Qt::AlignLeft);
}

void RichTextEditor::onAlignCenter()
{
    m_textEdit->setAlignment(Qt::AlignCenter);
}

void RichTextEditor::onAlignRight()
{
    m_textEdit->setAlignment(Qt::AlignRight);
}

void RichTextEditor::onAlignJustify()
{
    m_textEdit->setAlignment(Qt::AlignJustify);
}

void RichTextEditor::onClearFormat()
{
    QTextCursor cursor = m_textEdit->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.setCharFormat(QTextCharFormat());
    cursor.clearSelection();
    m_textEdit->setTextCursor(cursor);
}

void RichTextEditor::onCurrentCharFormatChanged(const QTextCharFormat &format)
{
    // 更新按钮选中状态（使用 blockSignals 防止循环触发）
    m_boldBtn->blockSignals(true);
    m_boldBtn->setChecked(format.fontWeight() == QFont::Bold);
    m_boldBtn->blockSignals(false);

    m_italicBtn->blockSignals(true);
    m_italicBtn->setChecked(format.fontItalic());
    m_italicBtn->blockSignals(false);

    m_underlineBtn->blockSignals(true);
    m_underlineBtn->setChecked(format.fontUnderline());
    m_underlineBtn->blockSignals(false);

    m_strikeBtn->blockSignals(true);
    m_strikeBtn->setChecked(format.fontStrikeOut());
    m_strikeBtn->blockSignals(false);

    // 更新字体和字号
    m_fontFamilyCombo->blockSignals(true);
    QStringList families = format.fontFamilies().toStringList();
    QString family = families.isEmpty() ? m_textEdit->font().family() : families.first();
    m_fontFamilyCombo->setCurrentText(family);
    m_fontFamilyCombo->blockSignals(false);

    m_fontSizeSpin->blockSignals(true);
    m_fontSizeSpin->setValue(static_cast<int>(format.fontPointSize()));
    m_fontSizeSpin->blockSignals(false);
}
