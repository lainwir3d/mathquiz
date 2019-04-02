#include "mathquizclient.h"

MathQuizClient::MathQuizClient(QObject *parent) : QObject(parent)
{

}



void MathQuizClient::setBackend(PlayerBackend * backend)
{
    if (m_backend == backend)
        return;

    m_backend = backend;
    emit backendChanged(m_backend);
}
