import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import EmployeeInfoModel 1.0

Window {
    width: 400
    height: 700
    minimumWidth: 400
    maximumWidth: 400
    minimumHeight: 700
    visible: true
    title: qsTr("Viewer A")

    Rectangle{
        anchors.fill: parent
        Column {
            id: column
            anchors.fill: parent
            spacing: 10

            Text{
                id: headerTxt
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                text: EmployeeInfoModel.name === "" ? "---" : EmployeeInfoModel.name
                font.pixelSize: 30
                font.bold: true
                onTextChanged: {
                    console.log(EmployeeInfoModel.name)
                }
            }
            ProgrammingScore{
                id : asmID
                height: 50
                programming_img : "/../rc/asm.png"
                programming_text : "Assembly"
                programming_score: EmployeeInfoModel.asm_score
            }
            ProgrammingScore{
                id : cppID
                height: 50
                programming_img  : "/../rc/cpp.png"
                programming_text : "C++"
                programming_score: EmployeeInfoModel.cpp_score
            }
            ProgrammingScore{
                id : jsID
                height: 50
                programming_img  : "/../rc/js.png"
                programming_text : "Javascript"
                programming_score: EmployeeInfoModel.js_score
            }
            ProgrammingScore{
                id : openglID
                programming_img  : "/../rc/opengl.png"
                programming_text : "OpenGL"
                programming_score: EmployeeInfoModel.opengl_score
            }
            ProgrammingScore{
                id: qmlId
                programming_img  : "/../rc/qml.png"
                programming_text : "QML"
                programming_score: EmployeeInfoModel.qml_score
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
                    EmployeeInfoModel.refeshItem(empid,[ parseInt(asmID.programming_score_input)
                                                , parseInt(cppID.programming_score_input)
                                                , parseInt(jsID.programming_score_input)
                                                , parseInt(openglID.programming_score_input)
                                                , parseInt(qmlId.programming_score_input)])
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
                        EmployeeInfoModel.updateSearch(searchtextedit.text)
                    }
                }
            }
            Row {
                id: headerRow
                height: 30
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: rowSearch.bottom
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
                // Button {
                //     text: "Append"
                //     width: 40
                //     onClicked: EmployeeInfoModel.addItem("tuan", [1,2,3,4,5])
                // }
                spacing: 100
            }
            Rectangle{
                id: loadingRect
                width: parent.width
                visible: !listView.visible
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: headerRow.bottom
                anchors.bottom: parent.bottom
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
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: headerRow.bottom
                anchors.bottom: parent.bottom
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
                            EmployeeInfoModel.select(index)
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
