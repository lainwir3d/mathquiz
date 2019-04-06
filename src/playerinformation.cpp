#include "playerinformation.h"

PlayerInformation::PlayerInformation(QObject *parent) : PlayerInformation(nullptr, parent)
{
}

PlayerInformation::PlayerInformation(PlayerBackend *backend, QObject *parent): QObject(parent)
{
    m_name = "Tsouin Tsouin";
    m_score = 0;
    m_alive = true;
}

void PlayerInformation::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void PlayerInformation::setScore(int score)
{
    if (m_score == score)
        return;

    m_score = score;
    emit scoreChanged(m_score);
}

void PlayerInformation::setAlive(bool alive)
{
    if (m_alive == alive)
        return;

    m_alive = alive;
    emit aliveChanged(m_alive);
}
