#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include <QDebug>

#include "playerinformation.h"
#include "playerbackend.h"
#include "encoderdecoder.h"
#include "message.h"

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PlayerInformation * infos READ infos WRITE setInfos NOTIFY infosChanged)
    Q_PROPERTY(PlayerBackend * backend READ backend WRITE setBackend NOTIFY backendChanged)
    Q_PROPERTY(EncoderDecoder * encoderDecoder READ encoderDecoder WRITE setEncoderDecoder NOTIFY encoderDecoderChanged)

public:
    explicit Player(QObject *parent = nullptr);
    explicit Player(PlayerInformation * infos, PlayerBackend * backend = nullptr, EncoderDecoder * encoderDecoder = nullptr, QObject *parent = nullptr);

    PlayerInformation * infos() const { return m_infos; }
    PlayerBackend * backend() const { return m_backend; }
    EncoderDecoder * encoderDecoder() const { return m_encoderDecoder; }

    bool sendMessage(Message * m);

signals:
    void infosChanged(PlayerInformation * infos);
    void backendChanged(PlayerBackend * backend);
    void encoderDecoderChanged(EncoderDecoder * encoderDecoder);
    void connectionStateChanged(PlayerBackend::ConnectionState state);

public slots:
    void setInfos(PlayerInformation * infos);
    void setBackend(PlayerBackend * backend);
    void setEncoderDecoder(EncoderDecoder * encoderDecoder);

private slots:
    void backendChanged_cb(PlayerBackend * backend);
    void encodedMessageReceived(QByteArray message);

private:
    PlayerInformation * m_infos;
    PlayerBackend * m_backend;
    EncoderDecoder * m_encoderDecoder;

    QString _className = "Player";
};

#endif // PLAYER_H
