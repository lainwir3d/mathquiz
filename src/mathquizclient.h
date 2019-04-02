#ifndef MATHQUIZCLIENT_H
#define MATHQUIZCLIENT_H

#include <QObject>

#include "playerbackend.h"

class MathQuizClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PlayerBackend * backend READ backend WRITE setBackend NOTIFY backendChanged);
public:
    explicit MathQuizClient(QObject *parent = nullptr);

    PlayerBackend * backend() const { return m_backend; }

signals:
    void backendChanged(PlayerBackend * backend);

public slots:
    void setBackend(PlayerBackend * backend);

private slots:


private:
    PlayerBackend * m_backend;
};

#endif // MATHQUIZCLIENT_H
