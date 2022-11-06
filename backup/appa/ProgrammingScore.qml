import QtQuick 2.15
import QtQuick.Layouts 1.3

Item {
    property string programming_img: ""
    property string programming_text: ""
    property int programming_score: 0
    width: 400
    height: 50

    Row {
        id: row
        anchors.fill: parent
        spacing: 50

        Image {
            id: pl_image_logo
            width: 60
            height: 60
            anchors.verticalCenter: parent.verticalCenter
            source: programming_img
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: pl_text_name
            width: 100
            text: programming_text
            anchors.verticalCenter: parent.verticalCenter
//            font.pixelSize: 12
        }

        Text {
            id: pl_text_score
            width: 30
            text: String(programming_score) + "/5"
            anchors.verticalCenter: parent.verticalCenter
//            font.pixelSize: 12
        }

        Image {
            id: pl_image_tick
            width: 25
            height: 25
            anchors.verticalCenter: parent.verticalCenter
            source: programming_score >= 3 ? "/../rc/tick.png" : "s/../rc/x.png"
            fillMode: Image.PreserveAspectFit
        }
    }
}
