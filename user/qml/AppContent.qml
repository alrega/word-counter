import QtQuick 2.0
import QtQuick.Controls 2.0

Flickable {
    property var histThreadManager: _histColumn.histThreadManager
    id: _root
    anchors.fill: parent
    anchors.margins: 10
    contentHeight: _histColumn.implicitHeight
    ScrollBar.vertical: ScrollBar {
        id: _scrollBar
        width: 10
        anchors.right: parent.right // adjust the anchor as suggested by derM
    }
    Histogram {
        id: _histColumn
        anchors.fill: parent
        anchors.rightMargin: _scrollBar.width
    }
}
