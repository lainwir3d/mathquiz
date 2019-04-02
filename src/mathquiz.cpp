#include "mathquiz.h"

MathQuiz::MathQuiz(QObject *parent) : QObject(parent)
{

}

void MathQuiz::declareQML()
{
    qmlRegisterType<MathQuizServer>("MathQuiz", 1, 0, "MathQuizServer");
    qmlRegisterType<MathQuizClient>("MathQuiz", 1, 0, "MathQuizClient");


    qmlRegisterType<ConnectionListener>("MathQuiz", 1, 0, "ConnectionListener");
    qmlRegisterType<TcpConnectionListener>("MathQuiz", 1, 0, "TcpConnectionListener");

    qmlRegisterType<PlayerBackend>("MathQuiz", 1, 0, "PlayerBackend");
    qmlRegisterType<PlayerTCPBackend>("MathQuiz", 1, 0, "PlayerTCPBackend");

    qmlRegisterType<Player>("MathQuiz", 1, 0, "Player");

}
