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
| 富文本编辑 | 字体、颜色、格式、对齐方式 |
| 搜索功能 | 延迟搜索，支持标题和内容搜索 |
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

### 3.3 MainWindow 类（主窗口）

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

#### 4.2.6 富文本编辑

```cpp
// 应用格式到选中文本
void RichTextEditor::mergeFormatOnWordOrSelection(const QTextCharFormat &format) {
    QTextCursor cursor = m_textEdit->textCursor();
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
}
```

#### 4.2.7 延迟搜索 (QTimer)

```cpp
// 用户输入后延迟触发搜索，避免频繁查询
void SearchWidget::onTextChanged(const QString &text) {
    m_searchTimer->stop();
    if (!text.isEmpty()) {
        m_searchTimer->start(m_searchDelay);  // 300ms 延迟
    }
}
```

---

## 5. 编译与运行

### 5.1 环境要求

- Qt 5.14.2 或更高版本
- CMake 3.10+
- MinGW 32位编译器（与 Qt 版本匹配）

### 5.2 编译步骤

```bash
cd NotepadPro

# 配置（使用 Qt 自带的 MinGW）
cmake -B build -G "MinGW Makefiles" \
  -DCMAKE_CXX_COMPILER="<Qt路径>/Tools/mingw730_32/bin/g++.exe"

# 编译
cmake --build build
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

1. **元对象系统** - Q_OBJECT、Q_PROPERTY
2. **信号槽机制** - 新式语法、Lambda 连接
3. **主窗口架构** - 菜单、工具栏、停靠窗口
4. **数据持久化** - JSON 序列化、QSettings
5. **自定义控件** - 继承、事件处理
6. **对话框** - 模态对话框、标准对话框

通过学习本项目，可以掌握 Qt 应用开发的完整流程。
