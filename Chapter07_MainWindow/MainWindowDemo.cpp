/**
 * @file MainWindowDemo.cpp
 * @brief 第7章示例 - QMainWindow主窗口演示实现
 */

#include "MainWindowDemo.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QTextCursor>
#include <QTreeWidgetItem>
#include <QApplication>
#include <QCloseEvent>
#include <QContextMenuEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>

MainWindowDemo::MainWindowDemo(QWidget *parent)
    : QMainWindow(parent)
    , m_menuBar(nullptr)
    , m_fileMenu(nullptr)
    , m_editMenu(nullptr)
    , m_formatMenu(nullptr)
    , m_viewMenu(nullptr)
    , m_helpMenu(nullptr)
    , m_newAction(nullptr)
    , m_openAction(nullptr)
    , m_saveAction(nullptr)
    , m_saveAsAction(nullptr)
    , m_exportAction(nullptr)
    , m_printAction(nullptr)
    , m_printPreviewAction(nullptr)
    , m_exitAction(nullptr)
    , m_undoAction(nullptr)
    , m_redoAction(nullptr)
    , m_cutAction(nullptr)
    , m_copyAction(nullptr)
    , m_pasteAction(nullptr)
    , m_selectAllAction(nullptr)
    , m_findAction(nullptr)
    , m_replaceAction(nullptr)
    , m_boldAction(nullptr)
    , m_italicAction(nullptr)
    , m_underlineAction(nullptr)
    , m_clearFormatAction(nullptr)
    , m_showDockAction(nullptr)
    , m_showStatusBarAction(nullptr)
    , m_showToolBarAction(nullptr)
    , m_aboutAction(nullptr)
    , m_aboutQtAction(nullptr)
    , m_fileToolBar(nullptr)
    , m_editToolBar(nullptr)
    , m_formatToolBar(nullptr)
    , m_fontFamilyCombo(nullptr)
    , m_fontSizeSpin(nullptr)
    , m_statusBar(nullptr)
    , m_statusLabel(nullptr)
    , m_cursorPositionLabel(nullptr)
    , m_wordCountLabel(nullptr)
    , m_fileInfoLabel(nullptr)
    , m_textEdit(nullptr)
    , m_structureDock(nullptr)
    , m_propertiesDock(nullptr)
    , m_structureList(nullptr)
    , m_propertiesTree(nullptr)
    , m_currentFile()
    , m_isUntitled(true)
{
    setupUi();
    connectSignals();
    
    setWindowTitle("第7章：主窗口 - 文本编辑器");
    resize(900, 650);
}

/**
 * @brief 析构函数
 */
MainWindowDemo::~MainWindowDemo()
{
}

/**
 * @brief 设置主界面
 */
void MainWindowDemo::setupUi()
{
    // 创建菜单栏
    createMenus();
    
    // 创建工具栏
    createToolBars();
    
    // 创建状态栏
    createStatusBar();
    
    // 创建中心部件
    createCentralWidget();
    
    // 创建停靠窗口
    createDockWindows();
}

/**
 * @brief 创建菜单栏
 */
