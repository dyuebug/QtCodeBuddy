/**
 * @file MainWindow.h
 * @brief 主窗口
 *
 * 知识点：
 * - QMainWindow 架构
 * - 菜单栏、工具栏、状态栏
 * - QDockWidget 停靠窗口
 * - 信号槽整合
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QSplitter>
#include <QTimer>

class NoteListWidget;
class RichTextEditor;
class CategoryTree;
class SearchWidget;
class StatusWidget;
class Note;

/**
 * @class MainWindow
 * @brief 主窗口类
 *
 * 整合所有控件，提供完整的笔记本应用界面
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setupUi();
    void createMenuBar();
    void createToolBar();
    void createStatusBar();
    void createDockWidgets();
    void createCentralWidget();
    void connectSignals();
    void loadSettings();
    void saveSettings();

    void updateWindowTitle();
    void updateStatusBar();

private slots:
    // 文件操作
    void onNewNote();
    void onSaveNote();
    void onDeleteNote();

    // 分类操作
    void onNewCategory();
    void onEditCategory(const QString &categoryId);
    void onDeleteCategory(const QString &categoryId);

    // 笔记选择
    void onNoteSelected(const QString &noteId);
    void onCategorySelected(const QString &categoryId);

    // 搜索
    void onSearchRequested(const QString &text);

    // 对话框
    void onShowNoteProperties(const QString &noteId);
    void onRenameNote(const QString &noteId);  // 新增：重命名笔记
    void onShowSettings();
    void onShowAbout();

    // 编辑器
    void onEditorTextChanged();
    void onAutoSave();

private:
    // 菜单
    QMenu *m_fileMenu;
    QMenu *m_editMenu;
    QMenu *m_viewMenu;
    QMenu *m_helpMenu;

    // 工具栏
    QToolBar *m_mainToolBar;

    // 动作
    QAction *m_newNoteAction;
    QAction *m_saveNoteAction;
    QAction *m_deleteNoteAction;
    QAction *m_settingsAction;
    QAction *m_exitAction;
    QAction *m_aboutAction;

    // 编辑动作
    QAction *m_undoAction;
    QAction *m_redoAction;
    QAction *m_cutAction;
    QAction *m_copyAction;
    QAction *m_pasteAction;
    QAction *m_selectAllAction;

    // 停靠窗口
    QDockWidget *m_categoryDock;
    QDockWidget *m_noteListDock;

    // 控件
    CategoryTree *m_categoryTree;
    NoteListWidget *m_noteList;
    RichTextEditor *m_editor;
    SearchWidget *m_searchWidget;
    StatusWidget *m_statusWidget;

    // 状态
    Note *m_currentNote;
    QString m_currentCategoryId;
    QTimer *m_autoSaveTimer;
};

#endif // MAINWINDOW_H
