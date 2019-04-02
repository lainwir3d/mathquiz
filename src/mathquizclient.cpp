#include "mathquizclient.h"

MathQuizClient::MathQuizClient(QObject *parent) : QObject(parent)
{
    connect(this, &MathQuizClient::backendChanged, this, &MathQuizClient::backendChanged_cb);

    m_backend = nullptr;
    m_encoderdecoder = new JSONEncoderDecoder();
}



void MathQuizClient::setBackend(PlayerBackend * backend)
{
    if (m_backend == backend)
        return;

    m_backend = backend;
    emit backendChanged(m_backend);
}

void MathQuizClient::backendChanged_cb(PlayerBackend *backend)
{
    disconnect(this, SLOT(backendStateChanged_cb()));

    connect(backend, &PlayerBackend::stateChanged, this, &MathQuizClient::backendStateChanged_cb);
}

void MathQuizClient::backendStateChanged_cb(PlayerBackend::ConnectionState state)
{
    if(state == PlayerBackend::ConnectedState){
        qDebug() << __func__ << "- We are now connected!";
        //m_backend->sendMessage(m_encoderdecoder->encode());
    }
}

void MathQuizClient::setPlayer(Player * player)
{
    if (m_player == player)
        return;

    m_player = player;
    emit playerChanged(m_player);
}

