import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import "."

Window {
    id: root
    objectName: "Root"
    visible: true
    width: 640
    height: 480
    color: "teal"
    title: qsTr("Test")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            model: ListModel {
                id: model
            }

            delegate: Rectangle {
                width: parent.width
                height: 80
                color: "transparent"
                border.width: 2
                border.color: ListView.isCurrentItem ? "brown" : "transparent"

                MouseArea {
                    anchors.fill: parent
                    onClicked: listView.currentIndex = index
                }

                Column {
                    padding: 5

                    Text {
                        id: nameField
                        text: model.name
                    }

                    Text {
                        id: widthField
                        text: model.width
                    }

                    Text {
                        id: heightField
                        text: model.height
                    }

                    Text {
                        id: visibleField
                        text: model.visible ? "true" : "false"
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            MyButton {
                property bool started: false
                id: startButton
                text: started ? qsTr("Stop Recording") : qsTr("Start Recording")
                source: "/res/start.png"
                onClicked: {console.log(text + " pressed"); Logger.toggleLogging(); started = !started }
            }

            Item {
                id: emptySpace
                Layout.fillWidth: true
            }

            MyButton {
                id: deleteButton
                text: qsTr("Delete Entry")
                source: "/res/delete.png"
                onClicked: {
                    if (model.count !== 0) {
                        model.remove(listView.currentIndex)
                    }
                }
            }
        }
    }

    function updateModel(name, width, height, visible) { model.append({"name": name, "width": width, "height": height, "visible": visible}) }
}
