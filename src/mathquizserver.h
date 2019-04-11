#ifndef MATHQUIZSERVER_H
#define MATHQUIZSERVER_H

#include <QObject>
#include <QVariantList>
#include <QQmlListProperty>
#include <QAbstractItemModel>

#include "connectionlistener.h"
#include "tcpconnectionlistener.h"

#include "playerlistmodel.h"
#include "questionbase.h"

#include "quiz.h"
#include "quizlistmodel.h"

#include <QDebug>

class MathQuizServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<ConnectionListener> listeners READ listeners)
    Q_PROPERTY(QAbstractItemModel * playerModel READ playerModel NOTIFY playerModelChanged)
    Q_PROPERTY(QAbstractItemModel * quizModel READ quizModel NOTIFY quizModelChanged)

public:
    explicit MathQuizServer(QObject *parent = nullptr);

    enum ServerMode {
        NoMode = 0,
        SingleGame = 1,
        MultiGame = 2
    };
    Q_ENUM(ServerMode)


    QQmlListProperty<ConnectionListener> listeners() { return QQmlListProperty<ConnectionListener>(this, this, &MathQuizServer::appendListener, &MathQuizServer::listenerCount, &MathQuizServer::listener, &MathQuizServer::clearListener); }
    void appendListener(ConnectionListener *l);
    int listenerCount();
    ConnectionListener* listener(int idx);
    void clearListener();

    QAbstractItemModel * playerModel() const { return m_playerListModel; }

    QAbstractItemModel * quizModel() const
    {
        return m_quizModel;
    }

signals:

    void playerModelChanged(PlayerListModel * playerModel);

    void quizModelChanged(QAbstractItemModel * quizModel);

public slots:

private slots:
    void newPlayerConnectionCallback(Player * p);
    void playerInformationReceived(Player * p, PlayerInformation * info);

private:
    PlayerListModel * m_playerListModel;
    QMap<QString, QuestionBase *> * m_questionBases;
    QMap<QString, Quiz *> * m_quizs;

    /*
     * Static listener accessor
     */
    QList<ConnectionListener *> m_listeners;
    static void appendListener(QQmlListProperty<ConnectionListener>*, ConnectionListener*);
    static int listenerCount(QQmlListProperty<ConnectionListener>*);
    static ConnectionListener* listener(QQmlListProperty<ConnectionListener>*, int);
    static void clearListener(QQmlListProperty<ConnectionListener>*);

    QString _classname = "MathQuizServer";
    QAbstractItemModel * m_quizModel;
};

#endif // MATHQUIZSERVER_H
