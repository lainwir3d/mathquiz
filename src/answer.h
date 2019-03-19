#ifndef ANSWER_H
#define ANSWER_H

#include <QObject>
#include <QString>

class Answer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString formula READ formula WRITE setFormula NOTIFY formulaChanged)
public:
    explicit Answer(QObject *parent = nullptr);

    QString formula() const { return m_formula; }

signals:

    void formulaChanged(QString formula);

public slots:
    void setFormula(QString formula);

private:
    QString m_formula;
};

#endif // ANSWER_H
