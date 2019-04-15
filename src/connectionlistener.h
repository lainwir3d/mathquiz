#ifndef CONNECTIONLISTENER_H
#define CONNECTIONLISTENER_H

#include <QObject>
#include <QDebug>
#include <QQmlEngine>

#include "player.h"

class ConnectionListener : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool listen READ listen WRITE setListen NOTIFY listenChanged)
    Q_PROPERTY(QString listeningDetails READ listeningDetails NOTIFY listeningDetailsChanged)
public:
    explicit ConnectionListener(QObject *parent = nullptr);

    bool startListening() { return false; }
    bool stopListening() { return true; }

    virtual bool listen() const { return false; }

    QString name() const { return QString("Generic"); }

    virtual QString listeningDetails() const { return ""; }

private slots:
    void newConnectionCallback(Player * p);

signals:
    void newConnection(Player *p);
    void listeningDetailsChanged(QString listeningDetails);

    void listenChanged(bool listen);

public slots:
    virtual void setListen(bool listen) { }

private:

bool m_listen;
};

QML_DECLARE_TYPE(ConnectionListener *)

#endif // CONNECTIONLISTENER_H
