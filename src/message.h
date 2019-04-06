#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QDateTime>

#include "playerinformation.h"

class Message : public QObject
{
    Q_OBJECT
public:
    enum MessageType {
        NoMessage = 0,
        PlayerInformationMessage = 1
    };
    Q_ENUM(MessageType)

    const static QMap<int, QString> typeMap;

    explicit Message(QObject *parent = nullptr);
    explicit Message(Message::MessageType type, QMap<QString, QVariant> payload, QObject *parent = nullptr);

    MessageType type() const { return m_type; };
    QMap<QString, QVariant> payload() const { return m_payload; }
    qint64 timestamp() const { return m_timestamp; }


    static Message * newMessage(PlayerInformation * i);
    static PlayerInformation * toPlayerInformation(Message * m);

signals:

public slots:

private:
    QMap<QString, QVariant> m_payload;
    MessageType m_type;
    qint64 m_timestamp;
};

#endif // MESSAGE_H
