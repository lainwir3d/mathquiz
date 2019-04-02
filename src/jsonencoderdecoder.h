#ifndef JSONENCODERDECODER_H
#define JSONENCODERDECODER_H

#include <QObject>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "player.h"
#include "question.h"
#include "answer.h"

#include "encoderdecoder.h"

class JSONEncoderDecoder : public EncoderDecoder
{
    Q_OBJECT
public:
    explicit JSONEncoderDecoder(QObject *parent = nullptr);

    QByteArray encode(const Player * p);
    Player decode(QByteArray o);

signals:

public slots:

private:
    QJsonObject _encode(const Player * p);
    Player _decode(QJsonObject o);

};

#endif // JSONENCODERDECODER_H
