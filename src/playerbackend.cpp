#include "playerbackend.h"

PlayerBackend::PlayerBackend(QObject *parent) : QObject(parent)
{
    m_state = UnconnectedState;
}

bool PlayerBackend::sendMessage(QString message)
{
    return p_sendMessage(message);
}

void PlayerBackend::setState(ConnectionState state)
{
    if (m_state == state)
        return;

    m_state = state;
    emit stateChanged(m_state);
}
