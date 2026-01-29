/**
 * @file SearchWidget.h
 * @brief 搜索控件
 *
 * 知识点：
 * - QLineEdit 输入处理
 * - QTimer 延迟搜索
 * - 事件过滤器
 * - 键盘快捷键
 */

#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTimer>

/**
 * @class SearchWidget
 * @brief 搜索控件
 *
 * 提供搜索输入框，支持延迟搜索和清除功能
 */
class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent = nullptr);
    ~SearchWidget() override = default;

    // 搜索文本
    QString searchText() const;
    void setSearchText(const QString &text);
    void clearSearch();

    // 延迟设置
    int searchDelay() const;
    void setSearchDelay(int msec);

signals:
    void searchTextChanged(const QString &text);
    void searchRequested(const QString &text);
    void searchCleared();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void setupUi();
    void connectSignals();

private slots:
    void onTextChanged(const QString &text);
    void onSearchTimeout();
    void onClearClicked();

private:
    QHBoxLayout *m_layout;
    QLineEdit *m_searchEdit;
    QPushButton *m_clearButton;
    QTimer *m_searchTimer;

    int m_searchDelay;  // 搜索延迟（毫秒）
};

#endif // SEARCHWIDGET_H