void MainWindowDemo::createMenus()
{
    // 文件菜单
    m_fileMenu = menuBar()->addMenu("文件(&F)");
    
    m_newAction = m_fileMenu->addAction("新建(&N)");
    m_newAction->setShortcut(QKeySequence::New);
    m_newAction->setStatusTip("创建新文件");
    
    m_openAction = m_fileMenu->addAction("打开(&O)");
    m_openAction->setShortcut(QKeySequence::Open);
    m_openAction->setStatusTip("打开文件");
    
    m_fileMenu->addSeparator();
    
    m_saveAction = m_fileMenu->addAction("保存(&S)");
    m_saveAction->setShortcut(QKeySequence::Save);
    m_saveAction->setStatusTip("保存文件");
    
    m_saveAsAction = m_fileMenu->addAction("另存为(&A)...");
    m_saveAsAction->setShortcut(QKeySequence::SaveAs);
    m_saveAsAction->setStatusTip("另存为新文件");
    
    m_exportAction = m_fileMenu->addAction("导出(&E)...");
    m_exportAction->setStatusTip("导出文件");
    
    m_fileMenu->addSeparator();
    
    m_printAction = m_fileMenu->addAction("打印(&P)...");
    m_printAction->setShortcut(QKeySequence::Print);
    m_printAction->setStatusTip("打印文件");
    
    m_printPreviewAction = m_fileMenu->addAction("打印预览(&V)...");
    m_printPreviewAction->setStatusTip("打印预览");
    
    m_fileMenu->addSeparator();
    
    m_exitAction = m_fileMenu->addAction("退出(&X)");
    m_exitAction->setShortcut(QKeySequence::Quit);
    m_exitAction->setStatusTip("退出程序");
    
    // 编辑菜单
    m_editMenu = menuBar()->addMenu("编辑(&E)");
    
    m_undoAction = m_editMenu->addAction("撤销(&U)");
    m_undoAction->setShortcut(QKeySequence::Undo);
    m_undoAction->setStatusTip("撤销操作");
    
    m_redoAction = m_editMenu->addAction("重做(&R)");
    m_redoAction->setShortcut(QKeySequence::Redo);
    m_redoAction->setStatusTip("重做操作");
    
    m_editMenu->addSeparator();
    
    m_cutAction = m_editMenu->addAction("剪切(&T)");
    m_cutAction->setShortcut(QKeySequence::Cut);
    m_cutAction->setStatusTip("剪切选中内容");
    
    m_copyAction = m_editMenu->addAction("复制(&C)");
    m_copyAction->setShortcut(QKeySequence::Copy);
    m_copyAction->setStatusTip("复制选中内容");
    
    m_pasteAction = m_editMenu->addAction("粘贴(&P)");
    m_pasteAction->setShortcut(QKeySequence::Paste);
    m_pasteAction->setStatusTip("粘贴内容");
    
    m_editMenu->addSeparator();
    
    m_selectAllAction = m_editMenu->addAction("全选(&A)");
    m_selectAllAction->setShortcut(QKeySequence::SelectAll);
    m_selectAllAction->setStatusTip("选中所有内容");
    
    m_findAction = m_editMenu->addAction("查找(&F)...");
    m_findAction->setShortcut(QKeySequence::Find);
    m_findAction->setStatusTip("查找文本");
    
    m_replaceAction = m_editMenu->addAction("替换(&E)...");
    m_replaceAction->setShortcut(QKeySequence::Replace);
    m_replaceAction->setStatusTip("替换文本");
    
    // 格式菜单
    m_formatMenu = menuBar()->addMenu("格式(&O)");
    
    m_boldAction = m_formatMenu->addAction("粗体(&B)");
    m_boldAction->setShortcut(QKeySequence::Bold);
    m_boldAction->setCheckable(true);
    m_boldAction->setStatusTip("设置粗体");
    
    m_italicAction = m_formatMenu->addAction("斜体(&I)");
    m_italicAction->setShortcut(QKeySequence::Italic);
    m_italicAction->setCheckable(true);
    m_italicAction->setStatusTip("设置斜体");
    
    m_underlineAction = m_formatMenu->addAction("下划线(&U)");
    m_underlineAction->setShortcut(QKeySequence::Underline);
    m_underlineAction->setCheckable(true);
    m_underlineAction->setStatusTip("设置下划线");
    
    m_formatMenu->addSeparator();
    
    m_clearFormatAction = m_formatMenu->addAction("清除格式(&L)");
    m_clearFormatAction->setStatusTip("清除所有格式");
    
    // 视图菜单
    m_viewMenu = menuBar()->addMenu("视图(&V)");
    
    m_showDockAction = m_viewMenu->addAction("显示/隐藏停靠窗口(&D)");
    m_showDockAction->setCheckable(true);
    m_showDockAction->setChecked(true);
    m_showDockAction->setStatusTip("显示或隐藏停靠窗口");
    
    m_showStatusBarAction = m_viewMenu->addAction("显示/隐藏状态栏(&S)");
    m_showStatusBarAction->setCheckable(true);
    m_showStatusBarAction->setChecked(true);
    m_showStatusBarAction->setStatusTip("显示或隐藏状态栏");
    
    m_showToolBarAction = m_viewMenu->addAction("显示/隐藏工具栏(&T)");
    m_showToolBarAction->setCheckable(true);
    m_showToolBarAction->setChecked(true);
    m_showToolBarAction->setStatusTip("显示或隐藏工具栏");
    
    // 帮助菜单
    m_helpMenu = menuBar()->addMenu("帮助(&H)");
    
    m_aboutAction = m_helpMenu->addAction("关于(&A)");
    m_aboutAction->setStatusTip("关于程序");
    
    m_aboutQtAction = m_helpMenu->addAction("关于Qt(&Q)");
    m_aboutQtAction->setStatusTip("关于Qt");
}

