/**
 * @file NotePropertiesDialog.cpp
 * @brief 笔记属性对话框实现
 */

#include "NotePropertiesDialog.h"
#include "Note.h"
#include "NoteManager.h"
#include "Category.h"

NotePropertiesDialog::NotePropertiesDialog(QWidget *parent)
    : QDialog(parent)
    , m_note(nullptr)
{
    setWindowTitle(tr("笔记属性"));
    setMinimumWidth(350);
    setupUi();
    connectSignals();
    updateCategoryCombo();
}

void NotePropertiesDialog::setupUi()
{
    m_mainLayout = new QVBoxLayout(this);
    m_formLayout = new QFormLayout();

    m_titleEdit = new QLineEdit(this);
    m_categoryCombo = new QComboBox(this);
    m_createdLabel = new QLabel(this);
    m_modifiedLabel = new QLabel(this);
    m_wordCountLabel = new QLabel(this);

    m_formLayout->addRow(tr("标题:"), m_titleEdit);
    m_formLayout->addRow(tr("分类:"), m_categoryCombo);
    m_formLayout->addRow(tr("创建时间:"), m_createdLabel);
    m_formLayout->addRow(tr("修改时间:"), m_modifiedLabel);
    m_formLayout->addRow(tr("字数:"), m_wordCountLabel);

    m_buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    m_mainLayout->addLayout(m_formLayout);
    m_mainLayout->addWidget(m_buttonBox);
}

void NotePropertiesDialog::connectSignals()
{
    connect(m_buttonBox, &QDialogButtonBox::accepted,
            this, &NotePropertiesDialog::onAccepted);
    connect(m_buttonBox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
}

void NotePropertiesDialog::updateCategoryCombo()
{
    m_categoryCombo->clear();
    m_categoryCombo->addItem(tr("无分类"), QString());

    QList<Category*> categories = NoteManager::instance()->getAllCategories();
    for (Category *cat : categories) {
        m_categoryCombo->addItem(cat->name(), cat->id());
    }
}

void NotePropertiesDialog::setNote(Note *note)
{
    m_note = note;
    if (!note) return;

    m_titleEdit->setText(note->title());

    // 设置分类
    int index = m_categoryCombo->findData(note->categoryId());
    if (index >= 0) {
        m_categoryCombo->setCurrentIndex(index);
    }

    // 显示时间信息
    m_createdLabel->setText(note->createdAt().toString("yyyy-MM-dd hh:mm:ss"));
    m_modifiedLabel->setText(note->updatedAt().toString("yyyy-MM-dd hh:mm:ss"));

    // 计算字数
    QString plainText = note->content();
    int wordCount = plainText.length();
    m_wordCountLabel->setText(QString::number(wordCount));
}

QString NotePropertiesDialog::noteTitle() const
{
    return m_titleEdit->text();
}

QString NotePropertiesDialog::categoryId() const
{
    return m_categoryCombo->currentData().toString();
}

void NotePropertiesDialog::onAccepted()
{
    if (m_titleEdit->text().trimmed().isEmpty()) {
        m_titleEdit->setFocus();
        return;
    }
    accept();
}
