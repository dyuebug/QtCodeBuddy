# NotepadPro 项目设计文档

## 1. 项目概述

NotepadPro 是一个基于 Qt6 的个人笔记本应用，旨在将 Qt6 的核心知识点整合到一个实际项目中，形成完整的学习体验。

### 1.1 项目目标

- **知识整合**：将 Qt6 的 8 个核心章节知识融合到实际项目
- **渐进学习**：按模块划分，每个模块对应特定知识点
- **实用性强**：完成后是一个可日常使用的笔记应用
- **代码规范**：遵循统一的代码风格和注释规范

### 1.2 核心功能

| 功能 | 描述 |
|------|------|
| 笔记管理 | 创建、编辑、删除、重命名笔记 |
| 分类管理 | 创建、编辑、删除分类，支持颜色标记 |
| 分类-笔记关联 | 笔记归属分类，按分类筛选笔记 |
| 富文本编辑 | 粗体、斜体、下划线、删除线、颜色、对齐 |
| 搜索功能 | 延迟搜索（防抖动），支持标题和内容搜索 |
| 数据持久化 | JSON 文件存储，自动保存 |

---

## 2. 架构设计

### 2.1 分层架构

```
┌─────────────────────────────────────────────────┐
│                  主窗口层 (mainwindow/)          │
│         MainWindow - 整合所有组件               │
├─────────────────────────────────────────────────┤
│                  对话框层 (dialogs/)             │
│   NotePropertiesDialog | CategoryDialog         │
│   SettingsDialog | AboutDialog                  │
├─────────────────────────────────────────────────┤
│                  控件层 (widgets/)               │
│   NoteListWidget | RichTextEditor               │
│   CategoryTree | SearchWidget | StatusWidget    │
├─────────────────────────────────────────────────┤
│                  核心数据层 (core/)              │
│   Note | Category | NoteManager                 │
└─────────────────────────────────────────────────┘
```

### 2.2 目录结构

```
NotepadPro/
├── CMakeLists.txt          # CMake 构建配置
├── main.cpp                # 程序入口
├── DESIGN.md               # 本设计文档
│
├── core/                   # 核心数据层
│   ├── Note.h/cpp         # 笔记数据模型
│   ├── Category.h/cpp     # 分类数据模型
│   └── NoteManager.h/cpp  # 数据管理器（单例）
│
├── widgets/                # 自定义控件层
│   ├── NoteListWidget.h/cpp    # 笔记列表
│   ├── RichTextEditor.h/cpp    # 富文本编辑器
│   ├── CategoryTree.h/cpp      # 分类树
│   ├── SearchWidget.h/cpp      # 搜索控件
│   └── StatusWidget.h/cpp      # 状态栏控件
│
├── dialogs/                # 对话框层
│   ├── NotePropertiesDialog.h/cpp  # 笔记属性
│   ├── CategoryDialog.h/cpp        # 分类编辑
│   ├── SettingsDialog.h/cpp        # 设置
│   └── AboutDialog.h/cpp           # 关于
│
├── mainwindow/             # 主窗口层
│   └── MainWindow.h/cpp    # 主窗口
│
└── resources/              # 资源文件
    └── icons.qrc           # 图标资源
```

---

## 3. 核心类设计

### 3.1 Note 类（笔记数据模型）

```cpp
class Note : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    // ... 其他属性
};
```

**设计要点：**
- 继承 `QObject` 以支持信号槽机制
- 使用 `Q_PROPERTY` 宏声明属性，支持属性绑定
- 提供 `toJson()` / `fromJson()` 实现序列化

### 3.2 NoteManager 类（数据管理器）

**设计模式：单例模式**

```cpp
class NoteManager : public QObject
{
public:
    static NoteManager* instance();  // 获取单例

    // 笔记 CRUD
    Note* createNote(const QString &title);
    Note* getNote(const QString &id) const;
    bool deleteNote(const QString &id);

    // 持久化
    bool saveToFile(const QString &path);
    bool loadFromFile(const QString &path);
};
```

### 3.3 分类-笔记关联机制

**设计思路：**
- 每个笔记通过 `categoryId` 字段关联到分类
- 分类树提供"全部笔记"选项（空 ID）显示所有笔记
- 选择分类时自动过滤笔记列表