/**
 * @brief 创建工具栏
 */
void MainWindowDemo::createToolBars()
{
    // 文件工具栏
    m_fileToolBar = addToolBar("文件");
    m_fileToolBar->addAction(m_newAction);
    m_fileToolBar->addAction(m_openAction);
    m_fileToolBar->addAction(m_saveAction);
    
    // 编辑工具栏
    m_editToolBar = addToolBar("编辑");
    m_editToolBar->addAction(m_cutAction);
    m_editToolBar->addAction(m_copyAction);
    m_editToolBar->addAction(m_pasteAction);
    m_editToolBar->addSeparator();
    m_editToolBar->addAction(m_findAction);
    
    // 格式工具栏
    m_formatToolBar = addToolBar("格式");
    
    // 字体选择
    m_formatToolBar->addWidget(new QLabel("字体: "));
    m_fontFamilyCombo = new QComboBox(this);
    m_fontFamilyCombo->addItems({"Arial", "Times New Roman", "Courier New", "微软雅黑", "宋体"});
    m_fontFamilyCombo->setCurrentIndex(0);
    m_formatToolBar->addWidget(m_fontFamilyCombo);
    
    // 字体大小
    m_formatToolBar->addWidget(new QLabel("大小: "));
    m_fontSizeSpin = new QSpinBox(this);
    m_fontSizeSpin->setRange(6, 72);
    m_fontSizeSpin->setValue(12);
    m_formatToolBar->addWidget(m_fontSizeSpin);
    
    // 格式按钮
    m_formatToolBar->addSeparator();
    m_formatToolBar->addAction(m_boldAction);
    m_formatToolBar->addAction(m_italicAction);
    m_formatToolBar->addAction(m_underlineAction);
}

/**
 * @brief 创建状态栏
 */
void MainWindowDemo::createStatusBar()
{
    m_statusLabel = new QLabel("就绪");
    statusBar()->addWidget(m_statusLabel);
    
    m_cursorPositionLabel = new QLabel("行: 1, 列: 1");
    statusBar()->addPermanentWidget(m_cursorPositionLabel);
    
    m_wordCountLabel = new QLabel("字数: 0");
    statusBar()->addPermanentWidget(m_wordCountLabel);
    
    m_fileInfoLabel = new QLabel("");
    statusBar()->addPermanentWidget(m_fileInfoLabel);
}

/**
 * @brief 创建中心部件
 */
void MainWindowDemo::createCentralWidget()
{
    m_textEdit = new TextEditWidget(this);
    setCentralWidget(m_textEdit);
    
    m_isUntitled = true;
    m_currentFile = tr("未命名.txt");
    setWindowTitle(m_currentFile + "[*]");
    
    connect(m_textEdit->document(), &QTextDocument::contentsChanged,
            this, &MainWindowDemo::onTextChanged);
    connect(m_textEdit, &TextEditWidget::selectionChanged,
            this, &MainWindowDemo::onSelectionChanged);
}

/**
 * @brief 创建停靠窗口
 */
void MainWindowDemo::createDockWindows()
{
    // 结构窗口
    m_structureDock = new QDockWidget("文档结构", this);
    m_structureDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    m_structureList = new QListWidget(m_structureDock);
    m_structureList->addItems({"段落1", "段落2", "段落3"});
    
    m_structureDock->setWidget(m_structureList);
    addDockWidget(Qt::LeftDockWidgetArea, m_structureDock);
    m_viewMenu->addAction(m_structureDock->toggleViewAction());
    
    // 属性窗口
    m_propertiesDock = new QDockWidget("文档属性", this);
    m_propertiesDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    m_propertiesTree = new QTreeWidget(m_propertiesDock);
    m_propertiesTree->setHeaderLabels({"属性", "值"});
    
    QTreeWidgetItem *infoItem = new QTreeWidgetItem(m_propertiesTree);
    infoItem->setText(0, "文档信息");
    infoItem->setText(1, "");
    
    QTreeWidgetItem *item1 = new QTreeWidgetItem(infoItem);
    item1->setText(0, "创建时间");
    item1->setText(1, "2024-01-01 00:00:00");
    
    QTreeWidgetItem *item2 = new QTreeWidgetItem(infoItem);
    item2->setText(0, "修改时间");
    item2->setText(1, "2024-01-01 00:00:00");
    
    QTreeWidgetItem *item3 = new QTreeWidgetItem(infoItem);
    item3->setText(0, "字符数");
    item3->setText(1, "0");
    
    m_propertiesTree->expandAll();
    
    m_propertiesDock->setWidget(m_propertiesTree);
    addDockWidget(Qt::RightDockWidgetArea, m_propertiesDock);
    m_viewMenu->addAction(m_propertiesDock->toggleViewAction());
}

