#ifndef JSONENCODERDECODER_H
#define JSONENCODERDECODER_H

#include <QObject>

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

    QString encode(const Player * p);
    Player decode(QString o);

signals:

public slots:
};

#endif // JSONENCODERDECODER_H
