#include "quizlistmodel.h"

QuizListModel::QuizListModel()
{

}
#include "playerlistmodel.h"

QuizListModel::QuizListModel(QObject *parent): QuizListModel(new QMap<QString, Quiz *>, parent)
{

}

QuizListModel::QuizListModel(QMap<QString, Quiz *> * quizs, QObject *parent):  QAbstractListModel(parent)
{
    m_roles[QuizIdRole] = "quizId";
    m_roles[QuizAuthorRole] = "quizAuthor";
    m_roles[QuizVersionRole] = "quizVersion";
    m_roles[QuizDifficultyRole] = "quizDifficulty";
    m_roles[QuizNumberOfQuestionRole] = "quizNumberOfQuestion";

    m_quizs = quizs;
}

int QuizListModel::rowCount(const QModelIndex &parent) const
{
    return m_quizs->size();
}

QVariant QuizListModel::data(const QModelIndex &index, int role) const
{
    qDebug() << QString("%1::%2 - row %3 role %4").arg(_classname).arg(__func__).arg(index.row()).arg(QString(m_roles[role]));

    if(index.isValid()){
        QList<QString> keys = m_quizs->keys();
        QString key = keys.at(index.row());
        const Quiz * q = m_quizs->value(key);

        switch(role){
            case QuizIdRole:
                return QVariant(q->id());
            case QuizAuthorRole:
                return QVariant(q->author());
            case QuizVersionRole:
                return QVariant(q->version());
            case QuizDifficultyRole:
                return QVariant(q->difficulty());
            case QuizNumberOfQuestionRole:
                return QVariant(q->questionNumbers());
            default:
                return QVariant();
        }
    }

    return QVariant();
}

QHash<int, QByteArray> QuizListModel::roleNames() const
{
    return m_roles;
}

void QuizListModel::append(QString name, Quiz *q)
{
    qDebug() << QString("%1::%2").arg(_classname).arg(__func__);

    if(m_quizs){
        QList<QString> keys = m_quizs->keys();
        keys.append(name);
        keys.sort();

        int i = keys.indexOf(name);

        QModelIndex idx = QModelIndex();
        beginInsertRows(idx, i, i+1);
        m_quizs->insert(name, q);
        endInsertRows();
    }
}

