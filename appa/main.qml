import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Viewer")

    Rectangle{
        anchors.fill: parent
        Text{
            id: headerTxt
            height: 100
            anchors.centerIn: parent
            text: "THE DIVA DIVO"
        }
        Rectangle{
            anchors.top: headerTxt.bottom
            anchors.centerIn: parent
            ProgrammingScore{
                programming_img  : "/../rc/asm.png"
                programming_text : "Assembly"
                programming_score: 4
            }
        }
    }
}
