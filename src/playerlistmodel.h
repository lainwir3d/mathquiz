#ifndef PLAYERLISTMODEL_H
#define PLAYERLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "player.h"

class PlayerListModel : public QAbstractListModel
{
public:
    enum PlayerRoles {
        PlayerNameRole = Qt::UserRole +1,
        PlayerScoreRole,
        PlayerAliveRole
    };

    PlayerListModel(QObject * parent = nullptr);
    PlayerListModel(QList<Player *> * players, QObject * parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    void append(Player * p);

private:
    QList<Player *> * m_players;

    QHash<int, QByteArray> m_roles;

    QString _classname = "PlayerListModel";
};

#endif // PLAYERLISTMODEL_H
