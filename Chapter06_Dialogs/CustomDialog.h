/**
 * @file CustomDialog.h
 * @brief 自定义对话框类
 * 
 * 学习要点：
 * 1. 如何继承QDialog创建自定义对话框
 * 2. 对话框的模态性设置
 * 3. 对话框的返回值
 * 4. 标准按钮的使用
 */

#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
/**
 * @class CustomDialog
 * @brief 一个自定义的用户信息对话框
 */
class CustomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = nullptr);
    
    /**
     * @brief 获取用户名
     */
    QString username() const { return m_usernameEdit->text(); }
    
    /**
     * @brief 获取年龄
     */
    int age() const { return m_ageSpinBox->value(); }
    
    /**
     * @brief 获取职业
     */
    QString profession() const { return m_professionCombo->currentText(); }
    
    /**
     * @brief 是否同意条款
     */
    bool agreed() const { return m_agreeCheckBox->isChecked(); }
    
    /**
     * @brief 获取备注
     */
    QString notes() const { return m_notesEdit->toPlainText(); }
    
    /**
     * @brief 静态方法 - 以模态方式显示对话框
     * @param parent 父窗口
     * @return 对话框结果（Accepted或Rejected）
     */
    static QDialog::DialogCode showModal(QWidget *parent = nullptr);

private:
    void setupUi();
    void connectSignals();

private slots:
    void onAgreeStateChanged(int state);

private:
    QLineEdit *m_usernameEdit;
    QSpinBox *m_ageSpinBox;
    QComboBox *m_professionCombo;
    QCheckBox *m_agreeCheckBox;
    QTextEdit *m_notesEdit;
    QPushButton *m_okButton;
};

#endif // CUSTOMDIALOG_H