/**
 * @brief 连接信号和槽
 */
void MainWindowDemo::connectSignals()
{
    // 文件菜单
    connect(m_newAction, &QAction::triggered, this, &MainWindowDemo::onNew);
    connect(m_openAction, &QAction::triggered, this, &MainWindowDemo::onOpen);
    connect(m_saveAction, &QAction::triggered, this, &MainWindowDemo::onSave);
    connect(m_saveAsAction, &QAction::triggered, this, &MainWindowDemo::onSaveAs);
    connect(m_exportAction, &QAction::triggered, this, &MainWindowDemo::onExport);
    connect(m_printAction, &QAction::triggered, this, &MainWindowDemo::onPrint);
    connect(m_printPreviewAction, &QAction::triggered, this, &MainWindowDemo::onPrintPreview);
    connect(m_exitAction, &QAction::triggered, this, &MainWindowDemo::onExit);
    
    // 编辑菜单
    connect(m_undoAction, &QAction::triggered, m_textEdit, &TextEditWidget::undo);
    connect(m_redoAction, &QAction::triggered, m_textEdit, &TextEditWidget::redo);
    connect(m_cutAction, &QAction::triggered, m_textEdit, &TextEditWidget::cut);
    connect(m_copyAction, &QAction::triggered, m_textEdit, &TextEditWidget::copy);
    connect(m_pasteAction, &QAction::triggered, m_textEdit, &TextEditWidget::paste);
    connect(m_selectAllAction, &QAction::triggered, m_textEdit, &TextEditWidget::selectAll);
    
    // 格式菜单
    connect(m_boldAction, &QAction::triggered, this, &MainWindowDemo::onBold);
    connect(m_italicAction, &QAction::triggered, this, &MainWindowDemo::onItalic);
    connect(m_underlineAction, &QAction::triggered, this, &MainWindowDemo::onUnderline);
    connect(m_clearFormatAction, &QAction::triggered, this, &MainWindowDemo::onClearFormat);
    
    // 字体控制
    connect(m_fontFamilyCombo, &QComboBox::currentTextChanged,
            this, &MainWindowDemo::onFontFamilyChanged);
    connect(m_fontSizeSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindowDemo::onFontSizeChanged);
    
    // 视图菜单
    connect(m_showDockAction, &QAction::triggered, this, &MainWindowDemo::onShowHideDock);
    connect(m_showStatusBarAction, &QAction::triggered, this, &MainWindowDemo::onShowHideStatusBar);
    connect(m_showToolBarAction, &QAction::triggered, this, &MainWindowDemo::onShowHideToolBar);
    
    // 帮助菜单
    connect(m_aboutAction, &QAction::triggered, this, &MainWindowDemo::onAbout);
    connect(m_aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
    
    // 其他连接
    connect(m_textEdit->document(), &QTextDocument::undoAvailable,
            m_undoAction, &QAction::setEnabled);
    connect(m_textEdit->document(), &QTextDocument::redoAvailable,
            m_redoAction, &QAction::setEnabled);
    connect(m_textEdit, &TextEditWidget::textChanged,
            this, &MainWindowDemo::onTextChanged);
    connect(m_textEdit, &TextEditWidget::selectionChanged,
            this, &MainWindowDemo::onSelectionChanged);
    
    // 初始状态
    m_undoAction->setEnabled(false);
    m_redoAction->setEnabled(false);
}

// ========== 文件操作 ==========

void MainWindowDemo::onNew()
{
    if (maybeSave()) {
        m_textEdit->clear();
        m_isUntitled = true;
        m_currentFile = tr("未命名.txt");
        setWindowTitle(m_currentFile + "[*]");
        setWindowModified(false);
        m_statusLabel->setText("新建文档");
    }
}

void MainWindowDemo::onOpen()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("打开文件"));
        if (!fileName.isEmpty()) {
            loadFile(fileName);
        }
    }
}

