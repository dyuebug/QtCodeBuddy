/**
 * @file NotePropertiesDialog.h
 * @brief 笔记属性对话框
 *
 * 知识点：
 * - QDialog 模态对话框
 * - QFormLayout 表单布局
 * - 数据验证
 */

#ifndef NOTEPROPERTIESDIALOG_H
#define NOTEPROPERTIESDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>

class Note;

/**
 * @class NotePropertiesDialog
 * @brief 笔记属性对话框
 *
 * 显示和编辑笔记的属性信息
 */
class NotePropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NotePropertiesDialog(QWidget *parent = nullptr);
    ~NotePropertiesDialog() override = default;

    void setNote(Note *note);
    QString noteTitle() const;
    QString categoryId() const;

private:
    void setupUi();
    void connectSignals();
    void updateCategoryCombo();

private slots:
    void onAccepted();

private:
    QVBoxLayout *m_mainLayout;
    QFormLayout *m_formLayout;

    QLineEdit *m_titleEdit;
    QComboBox *m_categoryCombo;
    QLabel *m_createdLabel;
    QLabel *m_modifiedLabel;
    QLabel *m_wordCountLabel;

    QDialogButtonBox *m_buttonBox;
    Note *m_note;
};

#endif // NOTEPROPERTIESDIALOG_H
