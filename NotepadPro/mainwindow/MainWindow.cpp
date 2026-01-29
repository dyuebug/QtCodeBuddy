/**
 * @file MainWindow.cpp
 * @brief 主窗口实现
 *
 * 本文件实现了 NotepadPro 应用的主窗口，包括：
 * - 菜单栏、工具栏、状态栏的创建
 * - 停靠窗口（分类树、笔记列表）的管理
 * - 笔记的增删改查操作
 * - 分类的管理
 * - 搜索功能
 * - 自动保存功能
 *
 * 知识点：
 * - QMainWindow 架构（菜单、工具栏、状态栏、停靠窗口、中央控件）
 * - QDockWidget 停靠窗口的使用和布局
 * - QSettings 保存/恢复窗口状态
 * - 信号槽机制连接各组件
 */

#include "MainWindow.h"
#include "NoteListWidget.h"
#include "RichTextEditor.h"
#include "CategoryTree.h"
#include "SearchWidget.h"
#include "StatusWidget.h"
#include "Note.h"
#include "Category.h"
#include "NoteManager.h"
#include "NotePropertiesDialog.h"
#include "CategoryDialog.h"
#include "SettingsDialog.h"
#include "AboutDialog.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QSettings>
#include <QRegularExpression>
#include <QInputDialog>

/**
 * @brief 构造函数
 * @param parent 父窗口指针
 *
 * 初始化主窗口，设置界面、连接信号、加载数据
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_currentNote(nullptr)
{
    setWindowTitle(tr("NotepadPro"));
    setMinimumSize(800, 600);

    // 1. 创建界面元素
    setupUi();
    // 2. 连接信号槽
    connectSignals();
    // 3. 加载窗口设置
    loadSettings();

    // 4. 加载数据并刷新界面
    NoteManager::instance()->loadFromFile();
    m_categoryTree->refreshTree();
    m_noteList->refreshList();
    updateStatusBar();
}

/**
 * @brief 析构函数
 *
 * 保存窗口设置后销毁
 */
MainWindow::~MainWindow()
{
    saveSettings();
}

/**
 * @brief 初始化界面
 *
 * 按顺序创建：菜单栏 -> 工具栏 -> 状态栏 -> 停靠窗口 -> 中央控件
 */
void MainWindow::setupUi()
{
    createMenuBar();
    createToolBar();
    createStatusBar();
    createDockWidgets();
    createCentralWidget();

    // 自动保存定时器
    m_autoSaveTimer = new QTimer(this);
    m_autoSaveTimer->setInterval(5 * 60 * 1000); // 5分钟
}

/**
 * @brief 创建菜单栏
 *
 * 创建文件、编辑、视图、帮助四个菜单
 * 每个菜单项都设置了快捷键和助记符(&)
 */
void MainWindow::createMenuBar()
{
    // 文件菜单
    m_fileMenu = menuBar()->addMenu(tr("文件(&F)"));

    m_newNoteAction = new QAction(tr("新建笔记(&N)"), this);
    m_newNoteAction->setShortcut(QKeySequence::New);
    m_fileMenu->addAction(m_newNoteAction);

    m_saveNoteAction = new QAction(tr("保存(&S)"), this);
    m_saveNoteAction->setShortcut(QKeySequence::Save);
    m_fileMenu->addAction(m_saveNoteAction);

    m_deleteNoteAction = new QAction(tr("删除笔记(&D)"), this);
    m_deleteNoteAction->setShortcut(QKeySequence::Delete);
    m_fileMenu->addAction(m_deleteNoteAction);

    m_fileMenu->addSeparator();

    m_settingsAction = new QAction(tr("设置(&P)..."), this);
    m_fileMenu->addAction(m_settingsAction);

    m_fileMenu->addSeparator();

    m_exitAction = new QAction(tr("退出(&X)"), this);
    m_exitAction->setShortcut(QKeySequence::Quit);
    m_fileMenu->addAction(m_exitAction);

    // 编辑菜单 - 添加常用编辑操作
    m_editMenu = menuBar()->addMenu(tr("编辑(&E)"));

    m_undoAction = new QAction(tr("撤销(&U)"), this);
    m_undoAction->setShortcut(QKeySequence::Undo);
    m_editMenu->addAction(m_undoAction);

    m_redoAction = new QAction(tr("重做(&R)"), this);
    m_redoAction->setShortcut(QKeySequence::Redo);
    m_editMenu->addAction(m_redoAction);

    m_editMenu->addSeparator();

    m_cutAction = new QAction(tr("剪切(&T)"), this);
    m_cutAction->setShortcut(QKeySequence::Cut);
    m_editMenu->addAction(m_cutAction);

    m_copyAction = new QAction(tr("复制(&C)"), this);
    m_copyAction->setShortcut(QKeySequence::Copy);
    m_editMenu->addAction(m_copyAction);

    m_pasteAction = new QAction(tr("粘贴(&P)"), this);
    m_pasteAction->setShortcut(QKeySequence::Paste);
    m_editMenu->addAction(m_pasteAction);

    m_editMenu->addSeparator();

    m_selectAllAction = new QAction(tr("全选(&A)"), this);
    m_selectAllAction->setShortcut(QKeySequence::SelectAll);
    m_editMenu->addAction(m_selectAllAction);

    // 视图菜单
    m_viewMenu = menuBar()->addMenu(tr("视图(&V)"));

    // 帮助菜单
    m_helpMenu = menuBar()->addMenu(tr("帮助(&H)"));

    m_aboutAction = new QAction(tr("关于(&A)..."), this);
    m_helpMenu->addAction(m_aboutAction);
}

