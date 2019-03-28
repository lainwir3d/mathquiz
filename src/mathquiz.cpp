#include "mathquiz.h"

MathQuiz::MathQuiz(QObject *parent) : QObject(parent)
{

}

void MathQuiz::declareQML()
{
    qmlRegisterType<TcpConnectionListener>("MathQuiz", 1, 0, "TcpConnectionListener");
}
