#include "playertcpbackend.h"

PlayerTCPBackend::PlayerTCPBackend(): PlayerTCPBackend(new QTcpSocket())
{
}

PlayerTCPBackend::PlayerTCPBackend(QTcpSocket * s)
{
    m_socket = s;

    if(m_socket){
        connect(s, &QTcpSocket::stateChanged, this, &PlayerTCPBackend::socketStateChanged_cb);
    }
}

void PlayerTCPBackend::setIp(QString ip)
{
    if (m_ip == ip)
        return;

    m_ip = ip;
    emit ipChanged(m_ip);
}

void PlayerTCPBackend::setPort(int port)
{
    if (m_port == port)
        return;

    m_port = port;
    emit portChanged(m_port);
}

void PlayerTCPBackend::connectToServer()
{
    if(!m_socket){
        qDebug() << "Invalid socket";
        return;
    }

    // TODO: verify ip validity, verify port validity

    qDebug() << QString("Connecting to ip %1 on port %2").arg(m_ip).arg(m_port);

    m_socket->connectToHost(m_ip, m_port);
}

void PlayerTCPBackend::socketStateChanged_cb(QAbstractSocket::SocketState socketState)
{
    if(socketState == QAbstractSocket::ConnectedState){
        qDebug() << __func__ << "- We are now connected!";
    }
}

