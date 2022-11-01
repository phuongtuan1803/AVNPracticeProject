import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 400
    height: 700
    visible: true
    title: qsTr("Viewer")

    Rectangle{
        anchors.fill: parent
        Column {
            id: column
            x: 0
            y: 100
            width: parent.width
            height: 500
            spacing: 10

            Text{
                id: headerTxt
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                text: name
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
                text: "Refresh"
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
                height: 30
                width: parent.width/2
                anchors.horizontalCenter: parent.horizontalCenter
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
                spacing: 150
            }
            Rectangle{
                id: loadingRect
                width: parent.width
                height: 600
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
                height: 600
                anchors.horizontalCenter: parent.horizontalCenter
                flickableDirection: Flickable.VerticalFlick
                boundsBehavior: Flickable.StopAtBounds
                clip: true
                model: searchtextedit.text === "" ? employeeListModel : employeeFilterModel

                delegate: Item {

                    height: 30
                    width: parent.width/2
                    anchors.horizontalCenter: parent.horizontalCenter

                    Row {
                        id: row1
                        Text {
                            text: model.name
                            width: 100
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            text: model.score
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        spacing: 150

                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            listView.currentIndex = index
                            employeeListModel.select(index)
                        }
                    }
                }
                ScrollBar.vertical: ScrollBar {}
                highlight: Rectangle {
                    color: 'green'
                    width: parent.width
                    //                    Text {
                    //                        anchors.centerIn: parent.w
                    //                        text: 'Hello ' + model.get(list.currentIndex).name
                    //                        color: 'white'
                    //                    }
                }
            }
        }
    }
}
