#ifndef ENCODERDECODER_H
#define ENCODERDECODER_H

#include <QObject>

#include "player.h"

class EncoderDecoder : public QObject
{
    Q_OBJECT
public:
    explicit EncoderDecoder(QObject *parent = nullptr);

    virtual QString encode(const Player * p) = 0;
    virtual Player decode(QString o) = 0;


signals:

public slots:
};

#endif // ENCODERDECODER_H
