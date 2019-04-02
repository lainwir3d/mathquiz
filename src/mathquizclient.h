#ifndef MATHQUIZCLIENT_H
#define MATHQUIZCLIENT_H

#include <QDebug>

#include <QObject>

#include "playerbackend.h"
#include "encoderdecoder.h"
#include "jsonencoderdecoder.h"
#include "player.h"

class MathQuizClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PlayerBackend * backend READ backend WRITE setBackend NOTIFY backendChanged)
    Q_PROPERTY(Player * player READ player WRITE setPlayer NOTIFY playerChanged)
public:
    explicit MathQuizClient(QObject *parent = nullptr);

    PlayerBackend * backend() const { return m_backend; }

    Player * player() const { return m_player; }

signals:
    void backendChanged(PlayerBackend * backend);

    void playerChanged(Player * player);

public slots:
    void setBackend(PlayerBackend * backend);
    void setPlayer(Player * player);

private slots:
    void backendChanged_cb(PlayerBackend * backend);
    void backendStateChanged_cb(PlayerBackend::ConnectionState state);


private:
    PlayerBackend * m_backend;
    EncoderDecoder * m_encoderdecoder;
    Player * m_player;
};

#endif // MATHQUIZCLIENT_H