```cpp
// MainWindow::onCategorySelected - 分类选择处理
void MainWindow::onCategorySelected(const QString &categoryId)
{
    m_currentCategoryId = categoryId;
    m_noteList->clear();

    QList<Note*> notes;
    if (categoryId.isEmpty()) {
        // "全部笔记" - 显示所有
        notes = NoteManager::instance()->getAllNotes();
    } else {
        // 按分类过滤
        notes = NoteManager::instance()->getNotesByCategory(categoryId);
    }

    for (Note *note : notes) {
        m_noteList->addNote(note);
    }
}
```

### 3.4 MainWindow 类（主窗口）

**QMainWindow 架构组成：**

```
┌────────────────────────────────────────┐
│              菜单栏 (MenuBar)           │
├────────────────────────────────────────┤
│              工具栏 (ToolBar)           │
├──────────┬─────────────────────────────┤
│ 分类树   │                             │
│ (Dock)   │      富文本编辑器            │
├──────────┤      (CentralWidget)        │
│ 笔记列表 │                             │
│ (Dock)   │                             │
├──────────┴─────────────────────────────┤
│              状态栏 (StatusBar)         │
└────────────────────────────────────────┘
```

---

## 4. Qt6 知识点映射

### 4.1 知识点总览

| 模块 | 涵盖知识点 | 对应章节 |
|------|-----------|---------|
| main.cpp | QApplication、程序入口 | Chapter01 |
| core/ | Q_OBJECT、Q_PROPERTY、信号槽 | Chapter04 |
| widgets/ | 自定义控件、事件处理 | Chapter02, 05, 08 |
| dialogs/ | QDialog、标准对话框 | Chapter06 |
| mainwindow/ | QMainWindow、菜单、工具栏、布局 | Chapter03, 07 |

### 4.2 详细知识点说明

#### 4.2.1 元对象系统 (Meta-Object System)

**Q_OBJECT 宏**
```cpp
class Note : public QObject
{
    Q_OBJECT  // 启用元对象系统
    // ...
};
```
- 必须放在类声明的私有区域
- 启用信号槽、属性系统、运行时类型信息

**Q_PROPERTY 属性系统**
```cpp
Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
```
- READ: 读取函数
- WRITE: 写入函数
- NOTIFY: 属性变化时发出的信号

#### 4.2.2 信号槽机制

**新式连接语法（推荐）**
```cpp
connect(m_noteList, &NoteListWidget::noteSelected,
        this, &MainWindow::onNoteSelected);
```

**Lambda 表达式连接**
```cpp
connect(m_deleteAction, &QAction::triggered, this, [this]() {
    QString noteId = currentNoteId();
    if (!noteId.isEmpty()) {
        emit deleteNoteRequested(noteId);
    }
});
```

#### 4.2.3 QMainWindow 架构

**停靠窗口 (QDockWidget)**
```cpp
// 创建停靠窗口
m_categoryDock = new QDockWidget(tr("分类"), this);
m_categoryDock->setWidget(m_categoryTree);
addDockWidget(Qt::LeftDockWidgetArea, m_categoryDock);

// 垂直分割两个 Dock，避免重叠
splitDockWidget(m_categoryDock, m_noteListDock, Qt::Vertical);
```

#### 4.2.4 JSON 数据持久化

```cpp
// 序列化
QJsonObject Note::toJson() const {
    QJsonObject obj;
    obj["id"] = m_id;
    obj["title"] = m_title;
    return obj;
}

// 反序列化
Note* Note::fromJson(const QJsonObject &json) {
    Note *note = new Note();
    note->m_id = json["id"].toString();
    note->m_title = json["title"].toString();
    return note;
}
```

#### 4.2.5 QSettings 配置存储

```cpp
// 保存窗口状态
void MainWindow::saveSettings() {
    QSettings settings;
    settings.setValue("mainWindow/geometry", saveGeometry());
    settings.setValue("mainWindow/state", saveState());
}

// 恢复窗口状态
void MainWindow::loadSettings() {
    QSettings settings;
    restoreGeometry(settings.value("mainWindow/geometry").toByteArray());
    restoreState(settings.value("mainWindow/state").toByteArray());
}
```

#### 4.2.6 富文本编辑器工具栏

