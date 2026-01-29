/**
 * @file NoteManager.cpp
 * @brief 笔记管理器实现
 *
 * 知识点：
 * - 单例模式（Singleton Pattern）的实现
 * - QHash 哈希表容器的使用
 * - QJsonDocument/QJsonObject/QJsonArray JSON 序列化
 * - QFile 文件读写操作
 * - QStandardPaths 获取标准路径
 * - 信号槽机制实现数据变化通知
 */

#include "NoteManager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>
#include <QDir>

// 静态成员初始化 - 单例模式的实例指针
NoteManager* NoteManager::s_instance = nullptr;

/**
 * @brief 获取单例实例
 * @return NoteManager 单例指针
 *
 * 知识点：
 * - 懒汉式单例：首次调用时创建实例
 * - 线程安全注意：此实现非线程安全，适用于单线程 GUI 应用
 */
NoteManager* NoteManager::instance()
{
    if (!s_instance) {
        s_instance = new NoteManager();
    }
    return s_instance;
}

/**
 * @brief 构造函数（私有）
 * @param parent 父对象指针
 *
 * 知识点：
 * - 私有构造函数是单例模式的关键
 * - 初始化列表设置成员变量初始值
 */
NoteManager::NoteManager(QObject *parent)
    : QObject(parent)
    , m_isDirty(false)
{
    m_dataFilePath = defaultDataPath();
}

/**
 * @brief 析构函数
 *
 * 知识点：
 * - qDeleteAll() 批量删除容器中的指针对象
 * - 防止内存泄漏
 */
NoteManager::~NoteManager()
{
    qDeleteAll(m_notes);
    qDeleteAll(m_categories);
}

/**
 * @brief 创建新笔记
 * @param title 笔记标题（可选）
 * @return 新创建的笔记指针
 *
 * 知识点：
 * - QHash::insert() 插入键值对
 * - emit 发出信号通知观察者
 */
Note* NoteManager::createNote(const QString &title)
{
    Note *note = new Note(title.isEmpty() ? tr("新建笔记") : title, QString(), this);
    connectNoteSignals(note);
    m_notes.insert(note->id(), note);
    setDirty(true);
    emit noteCreated(note);
    emit notesChanged();
    return note;
}

/**
 * @brief 根据ID获取笔记
 * @param id 笔记ID
 * @return 笔记指针，未找到返回 nullptr
 */
Note* NoteManager::getNote(const QString &id) const
{
    return m_notes.value(id, nullptr);
}

/**
 * @brief 获取所有笔记
 * @return 笔记列表
 */
QList<Note*> NoteManager::getAllNotes() const
{
    return m_notes.values();
}

/**
 * @brief 根据分类ID获取笔记
 * @param categoryId 分类ID
 * @return 属于该分类的笔记列表
 *
 * 这是分类-笔记关联的核心方法
 */
QList<Note*> NoteManager::getNotesByCategory(const QString &categoryId) const
{
    QList<Note*> result;
    for (Note *note : m_notes) {
        if (note->categoryId() == categoryId) {
            result.append(note);
        }
    }
    return result;
}

/**
 * @brief 搜索笔记
 * @param keyword 搜索关键词
 * @return 匹配的笔记列表
 */
QList<Note*> NoteManager::searchNotes(const QString &keyword) const
{
    QList<Note*> result;
    for (Note *note : m_notes) {
        if (note->containsText(keyword)) {
            result.append(note);
        }
    }
    return result;
}

/**
 * @brief 删除笔记
 * @param id 笔记ID
 * @return 删除成功返回 true
 *
 * 知识点：
 * - QHash::take() 移除并返回值
 */
bool NoteManager::deleteNote(const QString &id)
{
    if (!m_notes.contains(id)) {
        return false;
    }
    Note *note = m_notes.take(id);
    QString noteId = note->id();
    delete note;
    setDirty(true);
    emit noteDeleted(noteId);
    emit notesChanged();
    return true;
}

/**
 * @brief 获取笔记数量
 * @return 笔记总数
 */
int NoteManager::noteCount() const
{
    return m_notes.count();
}

/**
 * @brief 创建新分类
 * @param name 分类名称
 * @return 新创建的分类指针
 */
Category* NoteManager::createCategory(const QString &name)
{
    Category *category = new Category(name, this);
    connectCategorySignals(category);
    m_categories.insert(category->id(), category);
    setDirty(true);
    emit categoryCreated(category);
    emit categoriesChanged();
    return category;
}

/**
 * @brief 根据ID获取分类
 * @param id 分类ID
 * @return 分类指针，未找到返回 nullptr
 */
Category* NoteManager::getCategory(const QString &id) const
{
    return m_categories.value(id, nullptr);
}

/**
 * @brief 获取所有分类
 * @return 分类列表
 */
QList<Category*> NoteManager::getAllCategories() const
{
    return m_categories.values();
}

/**
 * @brief 获取根级分类（无父分类）
 * @return 根级分类列表
 */
