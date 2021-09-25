import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.3
import com.demo.project 1.0
//import .

ApplicationWindow
{
    id: root
    visible: true
    width: 1080
    height: 750
    color: 'white'

    header: AppHeader {
        id: _header
        fileOpenDialog: _fileOpenDialog
        histThreadManager: _content.histThreadManager
    }

    AppContent {
        id: _content
    }

    footer: AppFooter {
        id: _footer
        height: 54
        histThreadManager: _content.histThreadManager
    }

    FileDialog {
        id: _fileOpenDialog
        title: "Select a text file"
        folder: shortcuts.documents
        nameFilters: [
            "Text files (*.txt)",
        ]
        onAccepted: {
            let success = _content.histThreadManager.setFileUrl(fileUrl)
            if(!success) {
                _messageDialog.text = "File " + fileUrl + " is not local"
                _messageDialog.open()
            }
            else
                _content.histThreadManager.start()
        }
    }
    MessageDialog {
        id: _messageDialog
        title: "Failed to open file"
        text: "File is not local"
        icon: StandardIcon.Critical
        Component.onCompleted: visible = false
    }
}
