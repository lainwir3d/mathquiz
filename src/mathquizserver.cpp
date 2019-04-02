#include "mathquizserver.h"

MathQuizServer::MathQuizServer(QObject *parent) : QObject(parent)
{
}

void MathQuizServer::appendListener(ConnectionListener *l)
{
    m_listeners.append(l);

    connect(l, &ConnectionListener::newConnection, this, &MathQuizServer::newPlayerConnectionCallback);
}

int MathQuizServer::listenerCount()
{
    return m_listeners.count();
}

ConnectionListener *MathQuizServer::listener(int idx)
{
    return m_listeners.at(idx);
}

void MathQuizServer::clearListener()
{
    m_listeners.clear();
}

void MathQuizServer::newPlayerConnectionCallback(Player *p)
{
    qDebug() << QString("%1::%2").arg(metaObject()->className()).arg(__func__) << "- New connection from player";


}

void MathQuizServer::appendListener(QQmlListProperty<ConnectionListener> *list, ConnectionListener *p)
{
    reinterpret_cast< MathQuizServer* >(list->data)->appendListener(p);
}

int MathQuizServer::listenerCount(QQmlListProperty<ConnectionListener> * list)
{
    return reinterpret_cast< MathQuizServer* >(list->data)->listenerCount();
}

ConnectionListener *MathQuizServer::listener(QQmlListProperty<ConnectionListener> * list, int idx)
{
    return reinterpret_cast< MathQuizServer* >(list->data)->listener(idx);
}

void MathQuizServer::clearListener(QQmlListProperty<ConnectionListener> *list )
{
    reinterpret_cast< MathQuizServer* >(list->data)->clearListener();
}

