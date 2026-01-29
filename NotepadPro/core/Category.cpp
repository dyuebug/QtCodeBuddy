/**
 * @file Category.cpp
 * @brief 分类数据模型实现
 *
 * 知识点：
 * - QUuid 生成唯一标识符
 * - QColor 颜色处理
 * - QJsonObject JSON 序列化
 * - 信号槽通知属性变化
 */

#include "Category.h"

/**
 * @brief 默认构造函数
 * @param parent 父对象指针
 */
Category::Category(QObject *parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_name(tr("新建分类"))
    , m_color(Qt::blue)
{
}

/**
 * @brief 带参数构造函数
 * @param name 分类名称
 * @param parent 父对象指针
 */
Category::Category(const QString &name, QObject *parent)
    : QObject(parent)
    , m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_name(name)
    , m_color(Qt::blue)
{
}

// ========== Getter 方法 ==========

QString Category::id() const { return m_id; }
QString Category::name() const { return m_name; }
QColor Category::color() const { return m_color; }
QString Category::parentId() const { return m_parentId; }

// ========== Setter 方法 ==========

/**
 * @brief 设置分类名称
 * @param name 新名称
 */
void Category::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged(m_name);
        emit categoryModified();
    }
}

/**
 * @brief 设置分类颜色
 * @param color 新颜色
 */
void Category::setColor(const QColor &color)
{
    if (m_color != color) {
        m_color = color;
        emit colorChanged(m_color);
        emit categoryModified();
    }
}

/**
 * @brief 设置父分类ID
 * @param parentId 父分类ID
 */
void Category::setParentId(const QString &parentId)
{
    if (m_parentId != parentId) {
        m_parentId = parentId;
        emit parentIdChanged(m_parentId);
        emit categoryModified();
    }
}

/**
 * @brief 序列化为 JSON 对象
 * @return JSON 对象
 *
 * 知识点：
 * - QColor::name() 返回 "#RRGGBB" 格式字符串
 */
QJsonObject Category::toJson() const
{
    QJsonObject json;
    json["id"] = m_id;
    json["name"] = m_name;
    json["color"] = m_color.name();
    json["parentId"] = m_parentId;
    return json;
}

/**
 * @brief 从 JSON 对象反序列化
 * @param json JSON 对象
 * @param parent 父对象指针
 * @return 新创建的分类对象
 */
Category* Category::fromJson(const QJsonObject &json, QObject *parent)
{
    Category *category = new Category(parent);
    category->m_id = json["id"].toString();
    category->m_name = json["name"].toString();
    category->m_color = QColor(json["color"].toString());
    category->m_parentId = json["parentId"].toString();
    return category;
}
