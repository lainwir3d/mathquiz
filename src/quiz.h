#ifndef QUIZ_H
#define QUIZ_H

#include <QObject>

#include <QList>

#include "question.h"
#include "questionbase.h"

class Quiz : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged)
    Q_PROPERTY(int difficulty READ difficulty WRITE setDifficulty NOTIFY difficultyChanged)
    Q_PROPERTY(int questionNumbers READ questionNumbers NOTIFY questionNumbersChanged)
public:
    explicit Quiz(QObject *parent = nullptr);

    QString id() const { return m_id; }
    QString author() const { return m_author; }
    QString version() const { return m_version; }

    int length() { return m_questionList.length(); }
    int size() { return m_questionList.size(); }
    Question * at(int i) { return m_questionList.at(i); }

    static QString _classname;
    static bool parseStandardFolders(QMap<QString, Quiz *> ** quizs, QMap<QString, QuestionBase *> * base);
    static Quiz * decodeUTF8Json(QByteArray * barray, QMap<QString, QuestionBase *> * base);

    bool appendQuestion(Question * q);

    int difficulty() const { return m_difficulty; }
    int questionNumbers() const { return m_questionList.length(); }

signals:
    void idChanged(QString id);
    void authorChanged(QString author);
    void versionChanged(QString version);
    void difficultyChanged(int difficulty);
    void questionNumbersChanged(int questionNumbers);

public slots:
    void setId(QString id);
    void setAuthor(QString author);
    void setVersion(QString version);
    void setDifficulty(int difficulty);

private:
    QString m_id;
    QString m_author;
    QString m_version;
    int m_difficulty;

    QList<Question *> m_questionList;
};

#endif // QUIZ_H
