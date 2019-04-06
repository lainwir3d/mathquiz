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
    QJsonDocument doc = QJsonDocument::fromJson(o);

    if(doc.isNull()){
        return nullptr;
    }

    Message * m = nullptr;

    QJsonArray array = doc.array();
    if(array.count() > 0){ // we only support message 1 by 1
        QJsonObject obj = array.at(0).toObject();
        Message::MessageType type = static_cast<Message::MessageType>(Message::typeMap.key(obj.value("type").toString()));
        qint64 timestamp = obj.value("timestamp").toInt(0);
        QJsonObject payload = obj.value("payload").toObject();

        QMap<QString, QVariant> payloadMap;

        //QJsonObject::const_iterator iter = payload.begin();
        for(auto iter = payload.begin(); iter != payload.end() ; ++iter){
            payloadMap.insert(iter.key(), iter.value().toVariant());
        }

        m = new Message(type, payloadMap);

    }else{
        qDebug() << QString("%1::%2 - No message in array").arg(_classname).arg(__func__);
    }

    return m;
}
