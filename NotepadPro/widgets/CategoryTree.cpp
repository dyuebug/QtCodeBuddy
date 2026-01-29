/**
 * @file CategoryTree.cpp
 * @brief 分类树控件实现
 */

#include "CategoryTree.h"
#include "Category.h"
#include "NoteManager.h"

#include <QContextMenuEvent>
#include <QHeaderView>

CategoryTree::CategoryTree(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
    createContextMenu();
    connectSignals();
}

void CategoryTree::setupUi()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);

    m_treeWidget = new QTreeWidget(this);
    m_treeWidget->setHeaderLabel(tr("分类"));
    m_treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_treeWidget->header()->setVisible(false);

    m_layout->addWidget(m_treeWidget);
}

void CategoryTree::createContextMenu()
{
    m_contextMenu = new QMenu(this);

    m_newCategoryAction = new QAction(tr("新建分类"), this);
    m_editCategoryAction = new QAction(tr("编辑分类"), this);
    m_deleteCategoryAction = new QAction(tr("删除分类"), this);

    m_contextMenu->addAction(m_newCategoryAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(m_editCategoryAction);
    m_contextMenu->addAction(m_deleteCategoryAction);
}

void CategoryTree::connectSignals()
{
    connect(m_treeWidget, &QTreeWidget::itemClicked,
            this, &CategoryTree::onItemClicked);
    connect(m_treeWidget, &QTreeWidget::currentItemChanged,
            this, &CategoryTree::onCurrentItemChanged);

    connect(m_newCategoryAction, &QAction::triggered,
            this, &CategoryTree::createCategoryRequested);
    connect(m_editCategoryAction, &QAction::triggered, this, [this]() {
        QString catId = currentCategoryId();
        if (!catId.isEmpty()) {
            emit editCategoryRequested(catId);
        }
    });
    connect(m_deleteCategoryAction, &QAction::triggered, this, [this]() {
        QString catId = currentCategoryId();
        if (!catId.isEmpty()) {
            emit deleteCategoryRequested(catId);
        }
    });
}

void CategoryTree::addCategory(Category *category)
{
    if (!category) return;

    QTreeWidgetItem *item = new QTreeWidgetItem();
    updateItemFromCategory(item, category);
    m_treeWidget->addTopLevelItem(item);
}

void CategoryTree::removeCategory(const QString &categoryId)
{
    QTreeWidgetItem *item = findItemByCategoryId(categoryId);
    if (item) {
        delete item;
    }
}

void CategoryTree::updateCategory(Category *category)
{
    if (!category) return;
    QTreeWidgetItem *item = findItemByCategoryId(category->id());
    if (item) {
        updateItemFromCategory(item, category);
    }
}

void CategoryTree::clear()
{
    m_treeWidget->clear();
}

QString CategoryTree::currentCategoryId() const
{
    QTreeWidgetItem *item = m_treeWidget->currentItem();
    if (item) {
        return item->data(0, Qt::UserRole).toString();
    }
    return QString();
}

void CategoryTree::setCurrentCategoryId(const QString &categoryId)
{
    QTreeWidgetItem *item = findItemByCategoryId(categoryId);
    if (item) {
        m_treeWidget->setCurrentItem(item);
    }
}

/**
 * @brief 刷新分类树
 *
 * 清空并重新加载所有分类，同时添加"全部笔记"选项
 */
void CategoryTree::refreshTree()
{
    clear();

    // 添加"全部笔记"选项（空ID表示显示所有）
    QTreeWidgetItem *allItem = new QTreeWidgetItem();
    allItem->setText(0, tr("全部笔记"));
    allItem->setData(0, Qt::UserRole, QString());
    m_treeWidget->addTopLevelItem(allItem);

    // 添加所有分类
    QList<Category*> categories = NoteManager::instance()->getAllCategories();
    for (Category *cat : categories) {
        addCategory(cat);
    }

    // 默认选中"全部笔记"
    m_treeWidget->setCurrentItem(allItem);
}

/**
 * @brief 右键菜单事件处理
 * @param event 上下文菜单事件
 *
 * 根据当前选中项启用/禁用菜单项
 * "全部笔记"项不能编辑或删除
 */
void CategoryTree::contextMenuEvent(QContextMenuEvent *event)
{
    QTreeWidgetItem *item = m_treeWidget->currentItem();
    bool hasSelection = item != nullptr;
    // 检查是否选中了真实分类（非"全部笔记"）
    bool isRealCategory = hasSelection && !item->data(0, Qt::UserRole).toString().isEmpty();

    m_editCategoryAction->setEnabled(isRealCategory);
    m_deleteCategoryAction->setEnabled(isRealCategory);
    m_contextMenu->exec(event->globalPos());
}

QTreeWidgetItem* CategoryTree::findItemByCategoryId(const QString &categoryId)
{
    for (int i = 0; i < m_treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = m_treeWidget->topLevelItem(i);
        if (item->data(0, Qt::UserRole).toString() == categoryId) {
            return item;
        }
    }
    return nullptr;
}

void CategoryTree::updateItemFromCategory(QTreeWidgetItem *item, Category *category)
{
    item->setText(0, category->name());
    item->setData(0, Qt::UserRole, category->id());

    // 设置分类颜色图标
    QColor color = category->color();
    if (color.isValid()) {
        QPixmap pixmap(16, 16);
        pixmap.fill(color);
        item->setIcon(0, QIcon(pixmap));
    }
}

void CategoryTree::onItemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    if (item) {
        emit categorySelected(item->data(0, Qt::UserRole).toString());
    }
}

void CategoryTree::onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    Q_UNUSED(previous)
    if (current) {
        emit categorySelected(current->data(0, Qt::UserRole).toString());
    }
}
