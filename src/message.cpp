#include "message.h"

const QMap<int, QString> Message::typeMap { {0, "NoMessage"}, {1, "PlayerInformationMessage"}};

Message::Message(QObject *parent) : QObject(parent)
{
    m_timestamp = QDateTime::currentMSecsSinceEpoch();
}

Message::Message(Message::MessageType type, QMap<QString, QVariant> payload, QObject *parent): Message(parent)
{
    m_type = type;
    m_payload = payload;
}

Message * Message::newMessage(PlayerInformation *i)
{
    QMap<QString, QVariant> map;
    map.insert("name", i->name());
    map.insert("score", i->score());
    map.insert("alive", i->alive());

    Message * m = new Message(Message::PlayerInformationMessage, map);
    return m;
}

PlayerInformation * Message::toPlayerInformation(Message *m)
{
    if(!m) return nullptr;

    if(!m->type() == Message::PlayerInformationMessage) return nullptr;


    QMap<QString, QVariant> data = m->payload();

    PlayerInformation * i = new PlayerInformation();
    i->setName(data.value("name", "Invalid").toString());
    i->setScore(data.value("score", 0).toInt());
    i->setAlive(data.value("alive", true).toBool());

    return i;
}
