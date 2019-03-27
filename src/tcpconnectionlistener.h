#ifndef TCPCONNECTIONLISTENER_H
#define TCPCONNECTIONLISTENER_H

#include <QObject>
#include <QTcpServer>

#include "connectionlistener.h"
#include "player.h"

class TcpConnectionListener : public ConnectionListener
{
    Q_OBJECT
public:
    TcpConnectionListener();

    bool startListening();
    bool stopListening();

    QString name() const { return QString("TCPListener"); }

private slots:
    void newTCPConnectionCallback();

private:
    QTcpServer * m_tcpServer;

};

#endif // TCPCONNECTIONLISTENER_H
