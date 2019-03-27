#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{

    m_name = "Tsouin Tsouin";
    m_score = 0;
    m_alive = true;

    m_backend = nullptr;
}

Player::Player(PlayerBackend *backend, QObject *parent): Player(parent)
{
    m_backend = backend;
}

void Player::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void Player::setScore(int score)
{
    if (m_score == score)
        return;

    m_score = score;
    emit scoreChanged(m_score);
}

void Player::setAlive(bool alive)
{
    if (m_alive == alive)
        return;

    m_alive = alive;
    emit aliveChanged(m_alive);
}
