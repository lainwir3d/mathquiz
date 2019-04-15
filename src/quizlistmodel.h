#ifndef QUIZLISTMODEL_H
#define QUIZLISTMODEL_H

#include <QObject>

#include <QAbstractListModel>
#include <QList>

#include "quiz.h"

#include <QDebug>

class QuizListModel : public QAbstractListModel
{
public:
    QuizListModel();

    enum PlayerRoles {
        QuizIdRole = Qt::UserRole +1,
        QuizAuthorRole,
        QuizVersionRole,
        QuizDifficultyRole,
        QuizNumberOfQuestionRole
    };

    QuizListModel(QObject * parent = nullptr);
    QuizListModel(QMap<QString, Quiz *> * quizs, QObject * parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    void append(QString name, Quiz * q);

private:
    QMap<QString, Quiz *> * m_quizs;

    QHash<int, QByteArray> m_roles;

    QString _classname = "QuizListModel";
};

#endif // QUIZLISTMODEL_H
