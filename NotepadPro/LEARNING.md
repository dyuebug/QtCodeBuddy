# NotepadPro 学习路线图

## 目录

1. [学习顺序](#1-学习顺序)
2. [阶段一：程序入口 main.cpp](#2-阶段一程序入口-maincpp)
3. [阶段二：数据模型 Note](#3-阶段二数据模型-note)
4. [阶段三：数据模型 Category](#4-阶段三数据模型-category)
5. [阶段四：数据管理器 NoteManager](#5-阶段四数据管理器-notemanager)
6. [阶段五：搜索控件 SearchWidget](#6-阶段五搜索控件-searchwidget)
7. [阶段六：笔记列表 NoteListWidget](#7-阶段六笔记列表-notelistwidget)
8. [阶段七：分类树 CategoryTree](#8-阶段七分类树-categorytree)
9. [阶段八：富文本编辑器 RichTextEditor](#9-阶段八富文本编辑器-richtexteditor)
10. [阶段九：主窗口 MainWindow](#10-阶段九主窗口-mainwindow)
11. [调用关系总图](#11-调用关系总图)
12. [C++ 语法速查](#12-c-语法速查)
13. [Qt 知识速查](#13-qt-知识速查)

---

## 1. 学习顺序

```
推荐学习路径（由简到繁）：

┌─────────────────────────────────────────────────────────┐
│  第1步: main.cpp                                        │
│  理解 Qt 应用程序的启动流程                              │
└─────────────────────┬───────────────────────────────────┘
                      ▼
┌─────────────────────────────────────────────────────────┐
│  第2步: core/Note.h/cpp                                 │
│  学习数据模型、Q_OBJECT、Q_PROPERTY                      │
└─────────────────────┬───────────────────────────────────┘
                      ▼
┌─────────────────────────────────────────────────────────┐
│  第3步: core/Category.h/cpp                             │
│  巩固数据模型，理解 QColor                               │
└─────────────────────┬───────────────────────────────────┘
                      ▼
┌─────────────────────────────────────────────────────────┐
│  第4步: core/NoteManager.h/cpp                          │
│  学习单例模式、QHash、JSON 序列化                        │
└─────────────────────┬───────────────────────────────────┘
                      ▼
┌─────────────────────────────────────────────────────────┐
│  第5步: widgets/SearchWidget.h/cpp                      │
│  学习简单自定义控件、QTimer、事件过滤器                   │
└─────────────────────┬───────────────────────────────────┘
                      ▼
┌─────────────────────────────────────────────────────────┐
│  第6步: widgets/NoteListWidget.h/cpp                    │
│  学习 QListWidget、右键菜单、信号转发                    │
└─────────────────────┬───────────────────────────────────┘
                      ▼
┌─────────────────────────────────────────────────────────┐
│  第7步: widgets/CategoryTree.h/cpp                      │
│  学习 QTreeWidget、数据过滤                              │
└─────────────────────┬───────────────────────────────────┘
                      ▼
┌─────────────────────────────────────────────────────────┐
│  第8步: widgets/RichTextEditor.h/cpp                    │
│  学习 QTextEdit、文本格式、复杂控件组合                   │
└─────────────────────┬───────────────────────────────────┘
                      ▼
┌─────────────────────────────────────────────────────────┐
│  第9步: mainwindow/MainWindow.h/cpp                     │
│  学习 QMainWindow、整合所有组件                          │
└─────────────────────────────────────────────────────────┘
```

---

## 2. 阶段一：程序入口 main.cpp

### 2.1 完整源代码

**文件路径**: `main.cpp`

```cpp
/**
 * @file main.cpp
 * @brief NotepadPro 个人笔记本应用 - 程序入口
 *
 * 本项目是一个综合性的 Qt6 学习项目，整合了以下知识点：
 * - Chapter01: QApplication 程序入口
 * - Chapter02: 基础控件使用
 * - Chapter03: 布局管理
 * - Chapter04: 信号与槽机制
 * - Chapter05: 事件处理
 * - Chapter06: 对话框
 * - Chapter07: QMainWindow 主窗口
 * - Chapter08: 自定义控件
 */

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 设置应用程序信息
    app.setApplicationName("NotepadPro");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("QtCodeBuddy");
    app.setOrganizationDomain("qtcodebuddy.com");

    // 设置应用程序样式
    app.setStyle("Fusion");

    // 创建并显示主窗口
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
```

### 2.2 逐行解析

| 行号 | 代码 | 说明 |
|------|------|------|
| 16 | `#include <QApplication>` | Qt GUI 应用程序核心类 |
| 20 | `#include "MainWindow.h"` | 包含自定义主窗口头文件 |
| 22 | `int main(int argc, char *argv[])` | C++ 程序入口，argc 是参数个数，argv 是参数数组 |
| 24 | `QApplication app(argc, argv)` | 创建应用程序对象，管理 GUI 程序的控制流和主要设置 |
| 27-30 | `app.setApplicationName(...)` | 设置应用信息，影响 QSettings 存储路径 |
| 33 | `app.setStyle("Fusion")` | 设置界面风格，Fusion 是跨平台统一风格 |
| 36 | `MainWindow mainWindow` | 在栈上创建主窗口对象 |
| 37 | `mainWindow.show()` | 显示窗口（Qt 窗口默认隐藏） |
| 39 | `return app.exec()` | 进入事件循环，程序在此阻塞直到退出 |

### 2.3 涉及的 C++ 语法

| 语法 | 示例 | 说明 |
|------|------|------|
| 头文件包含 | `#include <QApplication>` | 尖括号表示系统/库头文件 |
| 头文件包含 | `#include "MainWindow.h"` | 双引号表示项目内头文件 |
| 函数参数 | `int argc, char *argv[]` | argc 是 int，argv 是字符指针数组 |
| 对象创建 | `QApplication app(...)` | 栈上创建对象，自动析构 |
| 成员函数调用 | `app.setApplicationName(...)` | 点号调用对象的成员函数 |
| 返回值 | `return app.exec()` | 返回事件循环的退出码 |

### 2.4 涉及的 Qt 知识

| 知识点 | 说明 |
|--------|------|
| `QApplication` | 管理 GUI 应用程序的控制流，每个程序只能有一个 |
| `exec()` | 启动事件循环，处理用户输入、定时器、网络等事件 |
| `setOrganizationName` | 设置组织名，QSettings 会用它来确定配置文件路径 |
| `setStyle` | 设置界面风格，可选 "Fusion"、"Windows" 等 |

---

## 3. 阶段二：数据模型 Note

### 3.1 头文件 Note.h

**文件路径**: `core/Note.h`

```cpp
/**
 * @file Note.h
 * @brief 笔记数据模型
 *
 * 知识点：
 * - Q_OBJECT 宏和元对象系统
 * - Q_PROPERTY 属性系统
 * - 自定义信号
 * - QDateTime 时间处理
 */

#ifndef NOTE_H
#define NOTE_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QUuid>
#include <QJsonObject>

/**
 * @class Note
 * @brief 笔记数据模型类
 *
 * 存储单个笔记的所有信息，包括标题、内容、分类、时间戳等
 */
class Note : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QString categoryId READ categoryId WRITE setCategoryId NOTIFY categoryIdChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt CONSTANT)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(bool isPinned READ isPinned WRITE setPinned NOTIFY isPinnedChanged)

public:
    explicit Note(QObject *parent = nullptr);
    explicit Note(const QString &title, const QString &content = QString(),
                  QObject *parent = nullptr);
    ~Note() override = default;

    // Getter 方法
    QString id() const;
    QString title() const;
    QString content() const;
    QString categoryId() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    bool isPinned() const;

    // Setter 方法
    void setTitle(const QString &title);
    void setContent(const QString &content);
    void setCategoryId(const QString &categoryId);
    void setPinned(bool pinned);

    // JSON 序列化
    QJsonObject toJson() const;
    static Note* fromJson(const QJsonObject &json, QObject *parent = nullptr);

    // 辅助方法
    QString preview(int maxLength = 100) const;
    bool containsText(const QString &text, Qt::CaseSensitivity cs = Qt::CaseInsensitive) const;

signals:
    void titleChanged(const QString &title);
    void contentChanged(const QString &content);
    void categoryIdChanged(const QString &categoryId);
    void updatedAtChanged(const QDateTime &updatedAt);
    void isPinnedChanged(bool isPinned);
    void noteModified();

private:
    void updateTimestamp();

    QString m_id;
    QString m_title;
    QString m_content;
    QString m_categoryId;
    QDateTime m_createdAt;
    QDateTime m_updatedAt;
    bool m_isPinned;
};

#endif // NOTE_H
```

### 3.2 头文件逐行解析

| 行号 | 代码 | 说明 |
|------|------|------|
| 12-13 | `#ifndef NOTE_H` / `#define NOTE_H` | 头文件保护宏，防止重复包含 |
| 15-19 | `#include <QObject>` 等 | 包含所需的 Qt 头文件 |
| 27 | `class Note : public QObject` | 继承 QObject，获得元对象系统支持 |
| 29 | `Q_OBJECT` | 启用元对象系统（信号槽、属性、反射） |
| 31-37 | `Q_PROPERTY(...)` | 声明属性，支持 QML 绑定和属性系统 |
| 40-42 | `explicit Note(...)` | explicit 防止隐式类型转换 |
| 43 | `~Note() override = default` | 使用默认析构函数，override 表示重写基类虚函数 |
| 68-74 | `signals:` | 信号声明区域，信号由 moc 自动实现 |
| 76-85 | `private:` | 私有成员变量，使用 m_ 前缀命名 |

### 3.3 涉及的 C++ 语法

| 语法 | 示例 | 说明 |
|------|------|------|
| 头文件保护 | `#ifndef NOTE_H` | 防止头文件被多次包含 |
| 类继承 | `class Note : public QObject` | public 继承，子类可访问基类 public/protected 成员 |
| explicit | `explicit Note(...)` | 防止单参数构造函数的隐式转换 |
| override | `~Note() override` | 明确表示重写基类虚函数，编译器会检查 |
| = default | `= default` | 使用编译器生成的默认实现 |
| const 成员函数 | `QString id() const` | 不修改对象状态的成员函数 |
| 静态成员函数 | `static Note* fromJson(...)` | 不依赖对象实例，通过类名调用 |
| 默认参数 | `int maxLength = 100` | 调用时可省略该参数 |

### 3.4 涉及的 Qt 知识

| 知识点 | 说明 |
|--------|------|
| `Q_OBJECT` | 启用元对象系统，必须放在类声明的私有区域 |
| `Q_PROPERTY` | 声明属性：READ(读取函数) WRITE(写入函数) NOTIFY(变化信号) CONSTANT(常量) |
| `signals:` | 信号声明关键字，信号由 moc 工具自动生成实现代码 |
| `QObject` | Qt 对象模型基类，提供对象树、信号槽、属性系统 |
| `QDateTime` | 日期时间类，支持时区、格式化、计算 |
| `QUuid` | 全局唯一标识符，用于生成不重复的 ID |
| `QJsonObject` | JSON 对象，用于数据序列化 |

### 3.5 实现文件 Note.cpp

**文件路径**: `core/Note.cpp`

```cpp
/**
 * @file Note.cpp
 * @brief 笔记数据模型实现
 *
 * 知识点：
 * - QUuid 生成全局唯一标识符
 * - QDateTime 日期时间处理
 * - QJsonObject JSON 序列化/反序列化
 * - Q_PROPERTY 属性系统的 getter/setter 实现
 * - 信号发射通知属性变化
 */

#include "Note.h"
#include <QJsonObject>
#include <QRegularExpression>

/**
 * @brief 默认构造函数
 * @param parent 父对象指针
 *
 * 知识点：
 * - QUuid::createUuid() 生成 UUID
 * - QUuid::WithoutBraces 去除花括号格式
 * - 初始化列表设置成员变量
 */
Note::Note(QObject *parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_title(tr("新建笔记"))
    , m_createdAt(QDateTime::currentDateTime())
    , m_updatedAt(m_createdAt)
    , m_isPinned(false)
{
}

/**
 * @brief 带参数构造函数
 * @param title 笔记标题
 * @param content 笔记内容
 * @param parent 父对象指针
 */
Note::Note(const QString &title, const QString &content, QObject *parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_title(title)
    , m_content(content)
    , m_createdAt(QDateTime::currentDateTime())
    , m_updatedAt(m_createdAt)
    , m_isPinned(false)
{
}
```

**Getter 和 Setter 方法（续）**：

```cpp
// ========== Getter 方法 ==========

QString Note::id() const { return m_id; }
QString Note::title() const { return m_title; }
QString Note::content() const { return m_content; }
QString Note::categoryId() const { return m_categoryId; }
QDateTime Note::createdAt() const { return m_createdAt; }
QDateTime Note::updatedAt() const { return m_updatedAt; }
bool Note::isPinned() const { return m_isPinned; }

// ========== Setter 方法 ==========

/**
 * @brief 设置笔记标题
 * 知识点：属性变化检测 + emit 发出信号
 */
void Note::setTitle(const QString &title)
{
    if (m_title != title) {
        m_title = title;
        updateTimestamp();
        emit titleChanged(m_title);
        emit noteModified();
    }
}
```

**JSON 序列化方法**：

```cpp
/**
 * @brief 序列化为 JSON 对象
 * 知识点：QJsonObject 键值对存储
 */
QJsonObject Note::toJson() const
{
    QJsonObject json;
    json["id"] = m_id;
    json["title"] = m_title;
    json["content"] = m_content;
    json["categoryId"] = m_categoryId;
    json["createdAt"] = m_createdAt.toString(Qt::ISODate);
    json["updatedAt"] = m_updatedAt.toString(Qt::ISODate);
    json["isPinned"] = m_isPinned;
    return json;
}

/**
 * @brief 从 JSON 对象反序列化（静态工厂方法）
 */
Note* Note::fromJson(const QJsonObject &json, QObject *parent)
{
    Note *note = new Note(parent);
    note->m_id = json["id"].toString();
    note->m_title = json["title"].toString();
    note->m_content = json["content"].toString();
    note->m_categoryId = json["categoryId"].toString();
    note->m_createdAt = QDateTime::fromString(
        json["createdAt"].toString(), Qt::ISODate);
    note->m_updatedAt = QDateTime::fromString(
        json["updatedAt"].toString(), Qt::ISODate);
    note->m_isPinned = json["isPinned"].toBool();
    return note;
}
```

### 3.6 Note.cpp 关键代码解析

| 代码 | 说明 |
|------|------|
| `QUuid::createUuid().toString(QUuid::WithoutBraces)` | 生成不带花括号的 UUID 字符串 |
| `: QObject(parent)` | 初始化列表调用基类构造函数 |
| `if (m_title != title)` | 属性变化检测，避免无意义的信号发射 |
| `emit titleChanged(m_title)` | 发射信号通知观察者属性已变化 |
| `json["key"] = value` | QJsonObject 键值对赋值 |
| `QDateTime::toString(Qt::ISODate)` | 转换为 ISO 8601 格式字符串 |
| `QDateTime::fromString(..., Qt::ISODate)` | 从 ISO 格式字符串解析日期时间 |

---

## 4. 阶段三：数据模型 Category

### 4.1 头文件 Category.h

**文件路径**: `core/Category.h`

```cpp
#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QUuid>
#include <QJsonObject>

class Category : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString parentId READ parentId WRITE setParentId NOTIFY parentIdChanged)

public:
    explicit Category(QObject *parent = nullptr);
    explicit Category(const QString &name, QObject *parent = nullptr);
    ~Category() override = default;

    // Getter 方法
    QString id() const;
    QString name() const;
    QColor color() const;
    QString parentId() const;

    // Setter 方法
    void setName(const QString &name);
    void setColor(const QColor &color);
    void setParentId(const QString &parentId);

    // JSON 序列化
    QJsonObject toJson() const;
    static Category* fromJson(const QJsonObject &json, QObject *parent = nullptr);

signals:
    void nameChanged(const QString &name);
    void colorChanged(const QColor &color);
    void parentIdChanged(const QString &parentId);
    void categoryModified();

private:
    QString m_id;
    QString m_name;
    QColor m_color;
    QString m_parentId;
};

#endif // CATEGORY_H
```

### 4.2 实现文件 Category.cpp

**文件路径**: `core/Category.cpp`

```cpp
#include "Category.h"

Category::Category(QObject *parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_name(tr("新建分类"))
    , m_color(Qt::blue)
{
}

Category::Category(const QString &name, QObject *parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_name(name)
    , m_color(Qt::blue)
{
}
```

**Getter/Setter 方法**：

```cpp
// Getter 方法
QString Category::id() const { return m_id; }
QString Category::name() const { return m_name; }
QColor Category::color() const { return m_color; }
QString Category::parentId() const { return m_parentId; }

// Setter 方法
void Category::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged(m_name);
        emit categoryModified();
    }
}

void Category::setColor(const QColor &color)
{
    if (m_color != color) {
        m_color = color;
        emit colorChanged(m_color);
        emit categoryModified();
    }
}
```

**JSON 序列化**：

```cpp
QJsonObject Category::toJson() const
{
    QJsonObject json;
    json["id"] = m_id;
    json["name"] = m_name;
    json["color"] = m_color.name();  // 返回 "#RRGGBB" 格式
    json["parentId"] = m_parentId;
    return json;
}

Category* Category::fromJson(const QJsonObject &json, QObject *parent)
{
    Category *category = new Category(parent);
    category->m_id = json["id"].toString();
    category->m_name = json["name"].toString();
    category->m_color = QColor(json["color"].toString());
    category->m_parentId = json["parentId"].toString();
    return category;
}
```

### 4.3 涉及的 Qt 知识

| 知识点 | 说明 |
|--------|------|
| `QColor` | Qt 颜色类，支持 RGB、HSV、CMYK 等颜色模型 |
| `QColor::name()` | 返回 "#RRGGBB" 格式的颜色字符串 |
| `QColor(QString)` | 从颜色字符串构造 QColor 对象 |
| `Qt::blue` | Qt 预定义颜色常量 |

---

## 5. 阶段四：数据管理器 NoteManager

### 5.1 头文件 NoteManager.h

**文件路径**: `core/NoteManager.h`

**设计模式：单例模式** - 确保全局只有一个数据管理器实例

```cpp
#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>
#include "Note.h"
#include "Category.h"

class NoteManager : public QObject
{
    Q_OBJECT

public:
    // 单例访问接口
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
    bool deleteCategory(const QString &id);

    // 数据持久化
    bool saveToFile(const QString &filePath = QString());
    bool loadFromFile(const QString &filePath = QString());
    QString defaultDataPath() const;

signals:
    void noteCreated(Note *note);
    void noteDeleted(const QString &id);
    void categoryCreated(Category *category);
    void categoryDeleted(const QString &id);
    void dataLoaded();
    void dataSaved();

private:
    // 私有构造函数（单例模式）
    explicit NoteManager(QObject *parent = nullptr);
    ~NoteManager() override;

    // 禁止拷贝（单例模式）
    NoteManager(const NoteManager&) = delete;
    NoteManager& operator=(const NoteManager&) = delete;

    static NoteManager *s_instance;  // 静态单例指针

    QMap<QString, Note*> m_notes;        // 笔记存储
    QMap<QString, Category*> m_categories;  // 分类存储
    QString m_dataFilePath;
    bool m_isDirty;
};

#endif // NOTEMANAGER_H
```

### 5.2 单例模式实现

**文件路径**: `core/NoteManager.cpp`

```cpp
#include "NoteManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>
#include <QDir>

// 静态成员初始化
NoteManager* NoteManager::s_instance = nullptr;

/**
 * @brief 获取单例实例（懒汉式）
 */
NoteManager* NoteManager::instance()
{
    if (!s_instance) {
        s_instance = new NoteManager();
    }
    return s_instance;
}

/**
 * @brief 私有构造函数
 */
NoteManager::NoteManager(QObject *parent)
    : QObject(parent)
    , m_isDirty(false)
{
    m_dataFilePath = defaultDataPath();
}

/**
 * @brief 析构函数 - 释放所有笔记和分类
 */
NoteManager::~NoteManager()
{
    qDeleteAll(m_notes);
    qDeleteAll(m_categories);
}
```

**笔记 CRUD 操作**：

```cpp
Note* NoteManager::createNote(const QString &title)
{
    Note *note = new Note(title.isEmpty() ? tr("新建笔记") : title,
                          QString(), this);
    connectNoteSignals(note);
    m_notes.insert(note->id(), note);
    setDirty(true);
    emit noteCreated(note);
    return note;
}

Note* NoteManager::getNote(const QString &id) const
{
    return m_notes.value(id, nullptr);
}

QList<Note*> NoteManager::getAllNotes() const
{
    return m_notes.values();
}

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
```

**JSON 数据持久化**：

```cpp
bool NoteManager::saveToFile(const QString &filePath)
{
    QString path = filePath.isEmpty() ? m_dataFilePath : filePath;

    QJsonObject root;

    // 保存笔记数组
    QJsonArray notesArray;
    for (Note *note : m_notes) {
        notesArray.append(note->toJson());
    }
    root["notes"] = notesArray;

    // 保存分类数组
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
    return true;
}
```

### 5.3 涉及的 C++ 语法

| 语法 | 示例 | 说明 |
|------|------|------|
| 单例模式 | `static NoteManager* instance()` | 全局唯一实例访问 |
| 静态成员 | `static NoteManager *s_instance` | 类级别共享变量 |
| = delete | `NoteManager(const NoteManager&) = delete` | 禁止拷贝构造 |
| 范围 for | `for (Note *note : m_notes)` | 遍历容器元素 |

### 5.4 涉及的 Qt 知识

| 知识点 | 说明 |
|--------|------|
| `QMap` | 有序键值对容器，按键排序 |
| `QJsonDocument` | JSON 文档类，用于解析和生成 JSON |
| `QJsonArray` | JSON 数组，存储多个 JSON 值 |
| `QFile` | 文件操作类 |
| `qDeleteAll()` | 批量删除容器中的指针对象 |

---

## 6. 阶段五：搜索控件 SearchWidget

### 6.1 头文件 SearchWidget.h

**文件路径**: `widgets/SearchWidget.h`

```cpp
#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTimer>

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent = nullptr);

    QString searchText() const;
    void clearSearch();

signals:
    void searchTextChanged(const QString &text);
    void searchRequested(const QString &text);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void onTextChanged(const QString &text);
    void onSearchTimeout();

private:
    QLineEdit *m_searchEdit;
    QPushButton *m_clearButton;
    QTimer *m_searchTimer;
    int m_searchDelay;
};

#endif // SEARCHWIDGET_H
```

### 6.2 实现文件 SearchWidget.cpp

**文件路径**: `widgets/SearchWidget.cpp`

```cpp
#include "SearchWidget.h"
#include <QKeyEvent>

SearchWidget::SearchWidget(QWidget *parent)
    : QWidget(parent)
    , m_searchDelay(300)
{
    setupUi();
    connectSignals();
}
```

**界面初始化和事件过滤器**：

```cpp
void SearchWidget::setupUi()
{
    m_layout = new QHBoxLayout(this);
    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText(tr("搜索笔记..."));
    m_searchEdit->installEventFilter(this);  // 安装事件过滤器

    m_clearButton = new QPushButton(tr("清除"), this);
    m_clearButton->setVisible(false);

    m_searchTimer = new QTimer(this);
    m_searchTimer->setSingleShot(true);  // 单次触发
}
```

**事件过滤器（拦截键盘事件）**：

```cpp
bool SearchWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_searchEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_Escape) {
            clearSearch();
            return true;  // 事件已处理
        }

        if (keyEvent->key() == Qt::Key_Return) {
            m_searchTimer->stop();
            emit searchRequested(m_searchEdit->text());
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}
```

**防抖动搜索（延迟触发）**：

```cpp
void SearchWidget::onTextChanged(const QString &text)
{
    m_clearButton->setVisible(!text.isEmpty());
    emit searchTextChanged(text);

    // 重启延迟定时器
    m_searchTimer->stop();
    if (!text.isEmpty()) {
        m_searchTimer->start(m_searchDelay);  // 300ms 后触发
    }
}

void SearchWidget::onSearchTimeout()
{
    emit searchRequested(m_searchEdit->text());
}
```

### 6.3 涉及的 Qt 知识

| 知识点 | 说明 |
|--------|------|
| `QTimer::setSingleShot(true)` | 单次触发定时器 |
| `installEventFilter()` | 安装事件过滤器 |
| `eventFilter()` | 重写事件过滤器方法 |
| `QKeyEvent` | 键盘事件类 |
| `setPlaceholderText()` | 设置输入框占位提示 |

---

## 7. 阶段六：笔记列表 NoteListWidget

### 7.1 头文件 NoteListWidget.h

**文件路径**: `widgets/NoteListWidget.h`

```cpp
#ifndef NOTELISTWIDGET_H
#define NOTELISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QMenu>

class Note;

class NoteListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NoteListWidget(QWidget *parent = nullptr);

    void addNote(Note *note);
    void removeNote(const QString &noteId);
    QString currentNoteId() const;

signals:
    void noteSelected(const QString &noteId);
    void createNoteRequested();
    void deleteNoteRequested(const QString &noteId);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QListWidget *m_listWidget;
    QMenu *m_contextMenu;
    QAction *m_newNoteAction;
    QAction *m_deleteNoteAction;
};

#endif // NOTELISTWIDGET_H
```

### 7.2 关键实现代码

```cpp
void NoteListWidget::setupUi()
{
    m_layout = new QVBoxLayout(this);
    m_listWidget = new QListWidget(this);
    m_listWidget->setAlternatingRowColors(true);
    m_layout->addWidget(m_listWidget);
}
```

**右键菜单事件处理**：

```cpp
void NoteListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}
```

### 7.3 涉及的 Qt 知识

| 知识点 | 说明 |
|--------|------|
| `QListWidget` | 列表控件，管理 QListWidgetItem |
| `Qt::UserRole` | 自定义数据角色，存储额外信息 |
| `contextMenuEvent` | 右键菜单事件 |
| `setAlternatingRowColors` | 交替行颜色 |

---

## 8. 阶段七：分类树 CategoryTree

### 8.1 头文件 CategoryTree.h

**文件路径**: `widgets/CategoryTree.h`

```cpp
#ifndef CATEGORYTREE_H
#define CATEGORYTREE_H

#include <QWidget>
#include <QTreeWidget>
#include <QMenu>

class Category;

class CategoryTree : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryTree(QWidget *parent = nullptr);

    void addCategory(Category *category);
    QString currentCategoryId() const;

signals:
    void categorySelected(const QString &categoryId);
    void createCategoryRequested();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QTreeWidget *m_treeWidget;
    QMenu *m_contextMenu;
};

#endif // CATEGORYTREE_H
```

### 8.2 涉及的 Qt 知识

| 知识点 | 说明 |
|--------|------|
| `QTreeWidget` | 树形控件 |
| `QTreeWidgetItem` | 树节点项 |

---

## 9. 阶段八：富文本编辑器 RichTextEditor

### 9.1 头文件 RichTextEditor.h

**文件路径**: `widgets/RichTextEditor.h`

```cpp
#ifndef RICHTEXTEDITOR_H
#define RICHTEXTEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QAction>
#include <QPushButton>

class RichTextEditor : public QWidget
{
    Q_OBJECT

public:
    explicit RichTextEditor(QWidget *parent = nullptr);

    QString toHtml() const;
    void setHtml(const QString &html);
    bool isModified() const;

signals:
    void textChanged();
    void modificationChanged(bool changed);

private:
    void setupUi();
    void createToolBar();
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);

private slots:
    void onBold(bool checked);
    void onCurrentCharFormatChanged(const QTextCharFormat &format);

private:
    QTextEdit *m_textEdit;
    QWidget *m_toolBarWidget;
    QPushButton *m_boldBtn;
    QAction *m_boldAction;
};

#endif // RICHTEXTEDITOR_H
```

### 9.2 关键实现代码

**格式应用方法**：

```cpp
void RichTextEditor::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = m_textEdit->textCursor();
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    m_textEdit->mergeCurrentCharFormat(format);
}
```

**按钮状态同步**：

```cpp
void RichTextEditor::onCurrentCharFormatChanged(const QTextCharFormat &format)
{
    m_boldBtn->blockSignals(true);
    m_boldBtn->setChecked(format.fontWeight() == QFont::Bold);
    m_boldBtn->blockSignals(false);
}
```

### 9.3 涉及的 Qt 知识

| 知识点 | 说明 |
|--------|------|
| `QTextEdit` | 富文本编辑器 |
| `QTextCharFormat` | 字符格式 |
| `QTextCursor` | 文本光标 |
| `blockSignals()` | 阻止信号发射 |

---

## 10. 阶段九：主窗口 MainWindow

### 10.1 头文件 MainWindow.h

**文件路径**: `mainwindow/MainWindow.h`

```cpp
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>

class NoteListWidget;
class RichTextEditor;
class CategoryTree;
class SearchWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setupUi();
    void createMenuBar();
    void createDockWidgets();
    void connectSignals();
    void loadSettings();
    void saveSettings();

private:
    NoteListWidget *m_noteList;
    RichTextEditor *m_editor;
    CategoryTree *m_categoryTree;
    QDockWidget *m_categoryDock;
    QDockWidget *m_noteListDock;
};

#endif // MAINWINDOW_H
```

### 10.2 关键实现代码

**停靠窗口创建**：

```cpp
void MainWindow::createDockWidgets()
{
    // 分类树停靠窗口
    m_categoryDock = new QDockWidget(tr("分类"), this);
    m_categoryDock->setWidget(m_categoryTree);
    addDockWidget(Qt::LeftDockWidgetArea, m_categoryDock);

    // 笔记列表停靠窗口
    m_noteListDock = new QDockWidget(tr("笔记"), this);
    m_noteListDock->setWidget(m_noteList);
    addDockWidget(Qt::LeftDockWidgetArea, m_noteListDock);

    // 垂直分割两个 Dock
    splitDockWidget(m_categoryDock, m_noteListDock, Qt::Vertical);
}
```

### 10.3 涉及的 Qt 知识

| 知识点 | 说明 |
|--------|------|
| `QMainWindow` | 主窗口框架 |
| `QDockWidget` | 停靠窗口 |
| `splitDockWidget` | 分割停靠窗口 |
| `QSettings` | 配置存储 |

---

## 11. 调用关系总图

```
┌─────────────────────────────────────────────────────────────┐
│                      MainWindow                              │
│  ┌─────────────┬─────────────┬─────────────┐                │
│  │ CategoryTree│ NoteListWidget│ RichTextEditor│             │
│  └──────┬──────┴──────┬──────┴──────┬──────┘                │
│         │             │             │                        │
│         └─────────────┼─────────────┘                        │
│                       ▼                                      │
│              ┌─────────────────┐                             │
│              │   NoteManager   │ (单例)                      │
│              │   ┌─────┬─────┐ │                             │
│              │   │Note │Category│                            │
│              │   └─────┴─────┘ │                             │
│              └─────────────────┘                             │
└─────────────────────────────────────────────────────────────┘
```

---

## 12. C++ 语法速查

| 语法 | 示例 | 说明 |
|------|------|------|
| 头文件保护 | `#ifndef XXX_H` | 防止重复包含 |
| 类继承 | `class A : public B` | 公有继承 |
| explicit | `explicit Foo(int)` | 防止隐式转换 |
| override | `void f() override` | 重写虚函数 |
| = default | `~Foo() = default` | 默认实现 |
| = delete | `Foo(const Foo&) = delete` | 禁止拷贝 |
| const 成员 | `int get() const` | 不修改对象 |
| static 成员 | `static Foo* instance()` | 类级别 |
| 初始化列表 | `: m_x(0), m_y(0)` | 构造函数初始化 |
| 范围 for | `for (auto &x : list)` | 遍历容器 |

---

## 13. Qt 知识速查

| 知识点 | 说明 |
|--------|------|
| `Q_OBJECT` | 启用元对象系统 |
| `Q_PROPERTY` | 声明属性 |
| `signals:` | 信号声明 |
| `emit` | 发射信号 |
| `connect()` | 连接信号槽 |
| `QApplication` | GUI 应用程序类 |
| `QMainWindow` | 主窗口框架 |
| `QDockWidget` | 停靠窗口 |
| `QListWidget` | 列表控件 |
| `QTreeWidget` | 树形控件 |
| `QTextEdit` | 富文本编辑器 |
| `QTimer` | 定时器 |
| `QJsonDocument` | JSON 文档 |
| `QSettings` | 配置存储 |
| `eventFilter()` | 事件过滤器 |

