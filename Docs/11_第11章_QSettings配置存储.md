# 第11章：QSettings 配置存储

## 一、本章概述

### 1.1 学习目标

- 掌握 QSettings 基本用法
- 学会保存和读取各种数据类型
- 理解分组管理配置
- 掌握窗口状态保存和恢复

### 1.2 核心知识点

| 知识点 | 重要程度 | 说明 |
|--------|----------|------|
| QSettings | ★★★★★ | 配置存储 |
| 分组管理 | ★★★★☆ | beginGroup/endGroup |
| 窗口状态 | ★★★☆☆ | saveGeometry/restoreGeometry |

---

## 二、QSettings 基本用法

### 2.1 创建 QSettings

```cpp
// 方式1：使用组织名和应用名
QSettings settings("MyCompany", "MyApp");

// 方式2：使用 INI 文件
QSettings settings("config.ini", QSettings::IniFormat);
```

### 2.2 读写数据

```cpp
// 写入
settings.setValue("username", "张三");
settings.setValue("age", 25);

// 读取（带默认值）
QString name = settings.value("username", "").toString();
int age = settings.value("age", 0).toInt();
```

---

## 三、分组管理

```cpp
QSettings settings("MyCompany", "MyApp");

// 使用分组
settings.beginGroup("User");
settings.setValue("name", "张三");
settings.setValue("age", 25);
settings.endGroup();

settings.beginGroup("UI");
settings.setValue("theme", "dark");
settings.endGroup();
```

---

## 四、窗口状态保存

```cpp
// 保存窗口状态
void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("MyCompany", "MyApp");
    settings.setValue("geometry", saveGeometry());
    event->accept();
}

// 恢复窗口状态
void MainWindow::loadSettings()
{
    QSettings settings("MyCompany", "MyApp");
    if (settings.contains("geometry")) {
        restoreGeometry(settings.value("geometry").toByteArray());
    }
}
```

---

## 五、本章小结

| 方法 | 用途 |
|------|------|
| setValue() | 保存配置 |
| value() | 读取配置 |
| beginGroup() | 开始分组 |
| endGroup() | 结束分组 |
| clear() | 清除所有配置 |
