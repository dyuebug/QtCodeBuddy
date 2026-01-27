/**
 * @file DialogDemo.h
 * @brief 第6章示例 - 对话框演示
 * 
 * 本章学习要点：
 * 1. 标准对话框（QMessageBox）
 * 2. 文件对话框（QFileDialog）
 * 3. 颜色对话框（QColorDialog）
 * 4. 字体对话框（QFontDialog）
 * 5. 输入对话框（QInputDialog）
 * 6. 进度对话框（QProgressDialog）
 * 7. 自定义对话框
 * 8. 对话框的模态性
 * 9. 对话框的返回值处理
 */

#ifndef DIALOGDEMO_H
#define DIALOGDEMO_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

/**
 * @class DialogDemo
 * @brief 演示各种对话框的使用
 */
class DialogDemo : public QWidget
{
    Q_OBJECT

public:
    explicit DialogDemo(QWidget *parent = nullptr);

private:
    void setupUi();
    void setupMessageDialogDemo(QWidget *parent);
    void setupFileDialogDemo(QWidget *parent);
    void setupColorFontDialogDemo(QWidget *parent);
    void setupInputDialogDemo(QWidget *parent);
    void setupProgressDialogDemo(QWidget *parent);
    void setupCustomDialogDemo(QWidget *parent);
    void connectSignals();
    
    // 辅助函数：添加日志
    void addLog(const QString &message);

private slots:
    // 消息对话框槽函数
    void onInformationButton();
    void onQuestionButton();
    void onWarningButton();
    void onCriticalButton();
    void onAboutButton();
    
    // 文件对话框槽函数
    void onOpenFile();
    void onSaveFile();
    void onSelectDirectory();
    void onSelectMultipleFiles();
    
    // 颜色和字体对话框槽函数
    void onSelectColor();
    void onSelectFont();
    
    // 输入对话框槽函数
    void onGetText();
    void onGetInt();
    void onGetDouble();
    void onGetItem();
    
    // 进度对话框槽函数
    void onStartProgress();
    
    // 自定义对话框槽函数
    void onShowCustomDialog();
    void onShowCustomDialogModal();
    void onShowCustomDialogModeless();

private:
    QTabWidget *m_tabWidget;
    
    // 消息对话框部件
    QPushButton *m_infoBtn;
    QPushButton *m_questionBtn;
    QPushButton *m_warningBtn;
    QPushButton *m_criticalBtn;
    QPushButton *m_aboutBtn;
    
    // 文件对话框部件
    QPushButton *m_openFileBtn;
    QPushButton *m_saveFileBtn;
    QPushButton *m_selectDirBtn;
    QPushButton *m_selectMultipleBtn;
    QLabel *m_filePathLabel;
    
    // 颜色和字体对话框部件
    QPushButton *m_selectColorBtn;
    QPushButton *m_selectFontBtn;
    QLabel *m_colorFontLabel;
    QLineEdit *m_colorEdit;
    QLineEdit *m_fontEdit;
    
    // 输入对话框部件
    QPushButton *m_getTextBtn;
    QPushButton *m_getIntBtn;
    QPushButton *m_getDoubleBtn;
    QPushButton *m_getItemBtn;
    QLabel *m_inputResultLabel;
    
    // 进度对话框部件
    QPushButton *m_startProgressBtn;
    QLabel *m_progressStatusLabel;
    
    // 自定义对话框部件
    QPushButton *m_showCustomBtn;
    QPushButton *m_showModalBtn;
    QPushButton *m_showModelessBtn;
    QLabel *m_customDialogResult;
    
    // 日志输出
    QTextEdit *m_logTextEdit;
};

#endif // DIALOGDEMO_H
