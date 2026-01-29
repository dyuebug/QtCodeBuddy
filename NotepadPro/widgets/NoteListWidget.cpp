/**
 * @file NoteListWidget.cpp
 * @brief 笔记列表控件实现
 *
 * 知识点：
 * - QListWidget 列表控件的使用
 * - QListWidgetItem 自定义数据存储（Qt::UserRole）
 * - QContextMenuEvent 右键菜单事件处理
 * - Lambda 表达式在信号槽中的应用
 * - 信号转发模式（将内部信号转换为外部信号）
 */

#include "NoteListWidget.h"
#include "Note.h"
#include "NoteManager.h"

#include <QContextMenuEvent>

/**
 * @brief 构造函数
 * @param parent 父控件指针
 *
 * 初始化笔记列表控件，按顺序执行：
 * 1. setupUi() - 创建界面元素
 * 2. createContextMenu() - 创建右键菜单
 * 3. connectSignals() - 连接信号槽
 */
NoteListWidget::NoteListWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
    createContextMenu();
    connectSignals();
}

/**
 * @brief 初始化界面
 *
 * 知识点：
 * - QVBoxLayout 垂直布局管理器
 * - setContentsMargins(0,0,0,0) 去除边距，让控件填满父容器
 * - setAlternatingRowColors(true) 交替行颜色，提升可读性
 * - SingleSelection 单选模式
 */
void NoteListWidget::setupUi()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);

    m_listWidget = new QListWidget(this);
    m_listWidget->setAlternatingRowColors(true);
    m_listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    m_layout->addWidget(m_listWidget);
}

/**
 * @brief 创建右键上下文菜单
 *
 * 菜单包含：新建、重命名、删除、属性等操作
 */