/**
 * @brief 创建工具栏
 *
 * 工具栏包含常用操作按钮和搜索框
 * 设置 ToolButtonTextBesideIcon 样式让按钮同时显示图标和文字
 */
void MainWindow::createToolBar()
{
    m_mainToolBar = addToolBar(tr("主工具栏"));
    m_mainToolBar->setMovable(false);
    // 设置工具栏按钮样式：显示文字（因为没有图标资源）
    m_mainToolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);

    m_mainToolBar->addAction(m_newNoteAction);
    m_mainToolBar->addAction(m_saveNoteAction);
    m_mainToolBar->addAction(m_deleteNoteAction);
    m_mainToolBar->addSeparator();

    // 搜索控件 - 添加到工具栏右侧
    m_searchWidget = new SearchWidget(this);
    m_searchWidget->setMinimumWidth(200);
    m_mainToolBar->addWidget(m_searchWidget);
}

void MainWindow::createStatusBar()
{
    m_statusWidget = new StatusWidget(this);
    statusBar()->addPermanentWidget(m_statusWidget, 1);
}

/**
 * @brief 创建停靠窗口
 *
 * 创建分类树和笔记列表两个停靠窗口
 * 使用 splitDockWidget 让它们垂直排列，避免重叠
 */
void MainWindow::createDockWidgets()
{
    // 分类停靠窗口 - 显示分类树
    m_categoryDock = new QDockWidget(tr("分类"), this);
    m_categoryDock->setFeatures(QDockWidget::DockWidgetClosable |
                                 QDockWidget::DockWidgetMovable);
    m_categoryTree = new CategoryTree(m_categoryDock);
    m_categoryDock->setWidget(m_categoryTree);
    addDockWidget(Qt::LeftDockWidgetArea, m_categoryDock);

    // 笔记列表停靠窗口 - 显示当前分类下的笔记
    m_noteListDock = new QDockWidget(tr("笔记列表"), this);
    m_noteListDock->setFeatures(QDockWidget::DockWidgetClosable |
                                 QDockWidget::DockWidgetMovable);
    m_noteList = new NoteListWidget(m_noteListDock);
    m_noteListDock->setWidget(m_noteList);
    addDockWidget(Qt::LeftDockWidgetArea, m_noteListDock);

    // 关键：让两个 Dock 垂直分割排列，而不是标签页重叠
    splitDockWidget(m_categoryDock, m_noteListDock, Qt::Vertical);

    // 添加到视图菜单，允许用户切换显示/隐藏
    m_viewMenu->addAction(m_categoryDock->toggleViewAction());
    m_viewMenu->addAction(m_noteListDock->toggleViewAction());
}

void MainWindow::createCentralWidget()
{
    m_editor = new RichTextEditor(this);
    setCentralWidget(m_editor);
}

