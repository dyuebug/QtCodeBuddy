/**
 * @file RichTextEditor.h
 * @brief 富文本编辑器控件
 *
 * 知识点：
 * - QTextEdit 高级用法
 * - QTextCharFormat 文本格式
 * - QTextCursor 光标操作
 * - 字体、颜色选择
 */

#ifndef RICHTEXTEDITOR_H
#define RICHTEXTEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QAction>
#include <QPushButton>

/**
 * @class RichTextEditor
 * @brief 富文本编辑器控件
 *
 * 提供富文本编辑功能，包括字体、颜色、格式等
 */
class RichTextEditor : public QWidget
{
    Q_OBJECT

public:
    explicit RichTextEditor(QWidget *parent = nullptr);
    ~RichTextEditor() override = default;

    // 内容操作
    QString toHtml() const;
    QString toPlainText() const;
    void setHtml(const QString &html);
    void setPlainText(const QString &text);
    void clear();

    // 编辑状态
    bool isModified() const;
    void setModified(bool modified);

    // 获取内部编辑器
    QTextEdit* textEdit() const;

signals:
    void textChanged();
    void modificationChanged(bool changed);
    void cursorPositionChanged();

private:
    void setupUi();
    void createToolBar();
    void connectSignals();

    // 格式操作
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void setTextColor(const QColor &color);
    void setBackgroundColor(const QColor &color);

private slots:
    void onBold(bool checked);
    void onItalic(bool checked);
    void onUnderline(bool checked);
    void onStrikethrough(bool checked);

    void onFontFamilyChanged(const QString &family);
    void onFontSizeChanged(int size);

    void onTextColorClicked();
    void onBackgroundColorClicked();

    void onAlignLeft();
    void onAlignCenter();
    void onAlignRight();
    void onAlignJustify();

    void onClearFormat();
    void onCurrentCharFormatChanged(const QTextCharFormat &format);

private:
    QVBoxLayout *m_layout;
    QWidget *m_toolBarWidget;      // 改用 QWidget 代替 QToolBar
    QHBoxLayout *m_toolBarLayout;  // 工具栏布局
    QTextEdit *m_textEdit;

    // 格式工具栏控件
    QComboBox *m_fontFamilyCombo;
    QSpinBox *m_fontSizeSpin;

    // 格式按钮
    QPushButton *m_boldBtn;
    QPushButton *m_italicBtn;
    QPushButton *m_underlineBtn;
    QPushButton *m_strikeBtn;

    // 格式动作
    QAction *m_boldAction;
    QAction *m_italicAction;
    QAction *m_underlineAction;
    QAction *m_strikethroughAction;

    QAction *m_textColorAction;
    QAction *m_bgColorAction;

    QAction *m_alignLeftAction;
    QAction *m_alignCenterAction;
    QAction *m_alignRightAction;
    QAction *m_alignJustifyAction;

    QAction *m_clearFormatAction;
};

#endif // RICHTEXTEDITOR_H
