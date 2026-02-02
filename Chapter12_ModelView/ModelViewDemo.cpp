/**
 * @file ModelViewDemo.cpp
 * @brief 第12章示例 - 模型视图演示实现
 */

#include "ModelViewDemo.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QHeaderView>

ModelViewDemo::ModelViewDemo(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
    connectSignals();

    setWindowTitle("第12章：模型视图");
    resize(650, 500);
}

void ModelViewDemo::setupUi()
{
    m_tabWidget = new QTabWidget(this);

    QWidget *listTab = new QWidget();
    QWidget *tableTab = new QWidget();

    setupListViewDemo(listTab);
    setupTableViewDemo(tableTab);

    m_tabWidget->addTab(listTab, "列表视图");
    m_tabWidget->addTab(tableTab, "表格视图");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tabWidget);
}

void ModelViewDemo::setupListViewDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);

    // 创建模型
    m_listModel = new QStringListModel(this);
    QStringList items = {"项目 1", "项目 2", "项目 3"};
    m_listModel->setStringList(items);

    // 创建视图
    m_listView = new QListView(parent);
    m_listView->setModel(m_listModel);
    m_listView->setEditTriggers(QAbstractItemView::DoubleClicked);
    mainLayout->addWidget(m_listView);

    // 输入和按钮
    QHBoxLayout *inputLayout = new QHBoxLayout();
    m_listItemEdit = new QLineEdit(parent);
    m_listItemEdit->setPlaceholderText("输入新项目");
    m_addListBtn = new QPushButton("添加", parent);
    m_removeListBtn = new QPushButton("删除", parent);

    inputLayout->addWidget(m_listItemEdit);
    inputLayout->addWidget(m_addListBtn);
    inputLayout->addWidget(m_removeListBtn);
    mainLayout->addLayout(inputLayout);
}

void ModelViewDemo::setupTableViewDemo(QWidget *parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(parent);

    // 创建模型
    m_tableModel = new QStandardItemModel(3, 3, this);
    m_tableModel->setHorizontalHeaderLabels({"姓名", "年龄", "城市"});

    // 添加初始数据
    m_tableModel->setItem(0, 0, new QStandardItem("张三"));
    m_tableModel->setItem(0, 1, new QStandardItem("25"));
    m_tableModel->setItem(0, 2, new QStandardItem("北京"));

    m_tableModel->setItem(1, 0, new QStandardItem("李四"));
    m_tableModel->setItem(1, 1, new QStandardItem("30"));
    m_tableModel->setItem(1, 2, new QStandardItem("上海"));

    m_tableModel->setItem(2, 0, new QStandardItem("王五"));
    m_tableModel->setItem(2, 1, new QStandardItem("28"));
    m_tableModel->setItem(2, 2, new QStandardItem("广州"));

    // 创建视图
    m_tableView = new QTableView(parent);
    m_tableView->setModel(m_tableModel);
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(m_tableView);

    // 按钮
    QHBoxLayout *btnLayout = new QHBoxLayout();
    m_addRowBtn = new QPushButton("添加行", parent);
    m_removeRowBtn = new QPushButton("删除行", parent);
    btnLayout->addWidget(m_addRowBtn);
    btnLayout->addWidget(m_removeRowBtn);
    btnLayout->addStretch();
    mainLayout->addLayout(btnLayout);
}

void ModelViewDemo::connectSignals()
{
    connect(m_addListBtn, &QPushButton::clicked, this, &ModelViewDemo::onAddListItem);
    connect(m_removeListBtn, &QPushButton::clicked, this, &ModelViewDemo::onRemoveListItem);
    connect(m_addRowBtn, &QPushButton::clicked, this, &ModelViewDemo::onAddTableRow);
    connect(m_removeRowBtn, &QPushButton::clicked, this, &ModelViewDemo::onRemoveTableRow);
}

void ModelViewDemo::onAddListItem()
{
    QString text = m_listItemEdit->text().trimmed();
    if (text.isEmpty()) return;

    int row = m_listModel->rowCount();
    m_listModel->insertRow(row);
    m_listModel->setData(m_listModel->index(row), text);
    m_listItemEdit->clear();
}

void ModelViewDemo::onRemoveListItem()
{
    QModelIndex index = m_listView->currentIndex();
    if (index.isValid()) {
        m_listModel->removeRow(index.row());
    }
}

void ModelViewDemo::onAddTableRow()
{
    int row = m_tableModel->rowCount();
    m_tableModel->insertRow(row);
    m_tableModel->setItem(row, 0, new QStandardItem("新用户"));
    m_tableModel->setItem(row, 1, new QStandardItem("0"));
    m_tableModel->setItem(row, 2, new QStandardItem("未知"));
}

void ModelViewDemo::onRemoveTableRow()
{
    QModelIndex index = m_tableView->currentIndex();
    if (index.isValid()) {
        m_tableModel->removeRow(index.row());
    }
}