QList<Category*> NoteManager::getRootCategories() const
{
    QList<Category*> result;
    for (Category *cat : m_categories) {
        if (cat->parentId().isEmpty()) {
            result.append(cat);
        }
    }
    return result;
}

/**
 * @brief 获取子分类
 * @param parentId 父分类ID
 * @return 子分类列表
 */
QList<Category*> NoteManager::getChildCategories(const QString &parentId) const
{
    QList<Category*> result;
    for (Category *cat : m_categories) {
        if (cat->parentId() == parentId) {
            result.append(cat);
        }
    }
    return result;
}

/**
 * @brief 删除分类
 * @param id 分类ID
 * @return 删除成功返回 true
 */
bool NoteManager::deleteCategory(const QString &id)
{
    if (!m_categories.contains(id)) {
        return false;
    }
    Category *category = m_categories.take(id);
    QString catId = category->id();
    delete category;
    setDirty(true);
    emit categoryDeleted(catId);
    emit categoriesChanged();
    return true;
}

/**
 * @brief 获取分类数量
 * @return 分类总数
 */
int NoteManager::categoryCount() const
{
    return m_categories.count();
}

/**
 * @brief 保存数据到文件
 * @param filePath 文件路径（可选，默认使用内部路径）
 * @return 保存成功返回 true
 *
 * 知识点：
 * - QJsonDocument 创建 JSON 文档
 * - QJsonArray 存储数组数据
 * - QFile::open(QIODevice::WriteOnly) 写入模式
 */
bool NoteManager::saveToFile(const QString &filePath)
{
    QString path = filePath.isEmpty() ? m_dataFilePath : filePath;

    QJsonObject root;

    // 保存笔记
    QJsonArray notesArray;
    for (Note *note : m_notes) {
        notesArray.append(note->toJson());
    }
    root["notes"] = notesArray;

    // 保存分类
    QJsonArray categoriesArray;
    for (Category *cat : m_categories) {
        categoriesArray.append(cat->toJson());
    }
    root["categories"] = categoriesArray;

    QJsonDocument doc(root);

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson());
    file.close();

    setDirty(false);
    emit dataSaved();
    return true;
}

/**
 * @brief 从文件加载数据
 * @param filePath 文件路径（可选）
 * @return 加载成功返回 true
 *
 * 知识点：
 * - QJsonDocument::fromJson() 解析 JSON
 * - QFile::readAll() 读取全部内容
 */
bool NoteManager::loadFromFile(const QString &filePath)
{
    QString path = filePath.isEmpty() ? m_dataFilePath : filePath;

    QFile file(path);
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        return false;
    }

    QJsonObject root = doc.object();

    // 清空现有数据
    qDeleteAll(m_notes);
    m_notes.clear();
    qDeleteAll(m_categories);
    m_categories.clear();

    // 加载笔记
    QJsonArray notesArray = root["notes"].toArray();
    for (const QJsonValue &val : notesArray) {
        Note *note = Note::fromJson(val.toObject(), this);
        connectNoteSignals(note);
        m_notes.insert(note->id(), note);
    }

    // 加载分类
    QJsonArray categoriesArray = root["categories"].toArray();
    for (const QJsonValue &val : categoriesArray) {
        Category *cat = Category::fromJson(val.toObject(), this);
        connectCategorySignals(cat);
        m_categories.insert(cat->id(), cat);
    }

    setDirty(false);
    emit dataLoaded();
    emit notesChanged();
    emit categoriesChanged();
    return true;
}

/**
 * @brief 获取默认数据文件路径
 * @return 数据文件完整路径
 *
 * 知识点：
 * - QStandardPaths::AppDataLocation 获取应用数据目录
 * - QDir::mkpath() 递归创建目录
 */
QString NoteManager::defaultDataPath() const
{
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dataDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    return dataDir + "/notepad_data.json";
}

/**
 * @brief 检查数据是否有未保存的修改
 * @return 有修改返回 true
 */
bool NoteManager::isDirty() const
{
    return m_isDirty;
}

/**
 * @brief 设置脏标记
 * @param dirty 是否有修改
 */
void NoteManager::setDirty(bool dirty)
{
    if (m_isDirty != dirty) {
        m_isDirty = dirty;
        emit dirtyChanged(m_isDirty);
    }
}

/**
 * @brief 连接笔记信号
 * @param note 笔记对象指针
 *
 * 知识点：
 * - Lambda 捕获 this 和 note 指针
 * - 信号转发模式
 */
void NoteManager::connectNoteSignals(Note *note)
{
    connect(note, &Note::noteModified, this, [this, note]() {
        setDirty(true);
        emit noteModified(note);
    });
}

/**
 * @brief 连接分类信号
 * @param category 分类对象指针
 */
void NoteManager::connectCategorySignals(Category *category)
{
    connect(category, &Category::categoryModified, this, [this, category]() {
        setDirty(true);
        emit categoryModified(category);
    });
}
