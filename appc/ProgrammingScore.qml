import QtQuick 2.15
import QtQuick.Layouts 1.3

Item {
    property string programming_img: ""
    property string programming_text: ""
    property int programming_score: 0
    property string programming_score_input: pl_text_score.text

    width: 400
    height: 30
    onProgramming_scoreChanged: {
        pl_text_score.text = programming_score
    }
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
            width: 50
            text: programming_text
            anchors.verticalCenter: parent.verticalCenter
        }
        TextInput {
            id: pl_text_score
            width: 50
//            text: "0"
            anchors.verticalCenter: parent.verticalCenter
        }

        Text {
            width: 5
            text: "/5"
            anchors.verticalCenter: parent.verticalCenter
        }

        Image {
            id: pl_image_tick
            width: 25
            height: 25
            anchors.verticalCenter: parent.verticalCenter
            source: programming_score < 3 ? "s/../rc/x.png" : "/../rc/tick.png"
            fillMode: Image.PreserveAspectFit
        }
    }
}
