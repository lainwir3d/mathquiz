#ifndef PLAYERTCPBACKEND_H
#define PLAYERTCPBACKEND_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QAbstractSocket>

#include "playerbackend.h"

class PlayerTCPBackend : public PlayerBackend
{
    Q_OBJECT
    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)

public:
    PlayerTCPBackend();
    PlayerTCPBackend(QTcpSocket * s);

    QString ip() const { return m_ip; }
    int port() const { return m_port; }

public slots:
    void setIp(QString ip);
    void setPort(int port);
    void connectToServer();

signals:
    void ipChanged(QString ip);

    void portChanged(int port);

private slots:
    void socketStateChanged_cb(QAbstractSocket::SocketState socketState);

private:
    QTcpSocket * m_socket;
    QString m_ip;
    int m_port;
};

#endif // PLAYERTCPBACKEND_H
