/**
 * @file SearchWidget.cpp
 * @brief 搜索控件实现
 *
 * 知识点：
 * - QLineEdit 输入框控件
 * - QTimer 延迟搜索（防抖动）
 * - eventFilter 事件过滤器拦截键盘事件
 * - 信号槽实现搜索功能
 */

#include "SearchWidget.h"

#include <QKeyEvent>

/**
 * @brief 构造函数
 * @param parent 父控件指针
 */
SearchWidget::SearchWidget(QWidget *parent)
    : QWidget(parent)
    , m_searchDelay(300)
{
    setupUi();
    connectSignals();
}

/**
 * @brief 初始化界面
 *
 * 知识点：
 * - QHBoxLayout 水平布局
 * - setPlaceholderText() 设置占位提示文本
 * - installEventFilter() 安装事件过滤器
 * - QTimer::setSingleShot(true) 单次触发定时器
 */
void SearchWidget::setupUi()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);

    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText(tr("搜索笔记..."));
    m_searchEdit->setClearButtonEnabled(false);
    m_searchEdit->installEventFilter(this);

    m_clearButton = new QPushButton(tr("清除"), this);
    m_clearButton->setVisible(false);

    m_layout->addWidget(m_searchEdit);
    m_layout->addWidget(m_clearButton);

    // 搜索延迟定时器
    m_searchTimer = new QTimer(this);
    m_searchTimer->setSingleShot(true);
}

/**
 * @brief 连接信号槽
 */
void SearchWidget::connectSignals()
{
    connect(m_searchEdit, &QLineEdit::textChanged,
            this, &SearchWidget::onTextChanged);
    connect(m_searchTimer, &QTimer::timeout,
            this, &SearchWidget::onSearchTimeout);
    connect(m_clearButton, &QPushButton::clicked,
            this, &SearchWidget::onClearClicked);
}

/**
 * @brief 获取搜索文本
 * @return 当前搜索文本
 */
QString SearchWidget::searchText() const
{
    return m_searchEdit->text();
}

/**
 * @brief 设置搜索文本
 * @param text 搜索文本
 */
void SearchWidget::setSearchText(const QString &text)
{
    m_searchEdit->setText(text);
}

/**
 * @brief 清除搜索
 */
void SearchWidget::clearSearch()
{
    m_searchEdit->clear();
    emit searchCleared();
}

/**
 * @brief 获取搜索延迟时间
 * @return 延迟毫秒数
 */
int SearchWidget::searchDelay() const
{
    return m_searchDelay;
}

/**
 * @brief 设置搜索延迟时间
 * @param msec 延迟毫秒数
 */
void SearchWidget::setSearchDelay(int msec)
{
    m_searchDelay = msec;
}

/**
 * @brief 事件过滤器
 * @param watched 被监视的对象
 * @param event 事件对象
 * @return 是否已处理事件
 *
 * 知识点：
 * - eventFilter 拦截子控件事件
 * - static_cast 类型转换
 * - Escape 键清除，Enter 键立即搜索
 */
bool SearchWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_searchEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        // Escape 键清除搜索
        if (keyEvent->key() == Qt::Key_Escape) {
            clearSearch();
            return true;
        }

        // Enter 键立即搜索
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            m_searchTimer->stop();
            emit searchRequested(m_searchEdit->text());
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

/**
 * @brief 文本变化事件处理
 * @param text 当前文本
 *
 * 实现防抖动搜索：用户停止输入后才触发搜索
 */
void SearchWidget::onTextChanged(const QString &text)
{
    // 显示/隐藏清除按钮
    m_clearButton->setVisible(!text.isEmpty());

    // 发送文本变化信号
    emit searchTextChanged(text);

    // 重启延迟搜索定时器
    m_searchTimer->stop();
    if (!text.isEmpty()) {
        m_searchTimer->start(m_searchDelay);
    }
}

/**
 * @brief 搜索延迟超时处理
 */
void SearchWidget::onSearchTimeout()
{
    emit searchRequested(m_searchEdit->text());
}

/**
 * @brief 清除按钮点击处理
 */
void SearchWidget::onClearClicked()
{
    clearSearch();
    m_searchEdit->setFocus();
}
