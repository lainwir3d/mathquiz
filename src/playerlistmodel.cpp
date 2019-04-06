#include "playerlistmodel.h"

PlayerListModel::PlayerListModel(QObject *parent): PlayerListModel(new QList<Player *>, parent)
{

}

PlayerListModel::PlayerListModel(QList<Player *> *players, QObject *parent):  QAbstractListModel(parent)
{
    m_roles[PlayerNameRole] = "playerName";
    m_roles[PlayerScoreRole] = "playerScore";
    m_roles[PlayerAliveRole] = "playerAlive";

    m_players = players;
}

int PlayerListModel::rowCount(const QModelIndex &parent) const
{
    return m_players->length();
}

QVariant PlayerListModel::data(const QModelIndex &index, int role) const
{
    qDebug() << QString("%1::%2 - row %3 role %4").arg(_classname).arg(__func__).arg(index.row()).arg(QString(m_roles[role]));

    if(index.isValid()){
        const Player * p = m_players->at(index.row());

        switch(role){
            case PlayerNameRole:
                return QVariant(p->infos()->name());
            case PlayerScoreRole:
                return QVariant(p->infos()->score());
            case PlayerAliveRole:
                return QVariant(p->infos()->alive());
            default:
                return QVariant();
        }
    }

    return QVariant();
}

QHash<int, QByteArray> PlayerListModel::roleNames() const
{
    return m_roles;
}

void PlayerListModel::append(Player *p)
{
    qDebug() << QString("%1::%2").arg(_classname).arg(__func__);

    if(m_players){
        QModelIndex idx = QModelIndex();
        beginInsertRows(idx, m_players->length(), m_players->length());
        m_players->append(p);
        endInsertRows();
    }
}

