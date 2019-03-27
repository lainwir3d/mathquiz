#ifndef PLAYERTCPBACKEND_H
#define PLAYERTCPBACKEND_H

#include <QObject>
#include <QTcpSocket>

#include "playerbackend.h"

class PlayerTCPBackend : public PlayerBackend
{
public:
    PlayerTCPBackend();
    PlayerTCPBackend(QTcpSocket * s);

private:
    QTcpSocket * m_socket;
};

#endif // PLAYERTCPBACKEND_H
