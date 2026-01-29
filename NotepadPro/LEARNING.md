# NotepadPro 学习路线图

## 目录

1. [学习顺序](#1-学习顺序)
2. [阶段一：程序入口](#2-阶段一程序入口)
3. [阶段二：核心数据模型](#3-阶段二核心数据模型)
4. [阶段三：数据管理器](#4-阶段三数据管理器)
5. [阶段四：自定义控件](#5-阶段四自定义控件)
6. [阶段五：主窗口整合](#6-阶段五主窗口整合)
7. [调用关系图](#7-调用关系图)
8. [C++ 语法速查](#8-c-语法速查)
9. [Qt 知识速查](#9-qt-知识速查)

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
│  第9步: dialogs/*.h/cpp                                 │
│  学习 QDialog、表单布局、数据验证                        │
└─────────────────────┬───────────────────────────────────┘
                      ▼
┌─────────────────────────────────────────────────────────┐
│  第10步: mainwindow/MainWindow.h/cpp                    │
│  学习 QMainWindow、整合所有组件                          │
└─────────────────────────────────────────────────────────┘
```

---

## 2. 阶段一：程序入口

### 文件：main.cpp

```cpp
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);  // 创建应用程序对象

    // 设置应用程序信息（用于 QSettings）
    app.setOrganizationName("QtLearning");
    app.setApplicationName("NotepadPro");

    MainWindow window;  // 创建主窗口
    window.show();      // 显示窗口

    return app.exec();  // 进入事件循环
}
```

### 涉及知识点

| 知识点 | 说明 |
|--------|------|
| `QApplication` | Qt GUI 应用程序的核心，管理事件循环 |
| `argc/argv` | 命令行参数，传递给 QApplication |
| `app.exec()` | 启动事件循环，程序在此阻塞直到退出 |
| `setOrganizationName` | 设置组织名，影响 QSettings 存储路径 |

---

## 3. 阶段二：核心数据模型

### 文件：core/Note.h

**类结构概览：**

```cpp
class Note : public QObject
{
    Q_OBJECT  // 启用元对象系统

    // 属性声明（可用于 QML 绑定）
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    explicit Note(QObject *parent = nullptr);

    // Getter
    QString id() const;
    QString title() const;
    QString categoryId() const;  // 关联分类

    // Setter
    void setTitle(const QString &title);
    void setCategoryId(const QString &categoryId);

    // JSON 序列化
    QJsonObject toJson() const;
    static Note* fromJson(const QJsonObject &json, QObject *parent = nullptr);

signals:
    void titleChanged(const QString &title);
    void noteModified();  // 任何属性变化时发出

private:
    QString m_id;        // UUID 唯一标识
    QString m_title;
    QString m_categoryId;
    QDateTime m_createdAt;
};
```

### C++ 语法要点

| 语法 | 示例 | 说明 |
|------|------|------|
| 继承 | `class Note : public QObject` | 公有继承 QObject |
| explicit | `explicit Note(QObject *parent)` | 防止隐式类型转换 |
| const 成员函数 | `QString title() const` | 不修改成员变量 |
| 默认参数 | `QObject *parent = nullptr` | 可选参数 |
| 静态成员函数 | `static Note* fromJson(...)` | 工厂方法 |

### Qt 知识要点

| 知识点 | 说明 |
|--------|------|
| `Q_OBJECT` | 必须放在类声明开头，启用信号槽 |
| `Q_PROPERTY` | 声明属性，支持 READ/WRITE/NOTIFY |
| `signals:` | 信号声明区，只声明不实现 |
| `emit` | 发射信号的关键字 |
| `QUuid` | 生成全局唯一标识符 |

---

## 4. 阶段三：数据管理器

### 文件：core/NoteManager.h

**单例模式实现：**

```cpp
class NoteManager : public QObject
{
    Q_OBJECT

public:
    static NoteManager* instance();  // 获取单例

    // 笔记 CRUD
    Note* createNote(const QString &title = QString());
    Note* getNote(const QString &id) const;
    QList<Note*> getNotesByCategory(const QString &categoryId) const;
    bool deleteNote(const QString &id);

    // 持久化
    bool saveToFile(const QString &path = QString());
    bool loadFromFile(const QString &path = QString());

signals:
    void noteCreated(Note *note);
    void noteDeleted(const QString &id);
    void notesChanged();

private:
    NoteManager(QObject *parent = nullptr);  // 私有构造
    static NoteManager* s_instance;          // 静态实例指针

    QHash<QString, Note*> m_notes;           // ID -> Note 映射
    QHash<QString, Category*> m_categories;
};
```

### 调用关系

```
NoteManager (单例)
    │
    ├── createNote() ──────► Note 对象
    │       │
    │       └── emit noteCreated(note)
    │               │
    │               └──► MainWindow::onNoteCreated()
    │
    ├── getNotesByCategory(categoryId)
    │       │
    │       └── 遍历 m_notes，筛选 categoryId 匹配的笔记
    │
    └── saveToFile()
            │
            ├── Note::toJson()
            └── QJsonDocument 写入文件
```

### C++ 语法要点

| 语法 | 示例 | 说明 |
|------|------|------|
| 静态成员变量 | `static NoteManager* s_instance` | 类级别共享 |
| 私有构造函数 | `private: NoteManager()` | 单例模式关键 |
| 范围 for 循环 | `for (Note *n : m_notes)` | C++11 遍历容器 |

### Qt 知识要点

| 知识点 | 说明 |
|--------|------|
| `QHash<K,V>` | 哈希表，O(1) 查找 |
| `QList<T>` | 动态数组 |
| `QJsonDocument` | JSON 文档处理 |
| `QStandardPaths` | 获取系统标准路径 |

---

## 5. 阶段四：自定义控件

### 5.1 SearchWidget（最简单的自定义控件）

**文件：widgets/SearchWidget.h**

```cpp
class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent = nullptr);

signals:
    void searchRequested(const QString &text);  // 搜索请求
    void searchCleared();                        // 清除搜索

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void onTextChanged(const QString &text);
    void onSearchTimeout();

private:
    QLineEdit *m_searchEdit;
    QPushButton *m_clearButton;
    QTimer *m_searchTimer;  // 延迟搜索
    int m_searchDelay;      // 延迟时间(ms)
};
```

**调用流程：**

```
用户输入
    │
    ▼
QLineEdit::textChanged
    │
    ▼
SearchWidget::onTextChanged()
    ├── 显示/隐藏清除按钮
    ├── 重启定时器
    │
    ▼ (300ms 后)
QTimer::timeout
    │
    ▼
SearchWidget::onSearchTimeout()
    │
    ▼
emit searchRequested(text)
    │
    ▼
MainWindow::onSearchRequested()
    │
    ▼
NoteManager::searchNotes()
```

### 5.2 NoteListWidget（列表控件）

**信号转发模式：**

```cpp
// 内部信号 → 外部信号
connect(m_listWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
    emit noteSelected(item->data(Qt::UserRole).toString());
});
```

**Qt::UserRole 存储自定义数据：**

```cpp
// 存储
item->setData(Qt::UserRole, note->id());

// 读取
QString noteId = item->data(Qt::UserRole).toString();
```

### 5.3 RichTextEditor（复杂控件）

**核心方法：**

```cpp
// 应用格式到选中文本
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

---

## 6. 阶段五：主窗口整合

### 文件：mainwindow/MainWindow.h

**核心成员变量：**

```cpp
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // 控件
    CategoryTree *m_categoryTree;
    NoteListWidget *m_noteList;
    RichTextEditor *m_editor;
    SearchWidget *m_searchWidget;

    // 停靠窗口
    QDockWidget *m_categoryDock;
    QDockWidget *m_noteListDock;

    // 状态
    Note *m_currentNote;
    QString m_currentCategoryId;
};
```

### 初始化流程

```
MainWindow 构造函数
    │
    ├── setupUi()
    │       ├── createMenuBar()
    │       ├── createToolBar()
    │       ├── createStatusBar()
    │       ├── createDockWidgets()
    │       └── createCentralWidget()
    │
    ├── connectSignals()
    │       └── 连接所有控件的信号槽
    │
    └── loadSettings()
            └── 恢复窗口状态
```

---

## 7. 调用关系图

### 7.1 整体架构

```
┌─────────────────────────────────────────────────────────────┐
│                      MainWindow                              │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────────────┐  │
│  │CategoryTree │  │NoteListWidget│  │   RichTextEditor    │  │
│  └──────┬──────┘  └──────┬──────┘  └──────────┬──────────┘  │
│         │                │                     │             │
│         ▼                ▼                     ▼             │
│  categorySelected  noteSelected          textChanged        │
│         │                │                     │             │
└─────────┼────────────────┼─────────────────────┼─────────────┘
          │                │                     │
          ▼                ▼                     ▼
┌─────────────────────────────────────────────────────────────┐
│                     NoteManager (单例)                       │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐       │
│  │ QHash<Note>  │  │QHash<Category>│  │ JSON 文件    │       │
│  └──────────────┘  └──────────────┘  └──────────────┘       │
└─────────────────────────────────────────────────────────────┘
```

### 7.2 分类选择流程

```
用户点击分类
       │
       ▼
CategoryTree::onItemClicked()
       │
       ▼
emit categorySelected(categoryId)
       │
       ▼
MainWindow::onCategorySelected(categoryId)
       │
       ├── m_currentCategoryId = categoryId
       │
       ├── NoteManager::getNotesByCategory(categoryId)
       │           │
       │           └── 返回 QList<Note*>
       │
       └── m_noteList->addNote(note)  // 逐个添加
```

### 7.3 笔记编辑流程

```
用户点击笔记
       │
       ▼
NoteListWidget::onItemClicked()
       │
       ▼
emit noteSelected(noteId)
       │
       ▼
MainWindow::onNoteSelected(noteId)
       │
       ├── 保存当前笔记（如有修改）
       │
       ├── NoteManager::getNote(noteId)
       │
       └── m_editor->setHtml(note->content())
```

### 7.4 保存流程

```
用户点击保存 / 自动保存
       │
       ▼
MainWindow::onSaveNote()
       │
       ├── m_currentNote->setContent(m_editor->toHtml())
       │
       ├── m_editor->setModified(false)
       │
       └── NoteManager::saveToFile()
               │
               ├── Note::toJson()  // 每个笔记
               ├── Category::toJson()  // 每个分类
               │
               └── QFile::write(QJsonDocument)
```

---

## 8. C++ 语法速查

### 8.1 类与继承

```cpp
// 公有继承
class Note : public QObject { };

// 构造函数初始化列表
Note::Note(QObject *parent)
    : QObject(parent)      // 调用父类构造
    , m_id("default")      // 初始化成员
    , m_isPinned(false)
{ }
```

### 8.2 指针与引用

```cpp
// 指针
Note *note = new Note();
note->setTitle("标题");

// 引用（避免拷贝）
void setTitle(const QString &title);

// 智能指针（Qt 中较少用，因为有父子关系）
std::unique_ptr<Note> note;
```

### 8.3 Lambda 表达式

```cpp
// 基本语法: [捕获](参数) { 函数体 }
connect(btn, &QPushButton::clicked, this, [this]() {
    QString id = currentNoteId();
    if (!id.isEmpty()) {
        emit deleteRequested(id);
    }
});

// 捕获说明
// [this]  - 捕获 this 指针
// [=]     - 值捕获所有外部变量
// [&]     - 引用捕获所有外部变量
// [a, &b] - a 值捕获，b 引用捕获
```

### 8.4 override 关键字

```cpp
// 明确表示重写父类虚函数
void closeEvent(QCloseEvent *event) override;
bool eventFilter(QObject *watched, QEvent *event) override;
```

### 8.5 static_cast 类型转换

```cpp
QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
int size = static_cast<int>(format.fontPointSize());
```

---

## 9. Qt 知识速查

### 9.1 信号槽连接

```cpp
// 新式语法（推荐）
connect(sender, &Sender::signal, receiver, &Receiver::slot);

// Lambda 连接
connect(sender, &Sender::signal, this, [this]() { });

// 断开连接
disconnect(sender, &Sender::signal, receiver, &Receiver::slot);
```

### 9.2 常用容器

```cpp
// QList - 动态数组
QList<Note*> notes;
notes.append(note);
for (Note *n : notes) { }

// QHash - 哈希表
QHash<QString, Note*> m_notes;
m_notes.insert(id, note);
Note *n = m_notes.value(id, nullptr);
```

### 9.3 布局管理

```cpp
// 垂直布局
QVBoxLayout *layout = new QVBoxLayout(this);
layout->addWidget(widget1);
layout->addWidget(widget2);

// 水平布局
QHBoxLayout *hLayout = new QHBoxLayout();

// 去除边距
layout->setContentsMargins(0, 0, 0, 0);
layout->setSpacing(0);
```

### 9.4 JSON 序列化

```cpp
// 写入
QJsonObject obj;
obj["id"] = m_id;
obj["title"] = m_title;
QJsonDocument doc(obj);
file.write(doc.toJson());

// 读取
QJsonDocument doc = QJsonDocument::fromJson(data);
QJsonObject obj = doc.object();
QString id = obj["id"].toString();
```

### 9.5 事件处理

```cpp
// 重写事件处理函数
void MainWindow::closeEvent(QCloseEvent *event) override {
    if (hasUnsavedChanges()) {
        event->ignore();  // 阻止关闭
    } else {
        event->accept();  // 允许关闭
    }
}

// 事件过滤器
bool SearchWidget::eventFilter(QObject *watched, QEvent *event) override {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        if (ke->key() == Qt::Key_Escape) {
            clearSearch();
            return true;  // 事件已处理
        }
    }
    return QWidget::eventFilter(watched, event);
}
```

### 9.6 定时器

```cpp
// 创建定时器
m_timer = new QTimer(this);
m_timer->setSingleShot(true);  // 单次触发

// 连接超时信号
connect(m_timer, &QTimer::timeout, this, &MyClass::onTimeout);

// 启动/停止
m_timer->start(300);  // 300ms
m_timer->stop();
```

### 9.7 QMainWindow 组件

```cpp
// 菜单栏
QMenu *menu = menuBar()->addMenu(tr("文件(&F)"));
QAction *action = new QAction(tr("新建(&N)"), this);
action->setShortcut(QKeySequence::New);
menu->addAction(action);

// 工具栏
QToolBar *toolbar = addToolBar(tr("主工具栏"));
toolbar->addAction(action);

// 停靠窗口
QDockWidget *dock = new QDockWidget(tr("分类"), this);
dock->setWidget(m_categoryTree);
addDockWidget(Qt::LeftDockWidgetArea, dock);

// 垂直分割两个 Dock
splitDockWidget(dock1, dock2, Qt::Vertical);
```

---

## 10. 学习建议

### 10.1 阅读顺序

1. **先看头文件** (.h) - 了解类的接口
2. **再看实现** (.cpp) - 理解具体逻辑
3. **跟踪信号槽** - 理解组件间通信

### 10.2 调试技巧

```cpp
// 打印调试信息
qDebug() << "noteId:" << noteId;
qDebug() << "count:" << m_notes.count();
```

### 10.3 常见问题

| 问题 | 原因 | 解决 |
|------|------|------|
| 信号槽不触发 | 忘记 Q_OBJECT | 添加宏并重新 qmake |
| 内存泄漏 | 未设置 parent | 传入父对象指针 |
| 界面不更新 | 未调用 update | 手动刷新或用信号 |


