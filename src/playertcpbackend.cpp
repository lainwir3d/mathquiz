#include "playertcpbackend.h"

PlayerTCPBackend::PlayerTCPBackend()
{
    m_socket = nullptr;
}

PlayerTCPBackend::PlayerTCPBackend(QTcpSocket * s)
{
    m_socket = s;
}
