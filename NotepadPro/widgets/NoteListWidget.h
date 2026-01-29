/**
 * @file NoteListWidget.h
 * @brief 笔记列表控件
 *
 * 知识点：
 * - QListWidget 使用
 * - 自定义 QListWidgetItem
 * - 右键上下文菜单
 * - 信号槽连接
 */

#ifndef NOTELISTWIDGET_H
#define NOTELISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QMenu>

class Note;

/**
 * @class NoteListWidget
 * @brief 笔记列表控件
 *
 * 显示笔记列表，支持选择、右键菜单等操作
 */
class NoteListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NoteListWidget(QWidget *parent = nullptr);
    ~NoteListWidget() override = default;

    // 笔记操作
    void addNote(Note *note);
    void removeNote(const QString &noteId);
    void updateNote(Note *note);
    void clear();

    // 选择操作
    QString currentNoteId() const;
    void setCurrentNoteId(const QString &noteId);

    // 刷新列表
    void refreshList();

signals:
    void noteSelected(const QString &noteId);
    void noteDoubleClicked(const QString &noteId);
    void createNoteRequested();
    void deleteNoteRequested(const QString &noteId);
    void notePropertiesRequested(const QString &noteId);
    void renameNoteRequested(const QString &noteId);  // 新增：重命名信号

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    void setupUi();
    void createContextMenu();
    void connectSignals();

    QListWidgetItem* findItemByNoteId(const QString &noteId);
    void updateItemFromNote(QListWidgetItem *item, Note *note);

private slots:
    void onItemClicked(QListWidgetItem *item);
    void onItemDoubleClicked(QListWidgetItem *item);
    void onCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    QVBoxLayout *m_layout;
    QListWidget *m_listWidget;
    QMenu *m_contextMenu;

    // 上下文菜单动作
    QAction *m_newNoteAction;
    QAction *m_renameNoteAction;   // 新增：重命名动作
    QAction *m_deleteNoteAction;
    QAction *m_propertiesAction;
};

#endif // NOTELISTWIDGET_H
