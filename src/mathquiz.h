#ifndef MATHQUIZ_H
#define MATHQUIZ_H

#include <QObject>
#include <QtQml>


#include "connectionlistener.h"
#include "tcpconnectionlistener.h"

#include "mathquizserver.h"
#include "mathquizclient.h"

#include "playerinformation.h"
#include "player.h"
#include "playertcpbackend.h"

#include "encoderdecoder.h"
#include "jsonencoderdecoder.h"

#include "playerlistmodel.h"

class MathQuiz : public QObject
{
    Q_OBJECT
public:
    explicit MathQuiz(QObject *parent = nullptr);
    static void declareQML();

signals:

public slots:
};

#endif // MATHQUIZ_H
