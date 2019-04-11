#include "mathquizserver.h"

MathQuizServer::MathQuizServer(QObject *parent) : QObject(parent)
{
    m_playerListModel = new PlayerListModel(this);


    QuestionBase::parseStandardFolders(&m_questionBases);
    Quiz::parseStandardFolders(&m_quizs, m_questionBases);
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

    p->infos()->setAlive(true);
    p->infos()->setScore(0);

    m_playerListModel->append(p);

    connect(p, &Player::playerInformationReceived, [this, p](PlayerInformation * infos){ this->playerInformationReceived(p, infos); });
}

void MathQuizServer::playerInformationReceived(Player *p, PlayerInformation *info)
{
    qDebug() << QString("%1::%2 - Received player name: %3").arg(_classname).arg(__func__).arg(info->name());

    // We only take the name from the object.
    p->infos()->setName(info->name());

    info->deleteLater();
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

