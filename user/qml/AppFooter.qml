import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    property var histThreadManager
    color: 'white'
    Column {
        id: _footerColumn
        spacing: 2
        width: parent.width
        ProgressBar {
            width: parent.width
            value: histThreadManager.percent
            visible: histThreadManager.percent !== 0
        }
        Button {
            id: _cancelButton
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 10
            enabled: false
            text: "Cancel"
            onClicked: {
                histThreadManager.cancel()
            }
            Connections {
                target: histThreadManager
                onStarted: {
                    _cancelButton.enabled = true
                }
                onFinished: {
                    _cancelButton.enabled = false
                }
            }
        }
    }
}
