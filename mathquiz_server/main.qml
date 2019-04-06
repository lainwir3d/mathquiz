import QtQuick 2.0
import QtQuick.Controls 2.12

import MathQuiz 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480

    title: qsTr("MathQuiz server")

    MathQuizServer {
        id: server

        listeners: [
            TcpConnectionListener {
                listen: true
            }

        ]
    }

    ListView {
        anchors.fill: parent

        model: server.playerModel

        delegate: Label {
            text: "Player: " + playerName
        }

    }

}