**问题与解决方案：**
- QToolBar 会被 QMainWindow 自动吸收到主工具栏区域
- 解决：使用 QWidget + QHBoxLayout + QPushButton 替代 QToolBar

```cpp
// 创建工具栏容器（使用 QWidget 而非 QToolBar）
m_toolBarWidget = new QWidget(this);
m_toolBarLayout = new QHBoxLayout(m_toolBarWidget);

// 格式按钮 - 点击触发 Action
m_boldBtn = new QPushButton(tr("B"), m_toolBarWidget);
m_boldBtn->setCheckable(true);
connect(m_boldBtn, &QPushButton::clicked, m_boldAction, &QAction::trigger);
```

**按钮状态同步：**
```cpp
// 光标位置变化时同步按钮选中状态
void RichTextEditor::onCurrentCharFormatChanged(const QTextCharFormat &format)
{
    m_boldBtn->blockSignals(true);  // 防止循环触发
    m_boldBtn->setChecked(format.fontWeight() == QFont::Bold);
    m_boldBtn->blockSignals(false);
}
```

#### 4.2.7 文本格式应用

```cpp
// 应用格式到选中文本或当前单词
void RichTextEditor::mergeFormatOnWordOrSelection(const QTextCharFormat &format) {
    QTextCursor cursor = m_textEdit->textCursor();
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    m_textEdit->mergeCurrentCharFormat(format);
}
```

#### 4.2.8 延迟搜索 (QTimer)

```cpp
// 用户输入后延迟触发搜索，避免频繁查询（防抖动）
void SearchWidget::onTextChanged(const QString &text) {
    m_searchTimer->stop();
    if (!text.isEmpty()) {
        m_searchTimer->start(m_searchDelay);  // 300ms 延迟
    }
}
```

#### 4.2.9 事件过滤器 (eventFilter)

```cpp
// 拦截子控件的键盘事件
bool SearchWidget::eventFilter(QObject *watched, QEvent *event) {
    if (watched == m_searchEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Escape) {
            clearSearch();  // Escape 清除搜索
            return true;
        }
        if (keyEvent->key() == Qt::Key_Return) {
            emit searchRequested(m_searchEdit->text());  // Enter 立即搜索
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}
```

---

## 5. 编译与运行

### 5.1 环境要求

- Qt 6.x（推荐 Qt 6.5+）
- CMake 3.16+
- MinGW 64位 或 MSVC 编译器

### 5.2 编译步骤

```bash
cd NotepadPro

# 配置
cmake -B build -G "MinGW Makefiles"

# 编译
cmake --build build --config Debug
```

### 5.3 运行

```bash
./build/NotepadPro.exe
```

---

## 6. 代码规范

### 6.1 命名规范

| 类型 | 规范 | 示例 |
|------|------|------|
| 成员变量 | m_camelCase | m_noteList |
| 槽函数 | onActionName | onNoteSelected |
| 信号 | actionRequested | createNoteRequested |
| 类名 | PascalCase | NoteListWidget |

### 6.2 注释规范

使用 Doxygen 格式的中文注释：

```cpp
/**
 * @brief 函数简要说明
 * @param paramName 参数说明
 * @return 返回值说明
 */
```

### 6.3 代码组织模式

```cpp
// 构造函数标准模式
ClassName::ClassName(QWidget *parent)
    : QWidget(parent)
{
    setupUi();        // 1. 创建界面
    connectSignals(); // 2. 连接信号
}
```

---

## 7. 总结

本项目通过实现一个完整的笔记本应用，系统性地展示了 Qt6 的核心知识点：

1. **元对象系统** - Q_OBJECT、Q_PROPERTY、信号槽
2. **信号槽机制** - 新式语法、Lambda 连接、信号转发
3. **主窗口架构** - 菜单、工具栏、停靠窗口、splitDockWidget
4. **数据持久化** - JSON 序列化、QSettings 配置存储
5. **自定义控件** - QWidget 组合、事件过滤器
6. **对话框** - 模态对话框、QInputDialog
7. **富文本编辑** - QTextEdit、QTextCharFormat、QTextCursor
8. **定时器应用** - QTimer 实现防抖动搜索

通过学习本项目，可以掌握 Qt6 应用开发的完整流程。
