#include "mathquizclient.h"

MathQuizClient::MathQuizClient(QObject *parent) : QObject(parent)
{
    m_player = nullptr;

    connect(this, &MathQuizClient::playerChanged, this, &MathQuizClient::playerChanged_cb);
}

void MathQuizClient::setPlayer(Player * playerInfos)
{
    if (m_player == playerInfos)
        return;

    m_player = playerInfos;
    emit playerChanged(m_player);
}

void MathQuizClient::connectionStateChanged_cb(PlayerBackend::ConnectionState state)
{
    qDebug() << QString("%1::%2").arg(_classname).arg(__func__);
    if(state == PlayerBackend::ConnectedState){
        Message * m = Message::newMessage(m_player->infos());

        if(!m_player->sendMessage(m)){
            qDebug() << QString("%1::%2 - Error sending player informations").arg(_classname).arg(__func__);
        }
    }
}

void MathQuizClient::playerChanged_cb(Player *p)
{
    qDebug() << QString("%1::%2").arg(_classname).arg(__func__);

    disconnect(this, SLOT(backendChanged_cb()));

    if(p){
        connect(p, &Player::connectionStateChanged, this, &MathQuizClient::connectionStateChanged_cb);
    }

}

