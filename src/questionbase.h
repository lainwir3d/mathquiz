#ifndef QUESTIONBASE_H
#define QUESTIONBASE_H

#include <QObject>

#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QCoreApplication>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "question.h"

class QuestionBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged)
public:
    explicit QuestionBase(QObject *parent = nullptr);

    int length() { return m_questionList.length(); }
    int size() { return m_questionList.size(); }
    Question * at(int i) { return m_questionList.at(i); }

    static QString _classname;
    static bool parseStandardFolders(QMap<QString, QuestionBase *> ** base);
    static QuestionBase * decodeUTF8Json(QByteArray * barray);

    QString id() const { return m_id; }
    QString author() const { return m_author; }
    QString version() const { return m_version; }
    bool appendQuestion(Question * q);

signals:
    void idChanged(QString id);
    void authorChanged(QString author);
    void versionChanged(QString version);

public slots:
    void setId(QString id);
    void setAuthor(QString author);
    void setVersion(QString version);

private:
    QList<Question *> m_questionList;

    QString m_id;
    QString m_author;
    QString m_version;
};

#endif // QUESTIONBASE_H
