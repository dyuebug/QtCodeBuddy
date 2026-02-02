/**
 * @file FileIODemo.h
 * @brief 第10章示例 - 文件操作演示
 *
 * 本章学习要点：
 * 1. QFile 文件读写
 * 2. QTextStream 文本流处理
 * 3. QDataStream 二进制流处理
 * 4. QDir 目录操作
 * 5. QFileInfo 文件信息获取
 */

#ifndef FILEIODEMO_H
#define FILEIODEMO_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QListWidget>

class FileIODemo : public QWidget
{
    Q_OBJECT

public:
    explicit FileIODemo(QWidget *parent = nullptr);

private:
    void setupUi();
    void setupTextFileDemo(QWidget *parent);
    void setupBinaryFileDemo(QWidget *parent);
    void setupDirDemo(QWidget *parent);
    void connectSignals();
    void addLog(const QString &message);

private slots:
    // 文本文件操作
    void onWriteTextFile();
    void onReadTextFile();
    void onAppendTextFile();

    // 二进制文件操作
    void onWriteBinaryFile();
    void onReadBinaryFile();

    // 目录操作
    void onBrowseDir();
    void onCreateDir();
    void onListFiles();

private:
    QTabWidget *m_tabWidget;

    // 文本文件部件
    QTextEdit *m_textEdit;
    QLineEdit *m_filePathEdit;
    QPushButton *m_writeBtn;
    QPushButton *m_readBtn;
    QPushButton *m_appendBtn;

    // 二进制文件部件
    QLineEdit *m_nameEdit;
    QLineEdit *m_ageEdit;
    QLineEdit *m_binaryPathEdit;
    QPushButton *m_writeBinaryBtn;
    QPushButton *m_readBinaryBtn;
    QLabel *m_binaryResultLabel;

    // 目录操作部件
    QLineEdit *m_dirPathEdit;
    QPushButton *m_browseDirBtn;
    QPushButton *m_createDirBtn;
    QPushButton *m_listFilesBtn;
    QListWidget *m_fileListWidget;

    // 日志
    QTextEdit *m_logTextEdit;
};

#endif // FILEIODEMO_H