void NoteListWidget::createContextMenu()
{
    m_contextMenu = new QMenu(this);

    m_newNoteAction = new QAction(tr("新建笔记"), this);
    m_renameNoteAction = new QAction(tr("重命名"), this);
    m_deleteNoteAction = new QAction(tr("删除笔记"), this);
    m_propertiesAction = new QAction(tr("属性"), this);

    m_contextMenu->addAction(m_newNoteAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(m_renameNoteAction);
    m_contextMenu->addAction(m_deleteNoteAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(m_propertiesAction);
}

/**
 * @brief 连接信号槽
 *
 * 知识点：
 * - Lambda 表达式捕获 this 指针
 * - 信号转发：将内部控件信号转换为自定义信号
 * - QAction::triggered 信号的使用
 */
void NoteListWidget::connectSignals()
{
    // 列表项点击事件 -> 发出笔记选中信号
    connect(m_listWidget, &QListWidget::itemClicked,
            this, &NoteListWidget::onItemClicked);
    connect(m_listWidget, &QListWidget::itemDoubleClicked,
            this, &NoteListWidget::onItemDoubleClicked);
    connect(m_listWidget, &QListWidget::currentItemChanged,
            this, &NoteListWidget::onCurrentItemChanged);

    // 上下文菜单动作 - 使用 Lambda 获取当前选中项ID
    connect(m_newNoteAction, &QAction::triggered,
            this, &NoteListWidget::createNoteRequested);
    connect(m_renameNoteAction, &QAction::triggered, this, [this]() {
        QString noteId = currentNoteId();
        if (!noteId.isEmpty()) {
            emit renameNoteRequested(noteId);
        }
    });
    connect(m_deleteNoteAction, &QAction::triggered, this, [this]() {
        QString noteId = currentNoteId();
        if (!noteId.isEmpty()) {
            emit deleteNoteRequested(noteId);
        }
    });
    connect(m_propertiesAction, &QAction::triggered, this, [this]() {
        QString noteId = currentNoteId();
        if (!noteId.isEmpty()) {
            emit notePropertiesRequested(noteId);
        }
    });
}

/**
 * @brief 添加笔记到列表
 * @param note 笔记对象指针
 *
 * 知识点：
 * - QListWidgetItem 的动态创建
 * - 数据与显示分离：使用 Qt::UserRole 存储笔记ID
 */
void NoteListWidget::addNote(Note *note)
{
    if (!note) return;

    QListWidgetItem *item = new QListWidgetItem(m_listWidget);
    updateItemFromNote(item, note);
    m_listWidget->addItem(item);
}

/**
 * @brief 从列表中移除笔记
 * @param noteId 笔记ID
 *
 * 知识点：
 * - takeItem() 从列表中移除但不删除内存
 * - delete 手动释放 QListWidgetItem 内存
 */
void NoteListWidget::removeNote(const QString &noteId)
{
    QListWidgetItem *item = findItemByNoteId(noteId);
    if (item) {
        delete m_listWidget->takeItem(m_listWidget->row(item));
    }
}

/**
 * @brief 更新列表中的笔记显示
 * @param note 笔记对象指针
 */
void NoteListWidget::updateNote(Note *note)
{
    if (!note) return;
    QListWidgetItem *item = findItemByNoteId(note->id());
    if (item) {
        updateItemFromNote(item, note);
    }
}

/**
 * @brief 清空笔记列表
 */
void NoteListWidget::clear()
{
    m_listWidget->clear();
}

/**
 * @brief 获取当前选中笔记的ID
 * @return 笔记ID，无选中时返回空字符串
 *
 * 知识点：
 * - Qt::UserRole 用于存储自定义数据
 * - QVariant::toString() 类型转换
 */
QString NoteListWidget::currentNoteId() const
{
    QListWidgetItem *item = m_listWidget->currentItem();
    if (item) {
        return item->data(Qt::UserRole).toString();
    }
    return QString();
}

/**
 * @brief 设置当前选中的笔记
 * @param noteId 笔记ID
 */
void NoteListWidget::setCurrentNoteId(const QString &noteId)
{
    QListWidgetItem *item = findItemByNoteId(noteId);
    if (item) {
        m_listWidget->setCurrentItem(item);
    }
}

/**
 * @brief 刷新笔记列表
 *
 * 从 NoteManager 获取所有笔记并重新填充列表
 */
void NoteListWidget::refreshList()
{
    clear();
    QList<Note*> notes = NoteManager::instance()->getAllNotes();
    for (Note *note : notes) {
        addNote(note);
    }
}

/**
 * @brief 右键菜单事件处理
 * @param event 上下文菜单事件
 */
void NoteListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    bool hasSelection = m_listWidget->currentItem() != nullptr;
    m_renameNoteAction->setEnabled(hasSelection);
    m_deleteNoteAction->setEnabled(hasSelection);
    m_propertiesAction->setEnabled(hasSelection);
    m_contextMenu->exec(event->globalPos());
}

/**
 * @brief 根据笔记ID查找列表项
 * @param noteId 笔记ID
 * @return 找到的列表项指针，未找到返回 nullptr
 *
 * 知识点：
 * - 遍历 QListWidget 的方式：count() + item(i)
 * - Qt::UserRole 存储的自定义数据检索
 */
QListWidgetItem* NoteListWidget::findItemByNoteId(const QString &noteId)
{
    for (int i = 0; i < m_listWidget->count(); ++i) {
        QListWidgetItem *item = m_listWidget->item(i);
        if (item->data(Qt::UserRole).toString() == noteId) {
            return item;
        }
    }
    return nullptr;
}

/**
 * @brief 从笔记对象更新列表项显示
 * @param item 列表项指针
 * @param note 笔记对象指针
 *
 * 知识点：
 * - setText() 设置显示文本
 * - setToolTip() 设置鼠标悬停提示
 * - setData(Qt::UserRole, ...) 存储自定义数据
 */
void NoteListWidget::updateItemFromNote(QListWidgetItem *item, Note *note)
{
    item->setText(note->title());
    item->setToolTip(note->preview());
    item->setData(Qt::UserRole, note->id());
}

/**
 * @brief 列表项单击事件处理
 * @param item 被点击的列表项
 *
 * 发出 noteSelected 信号，通知外部笔记被选中
 */
void NoteListWidget::onItemClicked(QListWidgetItem *item)
{
    if (item) {
        emit noteSelected(item->data(Qt::UserRole).toString());
    }
}

/**
 * @brief 列表项双击事件处理
 * @param item 被双击的列表项
 */
void NoteListWidget::onItemDoubleClicked(QListWidgetItem *item)
{
    if (item) {
        emit noteDoubleClicked(item->data(Qt::UserRole).toString());
    }
}

/**
 * @brief 当前选中项变化事件处理
 * @param current 新选中的列表项
 * @param previous 之前选中的列表项
 *
 * 知识点：
 * - Q_UNUSED 宏用于消除未使用参数的编译警告
 */
void NoteListWidget::onCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous)
    if (current) {
        emit noteSelected(current->data(Qt::UserRole).toString());
    }
}
