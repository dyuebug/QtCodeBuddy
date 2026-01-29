/**
 * @file CategoryDialog.h
 * @brief 分类管理对话框
 *
 * 知识点：
 * - QDialog 自定义对话框
 * - QColorDialog 颜色选择
 * - 数据验证
 */

#ifndef CATEGORYDIALOG_H
#define CATEGORYDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QColor>

class Category;

/**
 * @class CategoryDialog
 * @brief 分类管理对话框
 *
 * 用于创建和编辑分类
 */
class CategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryDialog(QWidget *parent = nullptr);
    ~CategoryDialog() override = default;

    void setCategory(Category *category);
    QString categoryName() const;
    QColor categoryColor() const;

private:
    void setupUi();
    void connectSignals();
    void updateColorButton();

private slots:
    void onColorClicked();
    void onAccepted();

private:
    QVBoxLayout *m_mainLayout;
    QFormLayout *m_formLayout;

    QLineEdit *m_nameEdit;
    QPushButton *m_colorButton;
    QDialogButtonBox *m_buttonBox;

    QColor m_color;
};

#endif // CATEGORYDIALOG_H
