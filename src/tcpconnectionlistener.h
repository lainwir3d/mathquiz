#ifndef TCPCONNECTIONLISTENER_H
#define TCPCONNECTIONLISTENER_H

#include <QObject>
#include <QTcpServer>

#include "connectionlistener.h"
#include "player.h"

class TcpConnectionListener : public ConnectionListener
{
    Q_OBJECT
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(bool listen READ listen WRITE setListen NOTIFY listenChanged)
public:
    TcpConnectionListener();

    Q_INVOKABLE bool startListening();
    Q_INVOKABLE bool stopListening();

    QString name() const { return QString("TCPListener"); }

    int port() const { return m_port; }

    bool listen() const { return m_listen; }

public slots:
    void setPort(int port);
    void setListen(bool listen);

signals:
    void portChanged(int port);
    void listenChanged(bool listen);

private slots:
    void newTCPConnectionCallback();

private:
    QTcpServer * m_tcpServer;

    int m_port;
    bool m_listen;
};

#endif // TCPCONNECTIONLISTENER_H
