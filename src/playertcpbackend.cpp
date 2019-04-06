#include "playertcpbackend.h"

PlayerTCPBackend::PlayerTCPBackend(QObject * parent): PlayerTCPBackend(new QTcpSocket(), parent)
{
}

PlayerTCPBackend::PlayerTCPBackend(QTcpSocket * s, QObject * parent): PlayerBackend(parent)
{
    m_socket = s;

    if(m_socket){
        connect(s, &QTcpSocket::stateChanged, this, &PlayerTCPBackend::socketStateChanged_cb);
        connect(s, &QTcpSocket::readyRead, this, &PlayerTCPBackend::readyRead_cb);
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
        qDebug() << QString("%1::%2 - ConnectedState").arg(_classname).arg(__func__);
        m_state = PlayerBackend::ConnectedState;
    }else if(socketState == QAbstractSocket::ConnectingState){
        qDebug() << QString("%1::%2 - ConnectingState").arg(_classname).arg(__func__);
        m_state = PlayerBackend::ConnectingState;
    }else if(socketState == QAbstractSocket::UnconnectedState){
        qDebug() << QString("%1::%2 - UnconnectedState").arg(_classname).arg(__func__);
        m_state = PlayerBackend::UnconnectedState;
    }

    emit stateChanged(m_state);
}

void PlayerTCPBackend::readyRead_cb()
{
    qDebug() << __func__ << "- readyRead!!!";
    QByteArray message_ar = m_socket->readAll();
    QString message = QString::fromUtf8(message_ar);
    qDebug() << QString("%1::%2 - Message received: \n %3").arg(_classname).arg(__func__).arg(message);

    static const QMetaMethod messageReceivedSignal = QMetaMethod::fromSignal(&PlayerTCPBackend::messageReceived);
    if(!this->isSignalConnected(messageReceivedSignal)){
        qDebug() << QString("%1::%2 - Storing message for later use.").arg(_classname).arg(__func__).arg(message);
        m_messagesStored.append(message_ar);
    }

    emit messageReceived(message_ar);
}

bool PlayerTCPBackend::sendMessage(QByteArray message)
{
    if(!m_socket){
        qDebug() << __func__ << "- Socket is nullptr";
        return false;
    }

    if(!m_socket->isValid()){
        qDebug() << __func__ << "- Invalid socket";
        return false;
    }

    qDebug() << __func__ << "Sending message!";
    int nbytes = m_socket->write(message);

    return (nbytes == message.size());
}

bool PlayerTCPBackend::messagesAvailable()
{
    return !(m_messagesStored.isEmpty());
}

QList<QByteArray> PlayerTCPBackend::messages()
{
    QList<QByteArray> m = m_messagesStored;

    m_messagesStored.clear();

    return m;
}