bool MainWindowDemo::onSave()
{
    if (m_isUntitled) {
        onSaveAs();
        return !m_isUntitled;  // 如果保存成功，返回true
    } else {
        return saveFile(m_currentFile);
    }
}

void MainWindowDemo::onSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"), m_currentFile);
    if (!fileName.isEmpty()) {
        saveFile(fileName);
    }
}

void MainWindowDemo::onExport()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出"), "", tr("文本文件 (*.txt);;HTML文件 (*.html)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            
            if (fileName.endsWith(".html", Qt::CaseInsensitive)) {
                out << m_textEdit->toHtml();
            } else {
                out << m_textEdit->toPlainText();
            }
            
            file.close();
            m_statusLabel->setText(tr("导出成功：%1").arg(fileName));
        }
    }
}

void MainWindowDemo::onPrint()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    
    if (dlg.exec() == QDialog::Accepted) {
        m_textEdit->print(&printer);
    }
}

void MainWindowDemo::onPrintPreview()
{
    m_statusLabel->setText(tr("打印预览功能待实现"));
}

void MainWindowDemo::onExit()
{
    if (maybeSave()) {
        close();
    }
}

// ========== 编辑操作 ==========

void MainWindowDemo::onUndo()
{
    m_textEdit->undo();
}

void MainWindowDemo::onRedo()
{
    m_textEdit->redo();
}

void MainWindowDemo::onCut()
{
    m_textEdit->cut();
}

void MainWindowDemo::onCopy()
{
    m_textEdit->copy();
}

void MainWindowDemo::onPaste()
{
    m_textEdit->paste();
}

void MainWindowDemo::onClear()
{
    m_textEdit->clear();
}

void MainWindowDemo::onSelectAll()
{
    m_textEdit->selectAll();
}

void MainWindowDemo::onBold(bool checked)
{
    m_textEdit->boldText(checked);
}

void MainWindowDemo::onItalic(bool checked)
{
    m_textEdit->italicText(checked);
}

void MainWindowDemo::onUnderline(bool checked)
{
    m_textEdit->underlineText(checked);
}

void MainWindowDemo::onFontSizeChanged(int size)
{
    m_textEdit->setFontSize(size);
}

void MainWindowDemo::onFontFamilyChanged(const QString &family)
{
    QFont font = m_textEdit->currentFont();
    font.setFamily(family);
    m_textEdit->setCurrentFont(font);
}

void MainWindowDemo::onClearFormat()
{
    m_textEdit->clearFormatting();
    m_boldAction->setChecked(false);
    m_italicAction->setChecked(false);
    m_underlineAction->setChecked(false);
}

void MainWindowDemo::onShowHideDock(bool show)
{
    m_structureDock->setVisible(show);
    m_propertiesDock->setVisible(show);
}

void MainWindowDemo::onShowHideStatusBar(bool show)
{
    statusBar()->setVisible(show);
}

void MainWindowDemo::onShowHideToolBar(bool show)
{
    m_fileToolBar->setVisible(show);
    m_editToolBar->setVisible(show);
    m_formatToolBar->setVisible(show);
}

void MainWindowDemo::onAbout()
{
    QMessageBox::about(this, tr("关于"), 
        tr("Qt6主窗口演示程序\n"
           "版本：1.0.0\n"
           "基于QMainWindow的文本编辑器示例\n"
           "演示了菜单栏、工具栏、状态栏、中心部件、停靠窗口等功能。"));
}

void MainWindowDemo::onAboutQt()
{
    qApp->aboutQt();
}

// ========== 其他函数 ==========

void MainWindowDemo::onTextChanged()
{
    setWindowModified(true);
    updateStatusBar();
}

void MainWindowDemo::onSelectionChanged()
{
    QTextCursor cursor = m_textEdit->textCursor();
    QTextCharFormat format = cursor.charFormat();
    
    m_boldAction->setChecked(format.fontWeight() == QFont::Bold);
    m_italicAction->setChecked(format.fontItalic());
    m_underlineAction->setChecked(format.fontUnderline());
}

/**
 * @brief 判断是否需要保存
 */
