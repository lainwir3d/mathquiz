#ifndef ANSWER_H
#define ANSWER_H

#include <QObject>

class Answer : public QObject
{
    Q_OBJECT
public:
    explicit Answer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ANSWER_H