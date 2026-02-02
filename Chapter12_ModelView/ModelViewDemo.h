/**
 * @file ModelViewDemo.h
 * @brief 第12章示例 - 模型视图演示
 *
 * 本章学习要点：
 * 1. QStringListModel 字符串列表模型
 * 2. QStandardItemModel 标准项模型
 * 3. QListView 列表视图
 * 4. QTableView 表格视图
 */

#ifndef MODELVIEWDEMO_H
#define MODELVIEWDEMO_H

#include <QWidget>
#include <QTabWidget>
#include <QListView>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QStringListModel>
#include <QStandardItemModel>

class ModelViewDemo : public QWidget
{
    Q_OBJECT

public:
    explicit ModelViewDemo(QWidget *parent = nullptr);

private:
    void setupUi();
    void setupListViewDemo(QWidget *parent);
    void setupTableViewDemo(QWidget *parent);
    void connectSignals();

private slots:
    void onAddListItem();
    void onRemoveListItem();
    void onAddTableRow();
    void onRemoveTableRow();

private:
    QTabWidget *m_tabWidget;

    // 列表视图部件
    QListView *m_listView;
    QStringListModel *m_listModel;
    QLineEdit *m_listItemEdit;
    QPushButton *m_addListBtn;
    QPushButton *m_removeListBtn;

    // 表格视图部件
    QTableView *m_tableView;
    QStandardItemModel *m_tableModel;
    QPushButton *m_addRowBtn;
    QPushButton *m_removeRowBtn;
};

#endif // MODELVIEWDEMO_H
