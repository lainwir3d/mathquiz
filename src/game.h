#ifndef GAME_H
#define GAME_H

#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    enum VictoryMode {
        NoVictoryMode = 0,
        FirstWinVictoryMode = 1,
        PodiumVictoryMode = 2
    };

    explicit Game(QObject *parent = nullptr);


signals:

public slots:
};

#endif // GAME_H
