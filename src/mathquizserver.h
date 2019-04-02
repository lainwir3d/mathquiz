#ifndef MATHQUIZSERVER_H
#define MATHQUIZSERVER_H

#include <QObject>
#include <QVariantList>
#include <QQmlListProperty>

#include "connectionlistener.h"
#include "tcpconnectionlistener.h"

#include <QDebug>

class MathQuizServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<ConnectionListener> listeners READ listeners)
public:
    explicit MathQuizServer(QObject *parent = nullptr);

    enum ServerMode {
        NoMode = 0,
        SingleGame = 1,
        MultiGame = 2
    };
    Q_ENUM(ServerMode)


    QQmlListProperty<ConnectionListener> listeners() { return QQmlListProperty<ConnectionListener>(this, this, &MathQuizServer::appendListener, &MathQuizServer::listenerCount, &MathQuizServer::listener, &MathQuizServer::clearListener); }
    void appendListener(ConnectionListener *l);
    int listenerCount();
    ConnectionListener* listener(int idx);
    void clearListener();

signals:

public slots:

private slots:
    void newPlayerConnectionCallback(Player * p);

private:
    QList<ConnectionListener *> m_listeners;

    /*
     * Static listener accessor
     */
    static void appendListener(QQmlListProperty<ConnectionListener>*, ConnectionListener*);
    static int listenerCount(QQmlListProperty<ConnectionListener>*);
    static ConnectionListener* listener(QQmlListProperty<ConnectionListener>*, int);
    static void clearListener(QQmlListProperty<ConnectionListener>*);
};

#endif // MATHQUIZSERVER_H
