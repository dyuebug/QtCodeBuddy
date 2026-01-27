# Qt6 纯代码学习教程

## 简介

这是一个系统的 Qt6 纯代码学习教程，包含 8 个章节，每个章节都有完整的代码示例和详细的中文注释。本教程采用 CMake 构建系统，所有示例均为纯代码实现（不使用 Qt Designer）。

## 教程结构

本教程包含以下 8 个章节：

### 第1章：Qt6基础入门
- **目标**：学习 Qt6 的基本概念和程序结构
- **内容**：
  - QApplication 应用程序类
  - QWidget 窗口基类
  - 基本部件（QLabel, QPushButton）
  - 布局管理器（QVBoxLayout）
  - 信号和槽机制的基本使用
- **主要文件**：
  - `HelloWorld.h/cpp` - Hello World 窗口类
  - `main.cpp` - 程序入口

### 第2章：窗口和部件
- **目标**：掌握各种常用窗口部件的使用
- **内容**：
  - 按钮部件（QPushButton, QCheckBox, QRadioButton）
  - 输入部件（QLineEdit, QTextEdit, QSpinBox, QComboBox, QSlider）
  - 显示部件（QLabel, QProgressBar, QLCDNumber）
  - 容器部件（QGroupBox, QTabWidget）
  - 窗口属性设置
  - 模态和非模态窗口
- **主要文件**：
  - `WidgetsDemo.h/cpp` - 部件演示类

### 第3章：布局管理
- **目标**：掌握 Qt6 的各种布局管理器
- **内容**：
  - QVBoxLayout（垂直布局）
  - QHBoxLayout（水平布局）
  - QGridLayout（网格布局）
  - QFormLayout（表单布局）
  - 布局的嵌套使用
  - 拉伸因子（Stretch Factor）
  - 动态添加和移除部件
- **主要文件**：
  - `LayoutDemo.h/cpp` - 布局演示类

### 第4章：信号和槽
- **目标**：深入理解 Qt6 的信号和槽机制
- **内容**：
  - 信号和槽的基本概念
  - Qt6 的 connect 语法（函数指针）
  - 自定义信号和槽
  - 参数传递
  - Lambda 表达式作为槽
  - 多重连接
  - 断开连接
- **主要文件**：
  - `SignalsSlotsDemo.h/cpp` - 信号槽演示类
  - `Counter.h/cpp` - 自定义计数器类

### 第5章：事件处理
- **目标**：掌握 Qt6 的事件处理机制
- **内容**：
  - 事件系统概述
  - 鼠标事件（mousePressEvent, mouseMoveEvent 等）
  - 键盘事件（keyPressEvent, keyReleaseEvent）
  - 焦点事件（focusInEvent, focusOutEvent）
  - 窗口事件（resizeEvent, moveEvent, closeEvent）
  - 绘制事件（paintEvent）
  - 定时器事件（timerEvent）
  - 事件过滤器
- **主要文件**：
  - `EventDemo.h/cpp` - 事件演示类
  - `ClickLabel.h/cpp` - 可点击标签
  - `MouseTracker.h/cpp` - 鼠标跟踪器

### 第6章：对话框
- **目标**：掌握各种对话框的使用
- **内容**：
  - QMessageBox（消息对话框）
  - QFileDialog（文件对话框）
  - QColorDialog（颜色对话框）
  - QFontDialog（字体对话框）
  - QInputDialog（输入对话框）
  - QProgressDialog（进度对话框）
  - 自定义对话框
  - 对话框的模态性
- **主要文件**：
  - `DialogDemo.h/cpp` - 对话框演示类
  - `CustomDialog.h/cpp` - 自定义对话框

### 第7章：主窗口
- **目标**：掌握 QMainWindow 主窗口架构
- **内容**：
  - QMainWindow 架构概述
  - 菜单栏（QMenuBar）
  - 工具栏（QToolBar）
  - 状态栏（QStatusBar）
  - 中心部件（Central Widget）
  - 停靠窗口（QDockWidget）
  - 上下文菜单
  - 完整的文本编辑器示例
- **主要文件**：
  - `MainWindowDemo.h/cpp` - 主窗口演示类
  - `TextEditWidget.h/cpp` - 文本编辑部件

### 第8章：自定义部件
- **目标**：学习如何创建自定义部件
- **内容**：
  - 自定义部件的基本概念
  - 重写 paintEvent() 进行自定义绘制
  - 重写事件处理函数
  - 自定义属性（Q_PROPERTY）
  - 自定义信号和槽
  - 动画效果的实现
  - 在 Qt Designer 中使用自定义部件
- **主要文件**：
  - `CustomWidgetDemo.h/cpp` - 自定义部件演示类
  - `ColorPickerWidget.h/cpp` - 颜色选择器
  - `CircularProgressBar.h/cpp` - 圆形进度条

## 构建和运行

### 前提条件

- CMake 3.16 或更高版本
- Qt6 开发库
- C++17 编译器

### 构建步骤

每个章节都是独立的 CMake 项目，可以单独构建和运行。

#### 使用 CMake GUI（推荐 Windows）

