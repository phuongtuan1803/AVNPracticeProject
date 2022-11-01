import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import EmployeeListModel 1.0

Window {
    width: 400
    height: 700
    visible: true
    title: qsTr("Viewer")
    EmployeeListModel{
        id: employeeListModel
    }
    Rectangle{
        anchors.fill: parent
        Column {
            //            Nulo{}
            id: column
            x: 0
            y: 100
            width: parent.width
            height: 500
            spacing: 10

            Text{
//                Nulo{}
                id: headerTxt
                height: 50
                anchors.horizontalCenter: parent.horizontalCenter
                text: employeeInfoModel.name
            }
            ProgrammingScore{
                height: 50
                programming_img : "/../rc/asm.png"
                programming_text : "Assembly"
                programming_score: employeeInfoModel.asm_scrore
            }
            ProgrammingScore{
                height: 50
                programming_img  : "/../rc/cpp.png"
                programming_text : "C++"
                programming_score: employeeInfoModel.cpp_scrore
            }
            ProgrammingScore{
                height: 50
                programming_img  : "/../rc/js.png"
                programming_text : "Javascript"
                programming_score: employeeInfoModel.js_scrore
            }
            ProgrammingScore{
                programming_img  : "/../rc/opengl.png"
                programming_text : "OpenGL"
                programming_score: employeeInfoModel.opengl_scrore
            }
            ProgrammingScore{
                programming_img  : "/../rc/qml.png"
                programming_text : "QML"
                programming_score: employeeInfoModel.qml_scrore
            }
            Row {
                id: rowSearch
                //                Nulo{}

                Text {
                    width: 80
                    height: 20
                    text: qsTr("Search: ")
                    //                    font.pixelSize: 12
                }

                TextEdit {
                    id: searchtextedit
                    width: 80
                    height: 20
                    text: qsTr("Text Edit")
                    //                    font.pixelSize: 12
                    font.styleName: "Medium Italic"
                }
            }
            ListView {
                id: listView
                Nulo{}
                width: parent.width
                height: 600
                anchors.horizontalCenter: parent.horizontalCenter
                flickableDirection: Flickable.VerticalFlick
                boundsBehavior: Flickable.StopAtBounds
                clip: true

                header:Row {
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
                model: employeeListModel

                delegate: Item {

                    height: 30
                    width: parent.width/2
                    anchors.horizontalCenter: parent.horizontalCenter
                    Row {
                        id: row1
                        Text {
                            text: name
                            width: 100
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            Nulo{}
                            text: score
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        spacing: 150
                    }
                }
            }
        }
    }
}
