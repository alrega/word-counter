import QtQuick 2.0
import QtQuick.Controls 2.0


ToolBar {
    property var fileOpenDialog
    property var histThreadManager
    id: _root
        Flow {
            anchors.fill: parent
            ToolButton {
                id: _menuItemOpen
                text: qsTr("Open")
                icon.name: "document-open"
                onClicked: _root.fileOpenDialog.open()
                Connections {
                    target: histThreadManager
                    onStarted: {
                        _menuItemOpen.enabled = false
                    }
                    onFinished: {
                        _menuItemOpen.enabled = true
                    }
                }
            }
        }
    }
