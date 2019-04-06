import QtQuick 2.9
import QtQuick.Window 2.2

import QtQuick.Controls 2.5

import MathQuiz 1.0

Window {
    id: mainW

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property string _defaultIP: "127.0.0.1"

    MathQuizClient {
        player: Player {
            infos: PlayerInformation {
                id: player

                name: playerNameField.text
            }
            backend: PlayerTCPBackend {
                id: tcpBackend

                ip: ipField.text
                port: 42000
            }
            encoderDecoder: JSONEncoderDecoder {

            }
        }
    }

    Column {
        anchors.centerIn: parent
        Row {
            spacing: 5
            Label {
                anchors.verticalCenter: parent.verticalCenter

                text: "Nom du joueur"
            }

            TextField {
                id: playerNameField

                anchors.verticalCenter: parent.verticalCenter

                text: "toto"
            }
        }

        Row {
            spacing: 5

            Label {
                anchors.verticalCenter: parent.verticalCenter

                text: "IP du serveur:"
            }

            TextField {
                id: ipField

                anchors.verticalCenter: parent.verticalCenter

                text: mainW._defaultIP
            }
        }
    }


    Button {
        id: connectButton

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        text: "Connect"

        onClicked: {
            tcpBackend.connectToServer();
        }
    }
}
