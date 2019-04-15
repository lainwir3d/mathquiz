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

    StackView {
        id: stack

        anchors.fill: parent

        Component.onCompleted: {
            stack.push([Qt.resolvedUrl("MathQuizServerOverview.qml"), {"server": server} ]);
        }
    }

    /*
    ListView {
        anchors.fill: parent

        model: server.playerModel

        delegate: Label {
            text: "Player: " + playerName
        }

    }
    */

}
