#ifndef PLAYERBACKEND_H
#define PLAYERBACKEND_H

#include <QObject>

#include <QDebug>

class PlayerBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ConnectionState state READ state WRITE setState NOTIFY stateChanged)
public:
    explicit PlayerBackend(QObject *parent = nullptr);

    enum ConnectionState {
        UnknownState = 0,
        UnconnectedState = 1,
        ConnectingState = 2,
        ConnectedState = 4
    };
    Q_ENUM(ConnectionState)

    ConnectionState state() const { return m_state; }
    bool sendMessage(QString message) { return sendMessage(message.toUtf8()); }
    virtual bool sendMessage(QByteArray message) { return false; }

signals:
    void stateChanged(ConnectionState state);
    void messageReceived(QByteArray message);

public slots:
    void setState(ConnectionState state);

private slots:

private:

protected:
    ConnectionState m_state;
};

#endif // PLAYERBACKEND_H
