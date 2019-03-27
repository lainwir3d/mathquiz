#ifndef CONNECTIONLISTENER_H
#define CONNECTIONLISTENER_H

#include <QObject>
#include <QDebug>

#include "player.h"

class ConnectionListener : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionListener(QObject *parent = nullptr);

    bool startListening() { return false; }
    bool stopListening() { return true; }

    QString name() const { return QString("Generic"); }

private slots:
    void newConnectionCallback(Player * p);

signals:
    void newConnection(Player *p);

public slots:
};

#endif // CONNECTIONLISTENER_H
