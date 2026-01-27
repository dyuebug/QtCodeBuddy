/**
 * @file MainWindowDemo.h
 * @brief 第7章示例 - QMainWindow主窗口演示
 * 
 * 本章学习要点：
 * 1. QMainWindow的架构：菜单栏、工具栏、状态栏、中心部件、停靠窗口
 * 2. 菜单栏（QMenuBar）的使用
 * 3. 工具栏（QToolBar）的使用
 * 4. 状态栏（QStatusBar）的使用
 * 5. 中心部件（Central Widget）的设置
 * 6. 停靠窗口（QDockWidget）的使用
 * 7. 上下文菜单（QMenu）的使用
 * 8. 保存和恢复窗口状态
 */

#ifndef MAINWINDOWDEMO_H
#define MAINWINDOWDEMO_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QListWidget>
#include <QTreeWidget>

#include "TextEditWidget.h"

/**
 * @class MainWindowDemo
 * @brief 演示QMainWindow主窗口的各种功能
 */
class MainWindowDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowDemo(QWidget *parent = nullptr);
    
    ~MainWindowDemo();

protected:
    /**
     * @brief 重写上下文菜单事件
     */
    void contextMenuEvent(QContextMenuEvent *event) override;
    
    /**
     * @brief 重写关闭事件
     */
    void closeEvent(QCloseEvent *event) override;

private:
    void setupUi();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void createCentralWidget();
    void connectSignals();
    
    // 辅助函数
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void exportFile();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    void updateStatusBar();
    
    // 查找和替换
    void showFindDialog();
    void findNext(const QString &text, Qt::CaseSensitivity cs);
    void findPrevious(const QString &text, Qt::CaseSensitivity cs);
    void replaceText();

private slots:
    // 文件菜单槽函数
    void onNew();
    void onOpen();
    void onSave();
    void onSaveAs();
    void onExport();
    void onPrint();
    void onPrintPreview();
    void onExit();
    
    // 编辑菜单槽函数
    void onUndo();
    void onRedo();
    void onCut();
    void onCopy();
    void onPaste();
    void onSelectAll();
    void onClear();
    
    // 格式菜单槽函数
    void onBold(bool checked);
    void onItalic(bool checked);
    void onUnderline(bool checked);
    void onFontSizeChanged(int size);
    void onFontFamilyChanged(const QString &family);
    void onClearFormat();
    
    // 视图菜单槽函数
    void onShowHideDock(bool show);
    void onShowHideStatusBar(bool show);
    void onShowHideToolBar(bool show);
    
    // 帮助菜单槽函数
    void onAbout();
    void onAboutQt();
    
    // 其他槽函数
    void onTextChanged();
    void onSelectionChanged();

private:
    // 菜单栏
    QMenuBar *m_menuBar;
    QMenu *m_fileMenu;
    QMenu *m_editMenu;
    QMenu *m_formatMenu;
    QMenu *m_viewMenu;
    QMenu *m_helpMenu;
    
    // 菜单项
    QAction *m_newAction;
    QAction *m_openAction;
    QAction *m_saveAction;
    QAction *m_saveAsAction;
    QAction *m_exportAction;
    QAction *m_printAction;
    QAction *m_printPreviewAction;
    QAction *m_exitAction;
    
    QAction *m_undoAction;
    QAction *m_redoAction;
    QAction *m_cutAction;
    QAction *m_copyAction;
    QAction *m_pasteAction;
    QAction *m_selectAllAction;
    QAction *m_findAction;
    QAction *m_replaceAction;
    
    QAction *m_boldAction;
    QAction *m_italicAction;
    QAction *m_underlineAction;
    QAction *m_clearFormatAction;
    
    QAction *m_showDockAction;
    QAction *m_showStatusBarAction;
    QAction *m_showToolBarAction;
    
    QAction *m_aboutAction;
    QAction *m_aboutQtAction;
    
    // 工具栏
    QToolBar *m_fileToolBar;
    QToolBar *m_editToolBar;
    QToolBar *m_formatToolBar;
    
    // 格式工具栏控件
    QComboBox *m_fontFamilyCombo;
    QSpinBox *m_fontSizeSpin;
    
    // 状态栏
    QStatusBar *m_statusBar;
    QLabel *m_statusLabel;
    QLabel *m_cursorPositionLabel;
    QLabel *m_wordCountLabel;
    QLabel *m_fileInfoLabel;
    
    // 中心部件
    TextEditWidget *m_textEdit;
    
    // 停靠窗口
    QDockWidget *m_structureDock;
    QDockWidget *m_propertiesDock;
    
    // 结构窗口部件
    QListWidget *m_structureList;
    
    // 属性窗口部件
    QTreeWidget *m_propertiesTree;
    
    // 其他
    QString m_currentFile;
    bool m_isUntitled;
};

#endif // MAINWINDOWDEMO_H
