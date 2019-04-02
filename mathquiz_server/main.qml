import QtQuick 2.0
import QtQuick.Controls 2.5

import MathQuiz 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480

    title: qsTr("MathQuiz server")

    MathQuizServer {

        listeners: [
            TcpConnectionListener {
                listen: true
            }

        ]
    }

}
