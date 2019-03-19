#ifndef QUESTIONGROUP_H
#define QUESTIONGROUP_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>

#include "question.h"

class QuestionGroup : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit QuestionGroup(QObject *parent = nullptr);

    QString name() const { return m_name; }

    bool insertQuestion(Question * q);
    bool removeQuestion(Question * q);
    bool removeQuestion(QString id);

signals:
    void nameChanged(QString name);

public slots:
    void setName(QString name);

private:
    QMap<QString, Question *> m_questionsMap;
    QString m_name;
};

#endif // QUESTIONGROUP_H
