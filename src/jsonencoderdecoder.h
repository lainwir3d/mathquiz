#ifndef JSONENCODERDECODER_H
#define JSONENCODERDECODER_H

#include <QObject>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "playerinformation.h"
#include "question.h"
#include "answer.h"

#include "message.h"

#include "encoderdecoder.h"

class JSONEncoderDecoder : public EncoderDecoder
{
    Q_OBJECT
public:
    explicit JSONEncoderDecoder(QObject *parent = nullptr);

    QByteArray encode(const Message * m);
    Message * decode(QByteArray o);

signals:

public slots:

private:

};

#endif // JSONENCODERDECODER_H