void MainWindow::connectSignals()
{
    // 菜单动作
    connect(m_newNoteAction, &QAction::triggered,
            this, &MainWindow::onNewNote);
    connect(m_saveNoteAction, &QAction::triggered,
            this, &MainWindow::onSaveNote);
    connect(m_deleteNoteAction, &QAction::triggered,
            this, &MainWindow::onDeleteNote);
    connect(m_settingsAction, &QAction::triggered,
            this, &MainWindow::onShowSettings);
    connect(m_exitAction, &QAction::triggered,
            this, &QMainWindow::close);
    connect(m_aboutAction, &QAction::triggered,
            this, &MainWindow::onShowAbout);

    // 编辑菜单动作 - 连接到编辑器
    connect(m_undoAction, &QAction::triggered,
            m_editor->textEdit(), &QTextEdit::undo);
    connect(m_redoAction, &QAction::triggered,
            m_editor->textEdit(), &QTextEdit::redo);
    connect(m_cutAction, &QAction::triggered,
            m_editor->textEdit(), &QTextEdit::cut);
    connect(m_copyAction, &QAction::triggered,
            m_editor->textEdit(), &QTextEdit::copy);
    connect(m_pasteAction, &QAction::triggered,
            m_editor->textEdit(), &QTextEdit::paste);
    connect(m_selectAllAction, &QAction::triggered,
            m_editor->textEdit(), &QTextEdit::selectAll);

    // 分类树
    connect(m_categoryTree, &CategoryTree::categorySelected,
            this, &MainWindow::onCategorySelected);
    connect(m_categoryTree, &CategoryTree::createCategoryRequested,
            this, &MainWindow::onNewCategory);
    connect(m_categoryTree, &CategoryTree::editCategoryRequested,
            this, &MainWindow::onEditCategory);
    connect(m_categoryTree, &CategoryTree::deleteCategoryRequested,
            this, &MainWindow::onDeleteCategory);

    // 笔记列表
    connect(m_noteList, &NoteListWidget::noteSelected,
            this, &MainWindow::onNoteSelected);
    connect(m_noteList, &NoteListWidget::createNoteRequested,
            this, &MainWindow::onNewNote);
    connect(m_noteList, &NoteListWidget::renameNoteRequested,
            this, &MainWindow::onRenameNote);
    connect(m_noteList, &NoteListWidget::deleteNoteRequested,
            this, [this](const QString &noteId) {
                Q_UNUSED(noteId)
                onDeleteNote();
            });
    connect(m_noteList, &NoteListWidget::notePropertiesRequested,
            this, &MainWindow::onShowNoteProperties);

    // 搜索
    connect(m_searchWidget, &SearchWidget::searchRequested,
            this, &MainWindow::onSearchRequested);

    // 编辑器
    connect(m_editor, &RichTextEditor::textChanged,
            this, &MainWindow::onEditorTextChanged);

    // 自动保存
    connect(m_autoSaveTimer, &QTimer::timeout,
            this, &MainWindow::onAutoSave);
}

void MainWindow::loadSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("mainWindow/geometry").toByteArray());
    restoreState(settings.value("mainWindow/state").toByteArray());

    // 自动保存设置
    bool autoSave = settings.value("autoSave/enabled", false).toBool();
    if (autoSave) {
        int interval = settings.value("autoSave/interval", 5).toInt();
        m_autoSaveTimer->setInterval(interval * 60 * 1000);
        m_autoSaveTimer->start();
    }
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.setValue("mainWindow/geometry", saveGeometry());
    settings.setValue("mainWindow/state", saveState());
}

void MainWindow::updateWindowTitle()
{
    QString title = tr("NotepadPro");
    if (m_currentNote) {
        title = m_currentNote->title() + " - " + title;
        if (m_editor->isModified()) {
            title = "* " + title;
        }
    }
    setWindowTitle(title);
}

