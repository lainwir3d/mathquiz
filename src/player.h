#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>

#include "playerbackend.h"

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int score READ score NOTIFY scoreChanged)
    Q_PROPERTY(bool alive READ alive NOTIFY aliveChanged)

public:
    explicit Player(QObject *parent = nullptr);
    Player(PlayerBackend * backend, QObject *parent = nullptr);

    QString name() const { return m_name; }
    int score() const { return m_score; }
    bool alive() const { return m_alive; }

signals:
    void nameChanged(QString name);
    void scoreChanged(int score);
    void aliveChanged(bool alive);

public slots:
    void setName(QString name);
    void setScore(int score);
    void setAlive(bool alive);

private:
    QString m_name;
    int m_score;
    bool m_alive;

    PlayerBackend * m_backend;

};

#endif // PLAYER_H
