/**
 * @file CategoryDialog.cpp
 * @brief 分类管理对话框实现
 */

#include "CategoryDialog.h"
#include "Category.h"

#include <QColorDialog>

CategoryDialog::CategoryDialog(QWidget *parent)
    : QDialog(parent)
    , m_color(Qt::blue)
{
    setWindowTitle(tr("分类"));
    setMinimumWidth(300);
    setupUi();
    connectSignals();
    updateColorButton();
}

void CategoryDialog::setupUi()
{
    m_mainLayout = new QVBoxLayout(this);
    m_formLayout = new QFormLayout();

    m_nameEdit = new QLineEdit(this);
    m_colorButton = new QPushButton(this);
    m_colorButton->setFixedSize(60, 24);

    m_formLayout->addRow(tr("名称:"), m_nameEdit);
    m_formLayout->addRow(tr("颜色:"), m_colorButton);

    m_buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    m_mainLayout->addLayout(m_formLayout);
    m_mainLayout->addWidget(m_buttonBox);
}

void CategoryDialog::connectSignals()
{
    connect(m_colorButton, &QPushButton::clicked,
            this, &CategoryDialog::onColorClicked);
    connect(m_buttonBox, &QDialogButtonBox::accepted,
            this, &CategoryDialog::onAccepted);
    connect(m_buttonBox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
}

void CategoryDialog::updateColorButton()
{
    QString style = QString("background-color: %1;").arg(m_color.name());
    m_colorButton->setStyleSheet(style);
}

void CategoryDialog::setCategory(Category *category)
{
    if (!category) return;

    m_nameEdit->setText(category->name());
    m_color = category->color();
    updateColorButton();
}

QString CategoryDialog::categoryName() const
{
    return m_nameEdit->text();
}

QColor CategoryDialog::categoryColor() const
{
    return m_color;
}

void CategoryDialog::onColorClicked()
{
    QColor color = QColorDialog::getColor(m_color, this, tr("选择颜色"));
    if (color.isValid()) {
        m_color = color;
        updateColorButton();
    }
}

void CategoryDialog::onAccepted()
{
    if (m_nameEdit->text().trimmed().isEmpty()) {
        m_nameEdit->setFocus();
        return;
    }
    accept();
}