void MainWindow::updateStatusBar()
{
    int noteCount = NoteManager::instance()->getAllNotes().count();
    int categoryCount = NoteManager::instance()->getAllCategories().count();
    m_statusWidget->setNoteCount(noteCount);
    m_statusWidget->setCategoryCount(categoryCount);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_editor->isModified()) {
        int ret = QMessageBox::question(this, tr("保存更改"),
            tr("当前笔记已修改，是否保存？"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (ret == QMessageBox::Save) {
            onSaveNote();
        } else if (ret == QMessageBox::Cancel) {
            event->ignore();
            return;
        }
    }

    NoteManager::instance()->saveToFile();
    event->accept();
}

void MainWindow::onNewNote()
{
    Note *note = NoteManager::instance()->createNote();
    note->setTitle(tr("新建笔记"));
    note->setCategoryId(m_currentCategoryId);

    m_noteList->addNote(note);
    m_noteList->setCurrentNoteId(note->id());
    onNoteSelected(note->id());
    updateStatusBar();
}

void MainWindow::onSaveNote()
{
    if (!m_currentNote) return;

    m_currentNote->setContent(m_editor->toHtml());
    m_editor->setModified(false);
    NoteManager::instance()->saveToFile();
    updateWindowTitle();
    m_statusWidget->showMessage(tr("笔记已保存"));
}

void MainWindow::onDeleteNote()
{
    if (!m_currentNote) return;

    int ret = QMessageBox::question(this, tr("删除笔记"),
        tr("确定要删除笔记 \"%1\" 吗？").arg(m_currentNote->title()),
        QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes) {
        QString noteId = m_currentNote->id();
        m_noteList->removeNote(noteId);
        NoteManager::instance()->deleteNote(noteId);

        m_currentNote = nullptr;
        m_editor->clear();
        m_editor->setModified(false);
        updateWindowTitle();
        updateStatusBar();
    }
}

void MainWindow::onNewCategory()
{
    CategoryDialog dialog(this);
    dialog.setWindowTitle(tr("新建分类"));

    if (dialog.exec() == QDialog::Accepted) {
        Category *cat = NoteManager::instance()->createCategory(dialog.categoryName());
        cat->setColor(dialog.categoryColor());

        m_categoryTree->addCategory(cat);
        updateStatusBar();
    }
}

void MainWindow::onEditCategory(const QString &categoryId)
{
    Category *cat = NoteManager::instance()->getCategory(categoryId);
    if (!cat) return;

    CategoryDialog dialog(this);
    dialog.setWindowTitle(tr("编辑分类"));
    dialog.setCategory(cat);

    if (dialog.exec() == QDialog::Accepted) {
        cat->setName(dialog.categoryName());
        cat->setColor(dialog.categoryColor());
        m_categoryTree->updateCategory(cat);
    }
}

void MainWindow::onDeleteCategory(const QString &categoryId)
{
    Category *cat = NoteManager::instance()->getCategory(categoryId);
    if (!cat) return;

    int ret = QMessageBox::question(this, tr("删除分类"),
        tr("确定要删除分类 \"%1\" 吗？").arg(cat->name()),
        QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes) {
        m_categoryTree->removeCategory(categoryId);
        NoteManager::instance()->deleteCategory(categoryId);
        updateStatusBar();
    }
}

void MainWindow::onNoteSelected(const QString &noteId)
{
    // 保存当前笔记
    if (m_currentNote && m_editor->isModified()) {
        m_currentNote->setContent(m_editor->toHtml());
    }

    m_currentNote = NoteManager::instance()->getNote(noteId);
    if (m_currentNote) {
        m_editor->setHtml(m_currentNote->content());
        m_editor->setModified(false);
    }
    updateWindowTitle();
}

/**
 * @brief 分类选择事件处理
 * @param categoryId 选中的分类ID
 *
 * 当用户点击分类树中的某个分类时：
 * 1. 保存当前选中的分类ID
 * 2. 过滤笔记列表，只显示该分类下的笔记
 * 3. 如果分类ID为空，显示所有笔记
 */
void MainWindow::onCategorySelected(const QString &categoryId)
{
    m_currentCategoryId = categoryId;

    // 根据分类过滤笔记列表
    m_noteList->clear();

    QList<Note*> notes;
    if (categoryId.isEmpty()) {
        // 未选择分类时显示所有笔记
        notes = NoteManager::instance()->getAllNotes();
    } else {
        // 显示指定分类下的笔记
        notes = NoteManager::instance()->getNotesByCategory(categoryId);
    }

    for (Note *note : notes) {
        m_noteList->addNote(note);
    }
}

void MainWindow::onSearchRequested(const QString &text)
{
    if (text.isEmpty()) {
        m_noteList->refreshList();
        return;
    }

    // 搜索笔记
    QList<Note*> results = NoteManager::instance()->searchNotes(text);
    m_noteList->clear();
    for (Note *note : results) {
        m_noteList->addNote(note);
    }
}

/**
 * @brief 重命名笔记
 * @param noteId 笔记ID
 *
 * 弹出输入对话框让用户输入新名称
 */
void MainWindow::onRenameNote(const QString &noteId)
{
    Note *note = NoteManager::instance()->getNote(noteId);
    if (!note) return;

    bool ok;
    QString newTitle = QInputDialog::getText(this, tr("重命名笔记"),
        tr("请输入新名称:"), QLineEdit::Normal, note->title(), &ok);

    if (ok && !newTitle.trimmed().isEmpty()) {
        note->setTitle(newTitle.trimmed());
        m_noteList->updateNote(note);
        updateWindowTitle();
        m_statusWidget->showMessage(tr("笔记已重命名"));
    }
}

void MainWindow::onShowNoteProperties(const QString &noteId)
{
    Note *note = NoteManager::instance()->getNote(noteId);
    if (!note) return;

    NotePropertiesDialog dialog(this);
    dialog.setNote(note);

    if (dialog.exec() == QDialog::Accepted) {
        note->setTitle(dialog.noteTitle());
        note->setCategoryId(dialog.categoryId());
        m_noteList->updateNote(note);
        updateWindowTitle();
    }
}

void MainWindow::onShowSettings()
{
    SettingsDialog dialog(this);
    dialog.exec();
}

void MainWindow::onShowAbout()
{
    AboutDialog dialog(this);
    dialog.exec();
}

void MainWindow::onEditorTextChanged()
{
    updateWindowTitle();

    // 更新字数统计
    QString text = m_editor->toPlainText();
    m_statusWidget->setCharCount(text.length());
    m_statusWidget->setWordCount(text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts).count());
}

void MainWindow::onAutoSave()
{
    if (m_currentNote && m_editor->isModified()) {
        onSaveNote();
    }
}
