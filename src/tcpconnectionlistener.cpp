#include "tcpconnectionlistener.h"

TcpConnectionListener::TcpConnectionListener()
{
    m_tcpServer = new QTcpServer();

    m_port = 42000;
    m_listen = false;

    connect(m_tcpServer, &QTcpServer::newConnection, this, &TcpConnectionListener::newTCPConnectionCallback);
}

bool TcpConnectionListener::startListening()
{
    if(!m_tcpServer) return false;
    else if(m_tcpServer->isListening()){
        qDebug() << __func__ << "- We are already listening to incoming connections.";
        return true;
    }

    return m_tcpServer->listen(QHostAddress::Any, 42000);
}

bool TcpConnectionListener::stopListening()
{
    m_tcpServer->close();
    return true;
}

void TcpConnectionListener::newTCPConnectionCallback()
{
    qDebug() << __func__ << "- New TCP connection! Waiting for info.";

    if(!m_tcpServer->hasPendingConnections()){
        qDebug() << __func__ << "- No pending connection, weird huh?";
        return;
    }

    QTcpSocket * s = m_tcpServer->nextPendingConnection();

    if(!s){
        qDebug() << __func__ << "- Returned socket is nullptr, weird huh?";
        return;
    }

    Player * p = new Player(new PlayerTCPBackend(s));

    emit newConnection(p);
}

void TcpConnectionListener::setPort(int port)
{
    if (m_port == port)
        return;

    m_port = port;
    emit portChanged(m_port);
}

void TcpConnectionListener::setListen(bool listen)
{
    if (m_listen == listen)
        return;

    if(listen){
        if(!startListening()) return;
    }else{
        if(!stopListening()) return;
    }

    m_listen = listen;
    emit listenChanged(m_listen);
}

