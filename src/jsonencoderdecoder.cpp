#include "jsonencoderdecoder.h"

JSONEncoderDecoder::JSONEncoderDecoder(QObject *parent) : EncoderDecoder(parent)
{

}

QByteArray JSONEncoderDecoder::encode(const Message * m)
{
    QJsonDocument doc;

    QJsonArray messages;

    QMap<QString, QVariant> data = m->payload();

    QJsonObject payload;

    QMapIterator<QString, QVariant> i(data);
    while (i.hasNext()) {
        i.next();
        payload.insert(i.key(), QJsonValue::fromVariant(i.value()));
    }

    QJsonObject jsonMessage;
    jsonMessage["payload"] = payload;
    jsonMessage["type"] = Message::typeMap.value(m->type());
    jsonMessage["timestamp"] = m->timestamp();

    messages.append(jsonMessage);

    doc.setArray(messages);

    return doc.toJson();
}

Message * JSONEncoderDecoder::decode(QByteArray o)
{

}
