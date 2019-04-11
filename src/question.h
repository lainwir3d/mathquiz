#ifndef QUESTION_H
#define QUESTION_H

#include <QObject>
#include <QString>
#include <QDebug>

#include "answer.h"

class Question : public QObject
{
 Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString question READ question WRITE setQuestion NOTIFY questionChanged)
    Q_PROPERTY(QString imageUri READ imageUri WRITE setImageUri NOTIFY imageUriChanged)
    Q_PROPERTY(QString formula READ formula WRITE setFormula NOTIFY formulaChanged)
    Q_PROPERTY(QString group READ group WRITE setGroup NOTIFY groupChanged)
    Q_PROPERTY(int timeLimit_ms READ timeLimit_ms WRITE setTimeLimit_ms NOTIFY timeLimit_msChanged)
    Q_PROPERTY(int difficulty READ difficulty WRITE setDifficulty NOTIFY difficultyChanged)
public:
    explicit Question(QObject *parent = nullptr);

    QString id() const { return m_id; }
    QString question() const { return m_question; }
    QString imageUri() const { return m_imageUri; }
    QString formula() const { return m_formula; }
    QString group() const { return m_group; }
    int timeLimit_ms() const { return m_timeLimit_ms; }
    int difficulty() const { return m_difficulty; }

    void appendAnswer(Answer * answer);
    bool checkAnswer(Answer *answer);


signals:
    void idChanged(QString id);
    void questionChanged(QString question);
    void imageUriChanged(QString imageUri);
    void formulaChanged(QString formula);

    void timeLimit_msChanged(int timeLimit_ms);

    void difficultyChanged(int difficulty);
    void groupChanged(QString group);

public slots:
    void setQuestion(QString question);
    void setId(QString id);
    void setImageUri(QString imageUri);
    void setFormula(QString formula);

    void setReadOnly(bool readOnly);

    void setTimeLimit_ms(int timeLimit_ms);
    void setDifficulty(int difficulty);

    void setGroup(QString group);

private:
    QString m_id;
    QString m_question;
    QString m_imageUri;
    QString m_formula;

    bool m_readOnly;
    int m_timeLimit_ms;
    int m_difficulty;

    QList<Answer *> m_answers;
    QString m_group;
};

#endif // QUESTION_H
