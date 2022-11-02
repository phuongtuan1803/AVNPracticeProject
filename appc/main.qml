import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 400
    height: 700
    visible: true
    title: qsTr("Viewer")

    Rectangle{
        //        Nulo{}
        anchors.fill: parent
        Column {
            id: column
            x: 0
            width: parent.width
            height: 500
            spacing: 10

            Text{
                id: headerTxt
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                text: name
                font.pixelSize: 30
                font.bold: true
            }
            ProgrammingScore{
                height: 50
                programming_img : "/../rc/asm.png"
                programming_text : "Assembly"
                programming_score: asm_score
            }
            ProgrammingScore{
                height: 50
                programming_img  : "/../rc/cpp.png"
                programming_text : "C++"
                programming_score: cpp_score
            }
            ProgrammingScore{
                height: 50
                programming_img  : "/../rc/js.png"
                programming_text : "Javascript"
                programming_score: js_score
            }
            ProgrammingScore{
                programming_img  : "/../rc/opengl.png"
                programming_text : "OpenGL"
                programming_score: opengl_score
            }
            ProgrammingScore{
                id: qmlScoreId
                programming_img  : "/../rc/qml.png"
                programming_text : "QML"
                programming_score: qml_score
            }
            Timer {
                id: loadingTimer
                interval: 3000; running: false; repeat: false
                onTriggered: {
                    listView.visible = true
                }
            }
            Button{
                id: updateButton
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Update"
                background: Rectangle {
                    color: "lightgreen"
                    width: 100
                    height: 30
                anchors.horizontalCenter: parent.horizontalCenter

                }
                onClicked: {
                    listView.visible = false
                    loadingTimer.start()
                    console.log("Timer started!")
                }
            }
            Row {
                id: rowSearch
                Text {
                    width: 80
                    height: 20
                    text: qsTr("Search: ")
                }

                TextEdit {
                    id: searchtextedit
                    width: 80
                    height: 20
                    text: ""

                    font.styleName: "Medium Italic"
                    onTextChanged: {
                        employeeListModel.updateSearch(searchtextedit.text)
                    }
                }
            }
            Row {
                id: headerRow
                height: 30
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    text: ""
                    width: 1
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    text: "Name"
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
                Text {
                    text: "Avg Score"
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
                Button {
                    text: "Append"
                    width: 40
                    onClicked: employeeListModel.addItem("tuan", [1,2,3,4,5])
                }
                spacing: 100
            }
            Rectangle{
                id: loadingRect
                width: parent.width
                height: 220
                visible: !listView.visible
                anchors.horizontalCenter: parent.horizontalCenter
                BusyIndicator {
                    id: busyIndicator
                    anchors.horizontalCenter: parent.horizontalCenter
                    running: loadingRect.visible === true
                }
            }
            ListView {
                id: listView
                objectName: "listView"
                width: parent.width
                height: 220
                anchors.horizontalCenter: parent.horizontalCenter

                flickableDirection: Flickable.VerticalFlick
                boundsBehavior: Flickable.StopAtBounds
                clip: true
                model: searchtextedit.text === "" ? employeeListModel : employeeListModel/*employeeFilterModel*/

                delegate: Item {

                    height: 30
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter

                    Row {
                        id: row1
                        Text {
                            text: ""
                            width: 1
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            text: model.name
                            width: 100
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            text: model.score
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        spacing: 100

                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            listView.currentIndex = index
                            employeeListModel.select(index)
                        }
                    }
                }
                ScrollBar.vertical: ScrollBar {
                    width: 15
                }
                highlight: Rectangle {
                    color: 'aquamarine'
                    width: parent.width
                }
            }
        }
    }
}
