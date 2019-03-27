#include "connectionlistener.h"

ConnectionListener::ConnectionListener(QObject *parent) : QObject(parent)
{
    connect(this, &ConnectionListener::newConnection, this, &ConnectionListener::newConnectionCallback);
}

void ConnectionListener::newConnectionCallback(Player *p)
{
    qDebug() << __func__ << "- New connection on backend %1 from %2.";
}
