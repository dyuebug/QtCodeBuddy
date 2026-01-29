/**
 * @file NoteManager.h
 * @brief 笔记管理器
 *
 * 知识点：
 * - 单例模式
 * - QFile 文件操作
 * - QJsonDocument 数据持久化
 * - 信号槽机制
 */

#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>

#include "Note.h"
#include "Category.h"

/**
 * @class NoteManager
 * @brief 笔记和分类的管理器
 *
 * 负责笔记和分类的增删改查以及数据持久化
 */
class NoteManager : public QObject
{
    Q_OBJECT

public:
    static NoteManager* instance();

    // 笔记操作
    Note* createNote(const QString &title = QString());
    Note* getNote(const QString &id) const;
    QList<Note*> getAllNotes() const;
    QList<Note*> getNotesByCategory(const QString &categoryId) const;
    QList<Note*> searchNotes(const QString &keyword) const;
    bool deleteNote(const QString &id);
    int noteCount() const;

    // 分类操作
    Category* createCategory(const QString &name);
    Category* getCategory(const QString &id) const;
    QList<Category*> getAllCategories() const;
    QList<Category*> getRootCategories() const;
    QList<Category*> getChildCategories(const QString &parentId) const;
    bool deleteCategory(const QString &id);
    int categoryCount() const;

    // 数据持久化
    bool saveToFile(const QString &filePath = QString());
    bool loadFromFile(const QString &filePath = QString());
    QString defaultDataPath() const;

    // 数据状态
    bool isDirty() const;
    void setDirty(bool dirty);

signals:
    // 笔记相关信号
    void noteCreated(Note *note);
    void noteDeleted(const QString &id);
    void noteModified(Note *note);
    void notesChanged();

    // 分类相关信号
    void categoryCreated(Category *category);
    void categoryDeleted(const QString &id);
    void categoryModified(Category *category);
    void categoriesChanged();

    // 数据状态信号
    void dataLoaded();
    void dataSaved();
    void dirtyChanged(bool dirty);

private:
    explicit NoteManager(QObject *parent = nullptr);
    ~NoteManager() override;

    // 禁止拷贝
    NoteManager(const NoteManager&) = delete;
    NoteManager& operator=(const NoteManager&) = delete;

    void connectNoteSignals(Note *note);
    void connectCategorySignals(Category *category);

    static NoteManager *s_instance;

    QMap<QString, Note*> m_notes;
    QMap<QString, Category*> m_categories;
    QString m_dataFilePath;
    bool m_isDirty;
};

#endif // NOTEMANAGER_H
