#include "jsonencoderdecoder.h"

JSONEncoderDecoder::JSONEncoderDecoder(QObject *parent) : EncoderDecoder(parent)
{

}

QByteArray JSONEncoderDecoder::encode(const Player *p)
{
    QJsonDocument doc;

    QJsonArray messages;

    QJsonObject obj = _encode(p);

    messages.append(obj);

    doc.setArray(messages);

    return doc.toJson();
}

Player JSONEncoderDecoder::decode(QByteArray o)
{

}

QJsonObject JSONEncoderDecoder::_encode(const Player *p)
{
    QJsonObject obj;

    obj["name"] = p->name();
    obj["score"] = p->score();
    obj["alive"] = p->alive();

    return obj;
}

Player JSONEncoderDecoder::_decode(QJsonObject o)
{

}
