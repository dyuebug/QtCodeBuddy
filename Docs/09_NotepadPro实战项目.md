# 第9章：NotepadPro 实战项目

## 一、项目概述

### 1.1 项目简介

NotepadPro 是一个基于 Qt6 的个人笔记本应用，整合了前8章所有知识点。

### 1.2 核心功能

| 功能 | 说明 |
|------|------|
| 笔记管理 | 创建、编辑、删除笔记 |
| 分类管理 | 分类创建、颜色标记 |
| 富文本编辑 | 粗体、斜体、颜色等 |
| 搜索功能 | 标题和内容搜索 |
| 数据持久化 | JSON 文件存储 |

---

## 二、项目架构

```
NotepadPro/
├── core/           # 数据层
│   ├── Note.h/cpp
│   ├── Category.h/cpp
│   └── NoteManager.h/cpp
├── widgets/        # 控件层
│   ├── NoteListWidget
│   ├── RichTextEditor
│   └── CategoryTree
├── dialogs/        # 对话框层
└── mainwindow/     # 主窗口层
```

---

## 三、知识点对应

| 章节 | 在项目中的应用 |
|------|----------------|
| 第1章 | main.cpp 程序入口 |
| 第2章 | 各种控件使用 |
| 第3章 | 界面布局设计 |
| 第4章 | 组件间通信 |
| 第5章 | 关闭事件处理 |
| 第6章 | 属性对话框 |
| 第7章 | 主窗口架构 |
| 第8章 | 富文本编辑器 |

---

## 四、核心类说明

### 4.1 NoteManager - 数据管理器

单例模式，负责笔记和分类的增删改查。

```cpp
// 获取实例
NoteManager::instance()->createNote("新笔记");

// 创建分类
NoteManager::instance()->createCategory("工作", Qt::blue);

// 保存数据
NoteManager::instance()->saveToFile("notes.json");
```

### 4.2 Note - 笔记类

```cpp
class Note {
    QString m_id;           // 唯一标识
    QString m_title;        // 标题
    QString m_content;      // 内容
    QString m_categoryId;   // 分类ID
    QDateTime m_createdAt;  // 创建时间
    QDateTime m_updatedAt;  // 更新时间
};
```

### 4.3 MainWindow - 主窗口

整合所有组件，处理用户交互。

---

## 五、设计模式应用

### 5.1 单例模式

```cpp
class NoteManager : public QObject
{
public:
    static NoteManager* instance();

private:
    NoteManager(QObject *parent = nullptr);
    static NoteManager* m_instance;
};
```

### 5.2 信号槽解耦

```cpp
// 笔记列表选中变化 -> 编辑器加载内容
connect(m_noteList, &NoteListWidget::noteSelected,
        m_editor, &RichTextEditor::loadNote);
```

---

## 六、运行项目

```bash
cd NotepadPro
mkdir build && cd build
cmake ..
cmake --build .
./NotepadPro
```

---

## 七、本章小结

| 技术点 | 应用场景 |
|--------|----------|
| 单例模式 | NoteManager 数据管理 |
| JSON 序列化 | 数据持久化 |
| 信号槽 | 组件间通信 |
| QMainWindow | 主窗口架构 |
| 富文本编辑 | 笔记内容编辑 |
