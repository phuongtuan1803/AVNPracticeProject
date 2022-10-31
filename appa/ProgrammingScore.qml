import QtQuick 2.15

Item {
    property string programming_img: ""
    property string programming_text: ""
    property int programming_score: 0
    Rectangle{
        height: 100
        color: "green"
        Image{
            id: programmingImage
            source: programming_img
            width: 50
            anchors.horizontalCenter: programmingName.horizontalCenter
            fillMode: Image.PreserveAspectFit
        }
        Text {
            id: programmingName
            anchors.left: programmingImage.right
//            height: 100
            width: 100
            text: programming_text
        }
        Text {
            id: programmingScore
            anchors.left: programmingName.right
//            height: parent.height
            width: 200
            text: String(programming_score) + "/5"
        }
        Image{
            id: programmingTick
            anchors.left: programmingScore.right
            width: 50
            fillMode: Image.PreserveAspectFit
            source: programming_score >= 3 ? "/../rc/tick.png" : "s/../rc/x.png"
        }
    }

}
