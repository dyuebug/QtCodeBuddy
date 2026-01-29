/**
 * @file CategoryTree.h
 * @brief 分类树控件
 *
 * 知识点：
 * - QTreeWidget 树形控件
 * - 自定义 QTreeWidgetItem
 * - 右键上下文菜单
 */

#ifndef CATEGORYTREE_H
#define CATEGORYTREE_H

#include <QWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QMenu>

class Category;

/**
 * @class CategoryTree
 * @brief 分类树控件
 *
 * 显示分类的树形结构，支持选择、右键菜单等操作
 */
class CategoryTree : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryTree(QWidget *parent = nullptr);
    ~CategoryTree() override = default;

    // 分类操作
    void addCategory(Category *category);
    void removeCategory(const QString &categoryId);
    void updateCategory(Category *category);
    void clear();

    // 选择操作
    QString currentCategoryId() const;
    void setCurrentCategoryId(const QString &categoryId);

    // 刷新列表
    void refreshTree();

signals:
    void categorySelected(const QString &categoryId);
    void createCategoryRequested();
    void deleteCategoryRequested(const QString &categoryId);
    void editCategoryRequested(const QString &categoryId);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void setupUi();
    void createContextMenu();
    void connectSignals();

    QTreeWidgetItem* findItemByCategoryId(const QString &categoryId);
    void updateItemFromCategory(QTreeWidgetItem *item, Category *category);

private slots:
    void onItemClicked(QTreeWidgetItem *item, int column);
    void onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    QVBoxLayout *m_layout;
    QTreeWidget *m_treeWidget;
    QMenu *m_contextMenu;

    // 上下文菜单动作
    QAction *m_newCategoryAction;
    QAction *m_editCategoryAction;
    QAction *m_deleteCategoryAction;
};

#endif // CATEGORYTREE_H
