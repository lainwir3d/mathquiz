import QtQuick 2.0

import QtQuick.Controls 2.12
import QtQuick.Layouts 1.2

import MathQuiz 1.0


Item {

    property MathQuizServer server: MathQuizServer { }

    Column {
        Label {
            text: server.listeners[0].listen ? qsTr("Listening on port %1: %2").arg(server.listeners[0].port).arg(server.listeners[0].listeningDetails) : qsTr("Server not listening")
        }

        Label {
            text: qsTr("Players connected: %1").arg(server.nbPlayersConnected)
        }

        Label {
            text: qsTr("Quiz availables: %1").arg(server.quizModel.rowCount())
        }
    }

    ListView {
        anchors.fill: parent

        visible: false
        model: server.quizModel

        delegate: Label {
            text: "Quiz: " + quizId + " (v" + quizVersion + ")"
        }

    }
}
