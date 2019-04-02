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
        m_state = PlayerBackend::ConnectedState;
    }else if(socketState == QAbstractSocket::ConnectingState){
        m_state = PlayerBackend::ConnectingState;
    }else if(socketState == QAbstractSocket::UnconnectedState){
        m_state = PlayerBackend::UnconnectedState;
    }

    emit stateChanged(m_state);
}

bool PlayerTCPBackend::p_sendMessage(QString message)
{
    if(!m_socket){
        qDebug() << __func__ << "- Socket is nullptr";
        return false;
    }

    if(!m_socket->isValid()){
        qDebug() << __func__ << "- Invalid socket";
        return false;
    }

    m_socket->write(message.toUtf8());
}

