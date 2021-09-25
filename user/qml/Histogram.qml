import QtQuick 2.0
import com.demo.project 1.0

Column {
    id: _histColumn
    spacing: 2
    property var histThreadManager: _histThreadManager

    Repeater {
        id: _histoBars
        model: WordRankModel {}
        delegate: _histBar
    }
    HistThreadManager {
        id: _histThreadManager
    }
    Component.onCompleted: {
        _histThreadManager.model = _histoBars.model
        // Uncomment the below 2 lines for debugging
        //_histThreadManager.setFileUrl("file:///home/tima/prj/exams/hist/tests/vm.txt")
        //_histThreadManager.start()
    }

    Component {
        id: _histBar
        Rectangle {
            width: parent.width
            height: 32
            color: 'green'
            border.color: 'yellow'
            Rectangle {
                width: parent.width * (model.total ? model.count / model.total : 0.0)
                height: parent.height
                color: 'lime'
                border.color: 'yellow'
            }
            Item {
                id: _text
                anchors.fill: parent
                anchors.margins: 10
                Text {
                    id: _word
                    height: parent.height
                    width: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: 'yellow'
                    text: model.display
                }
                Text {
                    id: _count
                    height: parent.height
                    width: parent.width
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                    color: 'lime'
                    text: ''+model.count
                }
            }
        }
    }
}