1. 打开 CMake GUI
2. 设置源代码路径：选择对应章节的目录（如 `Chapter01_Basic`）
3. 设置构建路径：建议在源代码目录下创建 `build` 文件夹
4. 点击 "Configure" 按钮
5. 选择你的编译器（如 Visual Studio, MinGW）
6. 确保 Qt6 路径正确配置
7. 点击 "Generate" 按钮
8. 点击 "Open Project" 按钮，使用 IDE 打开项目
9. 编译并运行

#### 使用命令行

```bash
# 进入章节目录
cd Chapter01_Basic

# 创建构建目录
mkdir build
cd build

# 配置
cmake ..

# 编译（Linux/macOS）
make

# 或编译（Windows - Visual Studio）
cmake --build . --config Release

# 运行
./Chapter01_Basic  # Linux/macOS
Chapter01_Basic.exe  # Windows
```

### CLion/VS Code 集成

如果使用 CLion 或 VS Code，可以直接打开章节目录，CMake 会自动配置项目。

## 学习方法

建议按照章节顺序学习，每个章节都建立在前面的基础之上。

### 学习步骤：

1. **阅读代码**：仔细阅读每个文件中的注释，理解代码逻辑
2. **修改实验**：尝试修改代码，观察效果变化
3. **扩展功能**：在示例基础上添加新功能
4. **应用到项目**：将学到的知识应用到自己的项目中

### 代码特点：

- **详细注释**：每个重要代码行都有中文注释
- **渐进学习**：从简单到复杂，循序渐进
- **实用示例**：所有示例都具有实际应用价值
- **现代 C++**：使用 C++17 标准和现代编程实践
- **纯代码实现**：所有界面都是纯代码编写，不使用 UI 文件

## 章节详解

### 第1章：Qt6基础入门

这是最简单的入门示例，展示了 Qt6 程序的基本结构：

```cpp
// 创建应用程序对象
QApplication app(argc, argv);

// 创建窗口
HelloWorld window;

// 显示窗口
window.show();

// 进入事件循环
return app.exec();
```

重点理解：
- QApplication 的作用
- QWidget 和窗口的关系
- 信号和槽的基本连接
- 布局管理器的使用

### 第2章：窗口和部件

这一章介绍了 Qt6 中常用的各种部件，通过实际示例演示了每个部件的用法。特别要注意：

- 不同部件的信号
- 部件的属性设置
- 部件之间的交互
- 窗口的模态性

### 第3章：布局管理

布局管理是创建美观界面的关键。本章详细介绍了：

- 各种布局管理器的特点
- 布局的嵌套使用
- 拉伸因子的作用
- 动态管理布局

### 第4章：信号和槽

信号和槽是 Qt 的核心机制。本章深入讲解了：

- Qt6 推荐的 connect 语法
- 自定义信号和槽
- Lambda 表达式的使用
- 多重连接

### 第5章：事件处理

事件处理是底层交互的基础。本章涵盖了：

- 各种事件的处理函数
- 事件过滤器
- 事件和信号的区别
- 自定义绘制

### 第6章：对话框

对话框是用户交互的重要方式。本章介绍了：

- 标准对话框的使用
- 自定义对话框的创建
- 对话框的返回值处理
- 模态和非模态对话框

### 第7章：主窗口

主窗口是复杂应用的基础。本章通过完整的文本编辑器示例演示了：

- QMainWindow 的完整架构
- 菜单栏、工具栏、状态栏的使用
- 停靠窗口的创建和管理
- 完整的文件操作流程

### 第8章：自定义部件

创建自定义部件是高级 Qt 开发的重要技能。本章展示了：

- 自定义绘制
- 自定义属性
- 动画效果
- 完整的自定义部件开发流程

## 常见问题

### 1. CMake 找不到 Qt6

确保 Qt6 已正确安装，并设置以下环境变量：

- Windows: `QT_ROOT` 或 `CMAKE_PREFIX_PATH` 指向 Qt 安装目录
- Linux: 使用包管理器安装 qt6-base-dev
- macOS: `brew install qt6`

### 2. 编译错误

确保：
- CMake 版本 >= 3.16
- C++17 编译器
- Qt6 版本 >= 6.0

### 3. 运行时错误

确保：
- Qt6 的 bin 目录在 PATH 环境变量中
- 或者将所需的 Qt 库复制到可执行文件目录

## 扩展学习

完成本教程后，可以进一步学习：

1. **Qt Quick/QML**：现代化的 UI 开发方式
2. **多线程编程**：QThread 的使用
3. **网络编程**：QTcpSocket, QUdpSocket
4. **数据库编程**：QtSQL 模块
5. **图形视图框架**：QGraphicsView
6. **OpenGL 集成**：QtOpenGL 模块

## 许可证

本教程代码采用 MIT 许可证，可以自由使用和学习。

## 贡献

欢迎提交 Issue 和 Pull Request，帮助改进本教程。

## 联系方式

如有问题或建议，请通过以下方式联系：

- 提交 GitHub Issue
- 发送邮件到：your-email@example.com

## 致谢

感谢 Qt 框架的开发者们提供了如此优秀的跨平台开发工具。

---

**Happy Coding!** 🚀
