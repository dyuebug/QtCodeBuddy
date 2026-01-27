/**
 * @file CustomDialog.cpp
 * @brief 自定义对话框实现
 */

#include "CustomDialog.h"

CustomDialog::CustomDialog(QWidget *parent)
    : QDialog(parent)
    , m_usernameEdit(nullptr)
    , m_ageSpinBox(nullptr)
    , m_professionCombo(nullptr)
    , m_agreeCheckBox(nullptr)
    , m_notesEdit(nullptr)
    , m_okButton(nullptr)
{
    setupUi();
    connectSignals();
    
    setWindowTitle("用户信息");
    setModal(true);  // 设置为模态对话框
}

/**
 * @brief 静态方法 - 显示模态对话框
 */
QDialog::DialogCode CustomDialog::showModal(QWidget *parent)
{
    CustomDialog dialog(parent);
    
    if (dialog.exec() == QDialog::Accepted) {
        // 对话框被接受
        return QDialog::Accepted;
    } else {
        // 对话框被拒绝
        return QDialog::Rejected;
    }
}

/**
 * @brief 设置界面
 */
void CustomDialog::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // 表单布局
    QFormLayout *formLayout = new QFormLayout();
    
    // 用户名
    m_usernameEdit = new QLineEdit(this);
    m_usernameEdit->setPlaceholderText("请输入用户名");
    formLayout->addRow("用户名:", m_usernameEdit);
    
    // 年龄
    m_ageSpinBox = new QSpinBox(this);
    m_ageSpinBox->setRange(1, 120);
    m_ageSpinBox->setValue(25);
    formLayout->addRow("年龄:", m_ageSpinBox);
    
    // 职业
    m_professionCombo = new QComboBox(this);
    m_professionCombo->addItem("学生");
    m_professionCombo->addItem("工程师");
    m_professionCombo->addItem("设计师");
    m_professionCombo->addItem("教师");
    m_professionCombo->addItem("医生");
    m_professionCombo->addItem("其他");
    formLayout->addRow("职业:", m_professionCombo);
    
    // 同意条款
    m_agreeCheckBox = new QCheckBox("我同意用户协议和隐私政策", this);
    formLayout->addRow("", m_agreeCheckBox);
    
    mainLayout->addLayout(formLayout);
    
    // 备注
    QLabel *notesLabel = new QLabel("备注:", this);
    m_notesEdit = new QTextEdit(this);
    m_notesEdit->setMaximumHeight(80);
    m_notesEdit->setPlaceholderText("请输入备注信息...");
    
    mainLayout->addWidget(notesLabel);
    mainLayout->addWidget(m_notesEdit);
    
    // 标准按钮框
    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
    m_okButton = buttonBox->addButton("确定", QDialogButtonBox::AcceptRole);
    QPushButton *cancelButton = buttonBox->addButton("取消", QDialogButtonBox::RejectRole);
    QPushButton *helpButton = buttonBox->addButton("帮助", QDialogButtonBox::HelpRole);
    
    mainLayout->addWidget(buttonBox);
    
    // 初始状态下禁用确定按钮
    m_okButton->setEnabled(false);
    
    // 连接按钮框信号
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(helpButton, &QPushButton::clicked, [this]() {
        QMessageBox::information(this, "帮助", "请填写所有必要信息并同意协议。");
    });
}

/**
 * @brief 连接信号和槽
 */
void CustomDialog::connectSignals()
{
    // 监听复选框状态变化
    connect(m_agreeCheckBox, &QCheckBox::stateChanged, this, &CustomDialog::onAgreeStateChanged);
}

/**
 * @brief 同意条款状态改变
 */
void CustomDialog::onAgreeStateChanged(int state)
{
    // 只有同意条款才能点击确定
    m_okButton->setEnabled(state == Qt::Checked);
}
