#ifndef ENCODERDECODER_H
#define ENCODERDECODER_H

#include <QObject>

#include <QByteArray>

#include "playerinformation.h"
#include "message.h"

class EncoderDecoder : public QObject
{
    Q_OBJECT
public:
    explicit EncoderDecoder(QObject *parent = nullptr);

    virtual QByteArray encode(const Message * p) { return QByteArray(); }
    virtual Message * decode(QByteArray o) { return new Message(); }

signals:

public slots:
};

#endif // ENCODERDECODER_H
