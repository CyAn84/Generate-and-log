import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    width: 150
    height: 50
    color: "gold"
    property alias text: label.text
    property alias source: icon.source
    signal clicked

    RowLayout {
        anchors.fill: parent
        anchors.margins: 5

        Image {
            id: icon
            width: 30
            height: 30
            sourceSize.width: width
            sourceSize.height: height
        }

        Text {
            id: label
            color: "brown"
            text: qsTr("text")
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onEntered: { root.state = 'hovered' }
        onExited: { root.state = "" }
        onClicked: { root.clicked() }
    }

    states: [
        State {
            name: "hovered"
            PropertyChanges { target: root; color: "orange" }
            PropertyChanges { target: label; color: "blue" }
        }
    ]
}
