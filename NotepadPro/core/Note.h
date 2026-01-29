/**
 * @file Note.h
 * @brief 笔记数据模型
 *
 * 知识点：
 * - Q_OBJECT 宏和元对象系统
 * - Q_PROPERTY 属性系统
 * - 自定义信号
 * - QDateTime 时间处理
 */

#ifndef NOTE_H
#define NOTE_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QUuid>
#include <QJsonObject>

/**
 * @class Note
 * @brief 笔记数据模型类
 *
 * 存储单个笔记的所有信息，包括标题、内容、分类、时间戳等
 */
class Note : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QString categoryId READ categoryId WRITE setCategoryId NOTIFY categoryIdChanged)
    Q_PROPERTY(QDateTime createdAt READ createdAt CONSTANT)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt NOTIFY updatedAtChanged)
    Q_PROPERTY(bool isPinned READ isPinned WRITE setPinned NOTIFY isPinnedChanged)

public:
    explicit Note(QObject *parent = nullptr);
    explicit Note(const QString &title, const QString &content = QString(),
                  QObject *parent = nullptr);
    ~Note() override = default;

    // Getter 方法
    QString id() const;
    QString title() const;
    QString content() const;
    QString categoryId() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    bool isPinned() const;

    // Setter 方法
    void setTitle(const QString &title);
    void setContent(const QString &content);
    void setCategoryId(const QString &categoryId);
    void setPinned(bool pinned);

    // JSON 序列化
    QJsonObject toJson() const;
    static Note* fromJson(const QJsonObject &json, QObject *parent = nullptr);

    // 辅助方法
    QString preview(int maxLength = 100) const;
    bool containsText(const QString &text, Qt::CaseSensitivity cs = Qt::CaseInsensitive) const;

signals:
    void titleChanged(const QString &title);
    void contentChanged(const QString &content);
    void categoryIdChanged(const QString &categoryId);
    void updatedAtChanged(const QDateTime &updatedAt);
    void isPinnedChanged(bool isPinned);
    void noteModified();

private:
    void updateTimestamp();

    QString m_id;
    QString m_title;
    QString m_content;
    QString m_categoryId;
    QDateTime m_createdAt;
    QDateTime m_updatedAt;
    bool m_isPinned;
};

#endif // NOTE_H
