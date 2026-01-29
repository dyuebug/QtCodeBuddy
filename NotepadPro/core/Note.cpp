/**
 * @file Note.cpp
 * @brief 笔记数据模型实现
 *
 * 知识点：
 * - QUuid 生成全局唯一标识符
 * - QDateTime 日期时间处理
 * - QJsonObject JSON 序列化/反序列化
 * - Q_PROPERTY 属性系统的 getter/setter 实现
 * - 信号发射通知属性变化
 */

#include "Note.h"
#include <QJsonObject>
#include <QRegularExpression>

/**
 * @brief 默认构造函数
 * @param parent 父对象指针
 *
 * 知识点：
 * - QUuid::createUuid() 生成 UUID
 * - QUuid::WithoutBraces 去除花括号格式
 * - 初始化列表设置成员变量
 */
Note::Note(QObject *parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_title(tr("新建笔记"))
    , m_createdAt(QDateTime::currentDateTime())
    , m_updatedAt(m_createdAt)
    , m_isPinned(false)
{
}

/**
 * @brief 带参数构造函数
 * @param title 笔记标题
 * @param content 笔记内容
 * @param parent 父对象指针
 */
Note::Note(const QString &title, const QString &content, QObject *parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_title(title)
    , m_content(content)
    , m_createdAt(QDateTime::currentDateTime())
    , m_updatedAt(m_createdAt)
    , m_isPinned(false)
{
}

// ========== Getter 方法 ==========

QString Note::id() const { return m_id; }
QString Note::title() const { return m_title; }
QString Note::content() const { return m_content; }
QString Note::categoryId() const { return m_categoryId; }
QDateTime Note::createdAt() const { return m_createdAt; }
QDateTime Note::updatedAt() const { return m_updatedAt; }
bool Note::isPinned() const { return m_isPinned; }

// ========== Setter 方法 ==========

/**
 * @brief 设置笔记标题
 * @param title 新标题
 *
 * 知识点：
 * - 属性变化检测：只有值真正改变时才发出信号
 * - emit 发出信号通知观察者
 */
void Note::setTitle(const QString &title)
{
    if (m_title != title) {
        m_title = title;
        updateTimestamp();
        emit titleChanged(m_title);
        emit noteModified();
    }
}

/**
 * @brief 设置笔记内容
 * @param content 新内容
 */
void Note::setContent(const QString &content)
{
    if (m_content != content) {
        m_content = content;
        updateTimestamp();
        emit contentChanged(m_content);
        emit noteModified();
    }
}

/**
 * @brief 设置笔记所属分类ID
 * @param categoryId 分类ID
 *
 * 这是笔记与分类关联的关键方法
 */
void Note::setCategoryId(const QString &categoryId)
{
    if (m_categoryId != categoryId) {
        m_categoryId = categoryId;
        updateTimestamp();
        emit categoryIdChanged(m_categoryId);
        emit noteModified();
    }
}

/**
 * @brief 设置置顶状态
 * @param pinned 是否置顶
 */
void Note::setPinned(bool pinned)
{
    if (m_isPinned != pinned) {
        m_isPinned = pinned;
        updateTimestamp();
        emit isPinnedChanged(m_isPinned);
        emit noteModified();
    }
}

/**
 * @brief 序列化为 JSON 对象
 * @return JSON 对象
 *
 * 知识点：
 * - QJsonObject 键值对存储
 * - QDateTime::toString(Qt::ISODate) ISO 格式日期字符串
 */
QJsonObject Note::toJson() const
{
    QJsonObject json;
    json["id"] = m_id;
    json["title"] = m_title;
    json["content"] = m_content;
    json["categoryId"] = m_categoryId;
    json["createdAt"] = m_createdAt.toString(Qt::ISODate);
    json["updatedAt"] = m_updatedAt.toString(Qt::ISODate);
    json["isPinned"] = m_isPinned;
    return json;
}

/**
 * @brief 从 JSON 对象反序列化
 * @param json JSON 对象
 * @param parent 父对象指针
 * @return 新创建的笔记对象
 *
 * 知识点：
 * - 静态工厂方法模式
 * - QDateTime::fromString() 解析日期字符串
 */
Note* Note::fromJson(const QJsonObject &json, QObject *parent)
{
    Note *note = new Note(parent);
    note->m_id = json["id"].toString();
    note->m_title = json["title"].toString();
    note->m_content = json["content"].toString();
    note->m_categoryId = json["categoryId"].toString();
    note->m_createdAt = QDateTime::fromString(json["createdAt"].toString(), Qt::ISODate);
    note->m_updatedAt = QDateTime::fromString(json["updatedAt"].toString(), Qt::ISODate);
    note->m_isPinned = json["isPinned"].toBool();
    return note;
}

/**
 * @brief 获取笔记内容预览
 * @param maxLength 最大长度
 * @return 纯文本预览
 *
 * 知识点：
 * - QRegularExpression 正则表达式移除 HTML 标签
 * - QString::simplified() 合并空白字符
 */
QString Note::preview(int maxLength) const
{
    // 移除 HTML 标签，获取纯文本预览
    QString plainText = m_content;
    plainText.remove(QRegularExpression("<[^>]*>"));
    plainText = plainText.simplified();

    if (plainText.length() > maxLength) {
        return plainText.left(maxLength) + "...";
    }
    return plainText;
}

/**
 * @brief 检查笔记是否包含指定文本
 * @param text 搜索文本
 * @param cs 大小写敏感性
 * @return 包含返回 true
 */
bool Note::containsText(const QString &text, Qt::CaseSensitivity cs) const
{
    return m_title.contains(text, cs) || m_content.contains(text, cs);
}

/**
 * @brief 更新修改时间戳
 */
void Note::updateTimestamp()
{
    m_updatedAt = QDateTime::currentDateTime();
    emit updatedAtChanged(m_updatedAt);
}
