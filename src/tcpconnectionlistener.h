#ifndef TCPCONNECTIONLISTENER_H
#define TCPCONNECTIONLISTENER_H

#include <QObject>
#include <QTcpServer>
#include <QNetworkInterface>

#include "connectionlistener.h"
#include "playertcpbackend.h"
#include "playerinformation.h"
#include "jsonencoderdecoder.h"

class TcpConnectionListener : public ConnectionListener
{
    Q_OBJECT
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
public:
    TcpConnectionListener();

    Q_INVOKABLE bool startListening();
    Q_INVOKABLE bool stopListening();

    QString name() const { return QString("TCPListener"); }

    int port() const { return m_port; }

    bool listen() const { return m_listen; }

    QString listeningDetails() const { return m_listeningDetails; }

public slots:
    void setPort(int port);
    void setListen(bool listen);

signals:
    void portChanged(int port);

private slots:
    void newTCPConnectionCallback();

private:
    QTcpServer * m_tcpServer;

    int m_port;
    bool m_listen;
    QString m_listeningDetails;
};

#endif // TCPCONNECTIONLISTENER_H
