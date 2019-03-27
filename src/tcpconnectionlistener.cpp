#include "tcpconnectionlistener.h"

TcpConnectionListener::TcpConnectionListener()
{
    m_tcpServer = new QTcpServer();

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

    Player * p = new Player();

    emit newConnection(p);
}