bool MainWindowDemo::maybeSave()
{
    if (m_textEdit->document()->isModified()) {
        QDialog *dialog = new QDialog(this);
        dialog->setWindowTitle(tr("警告"));
        dialog->setModal(true);
        dialog->resize(400, 150);

        QVBoxLayout *layout = new QVBoxLayout(dialog);

        QLabel *label = new QLabel(tr("文档已被修改。\n是否保存更改？"), dialog);
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(dialog);
        QPushButton *saveBtn = buttonBox->addButton(tr("保存"), QDialogButtonBox::AcceptRole);
        QPushButton *discardBtn = buttonBox->addButton(tr("不保存"), QDialogButtonBox::DestructiveRole);
        buttonBox->addButton(tr("取消"), QDialogButtonBox::RejectRole);

        // 连接信号来获取被点击的按钮
        QPushButton *clickedButton = nullptr;
        connect(buttonBox, &QDialogButtonBox::clicked, [&](QAbstractButton *button) {
            clickedButton = qobject_cast<QPushButton*>(button);
        });

        layout->addWidget(buttonBox);

        dialog->exec();

        bool result = false;
        if (clickedButton == saveBtn) {
            result = onSave();  // 保存
        } else if (clickedButton == discardBtn) {
            result = true;      // 不保存
        } else {
            result = false;     // 取消
        }

        delete dialog;
        return result;
    }
    return true;
}

/**
 * @brief 加载文件
 */
void MainWindowDemo::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QDialog *dialog = new QDialog(this);
        dialog->setWindowTitle(tr("警告"));
        dialog->setModal(true);
        dialog->resize(400, 150);

        QVBoxLayout *layout = new QVBoxLayout(dialog);

        QLabel *label = new QLabel(tr("无法读取文件 %1:\n%2.")
            .arg(fileName, file.errorString()), dialog);
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(dialog);
        buttonBox->addButton(tr("确定"), QDialogButtonBox::AcceptRole);
        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);

        dialog->exec();
        delete dialog;
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    m_textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    m_statusLabel->setText(tr("文件加载成功"));
}

/**
 * @brief 保存文件
 */
bool MainWindowDemo::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("警告"), 
            tr("无法写入文件 %1:\n%2.")
            .arg(fileName, file.errorString()),
            QMessageBox::Ok);
        return false;
    }
    
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << m_textEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    
    setCurrentFile(fileName);
    m_statusLabel->setText(tr("文件保存成功"));
    return true;
}

/**
 * @brief 设置当前文件
 */
void MainWindowDemo::setCurrentFile(const QString &fileName)
{
    m_currentFile = fileName;
    m_isUntitled = false;
    
    m_textEdit->document()->setModified(false);
    setWindowModified(false);
    
    QString shownName = m_currentFile;
    if (m_currentFile.isEmpty()) {
        shownName = "未命名.txt";
    }
    setWindowTitle(tr("%1[*] - 文本编辑器").arg(shownName));
}

/**
 * @brief 更新状态栏
 */
void MainWindowDemo::updateStatusBar()
{
    QTextCursor cursor = m_textEdit->textCursor();
    int blockNumber = cursor.blockNumber() + 1;
    int columnNumber = cursor.columnNumber() + 1;
    
    m_cursorPositionLabel->setText(tr("行: %1, 列: %2").arg(blockNumber).arg(columnNumber));
    
    int wordCount = m_textEdit->toPlainText().length();
    m_wordCountLabel->setText(tr("字数: %1").arg(wordCount));
    
    // 更新属性窗口
    if (m_propertiesTree->topLevelItemCount() > 0) {
        QTreeWidgetItem *root = m_propertiesTree->topLevelItem(0);
        if (root->childCount() >= 3) {
            root->child(2)->setText(1, QString::number(wordCount));
        }
    }
}

/**
 * @brief 上下文菜单事件
 */
void MainWindowDemo::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    
    menu.addAction(m_cutAction);
    menu.addAction(m_copyAction);
    menu.addAction(m_pasteAction);
    menu.addSeparator();
    menu.addAction(m_selectAllAction);
    menu.addSeparator();
    menu.addAction(m_findAction);
    menu.addAction(m_replaceAction);
    
    menu.exec(event->globalPos());
}

/**
 * @brief 关闭事件
 */
void MainWindowDemo::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}
