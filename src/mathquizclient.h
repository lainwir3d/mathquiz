#ifndef MATHQUIZCLIENT_H
#define MATHQUIZCLIENT_H

#include <QDebug>

#include <QObject>

#include "message.h"

#include "player.h"
#include "playerbackend.h"

class MathQuizClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Player * player READ player WRITE setPlayer NOTIFY playerChanged)
public:
    explicit MathQuizClient(QObject *parent = nullptr);

    Player * player() const { return m_player; }

signals:
    void playerChanged(Player * player);

public slots:
    void setPlayer(Player * player);

private slots:
    void connectionStateChanged_cb(PlayerBackend::ConnectionState state);
    void playerChanged_cb(Player * p);

private:
    Player * m_player;

    QString _classname = "MathQuizClient";
};

#endif // MATHQUIZCLIENT_H
