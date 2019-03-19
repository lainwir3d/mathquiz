#ifndef QUESTIONGROUP_H
#define QUESTIONGROUP_H

#include <QObject>

class QuestionGroup : public QObject
{
    Q_OBJECT
public:
    explicit QuestionGroup(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QUESTIONGROUP_H