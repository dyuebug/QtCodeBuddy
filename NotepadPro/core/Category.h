/**
 * @file Category.h
 * @brief 分类数据模型
 *
 * 知识点：
 * - Q_OBJECT 宏和元对象系统
 * - 自定义信号
 * - JSON 序列化
 */

#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QUuid>
#include <QJsonObject>

/**
 * @class Category
 * @brief 分类数据模型类
 *
 * 用于组织和管理笔记的分类
 */
class Category : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString parentId READ parentId WRITE setParentId NOTIFY parentIdChanged)

public:
    explicit Category(QObject *parent = nullptr);
    explicit Category(const QString &name, QObject *parent = nullptr);
    ~Category() override = default;

    // Getter 方法
    QString id() const;
    QString name() const;
    QColor color() const;
    QString parentId() const;

    // Setter 方法
    void setName(const QString &name);
    void setColor(const QColor &color);
    void setParentId(const QString &parentId);

    // JSON 序列化
    QJsonObject toJson() const;
    static Category* fromJson(const QJsonObject &json, QObject *parent = nullptr);

signals:
    void nameChanged(const QString &name);
    void colorChanged(const QColor &color);
    void parentIdChanged(const QString &parentId);
    void categoryModified();

private:
    QString m_id;
    QString m_name;
    QColor m_color;
    QString m_parentId;
};

#endif // CATEGORY_H
