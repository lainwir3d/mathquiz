import QtQuick 2.9
import QtQuick.Window 2.2

import QtQuick.Controls 2.5

Window {
    id: mainW

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property string _defaultIP: "127.0.0.1"

    TextField {
        id: ipField

        anchors.centerIn: parent

        text: mainW._defaultIP
    }


    Button {
        id: connectButton

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        text: "Connect"
    }
}
