#include "player.h"

Player::Player(QObject *parent) : Player(new PlayerInformation(), nullptr, nullptr, parent)
{

}

Player::Player(PlayerInformation *infos, PlayerBackend *backend, EncoderDecoder *encDec, QObject *parent): QObject(parent)
{
    m_infos = infos;
    m_backend = backend;
    m_encoderDecoder = encDec;

    connect(this, &Player::backendChanged, this, &Player::backendChanged_cb);

    backendChanged_cb(m_backend);
}

bool Player::sendMessage(Message *m)
{
    if(!m_encoderDecoder) return false;

    QByteArray data = m_encoderDecoder->encode(m);
    if(data.isEmpty()) return false;

    return m_backend->sendMessage(data);
}

void Player::setInfos(PlayerInformation *infos)
{
    if (m_infos == infos)
        return;

    m_infos = infos;
    emit infosChanged(m_infos);
}

void Player::setBackend(PlayerBackend *backend)
{
    if (m_backend == backend)
        return;

    m_backend = backend;
    emit backendChanged(m_backend);
}

void Player::setEncoderDecoder(EncoderDecoder *encoderDecoder)
{
    if (m_encoderDecoder == encoderDecoder)
        return;

    m_encoderDecoder = encoderDecoder;
    emit encoderDecoderChanged(m_encoderDecoder);
}

void Player::backendChanged_cb(PlayerBackend *backend)
{
    disconnect(this, SLOT(encodedMessageReceived()));

    if(m_backend){
        connect(m_backend, &PlayerBackend::stateChanged, this, &Player::connectionStateChanged);
        connect(m_backend, &PlayerBackend::messageReceived, this, &Player::encodedMessageReceived);
    }
}

void Player::encodedMessageReceived(QByteArray message)
{
    qDebug() << QString("%1::%2 - Encoded message received").arg(_className).arg(__func__);


}
