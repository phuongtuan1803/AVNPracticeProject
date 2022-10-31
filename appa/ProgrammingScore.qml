import QtQuick 2.15
import QtQuick.Layouts 1.3

Item {
    property string programming_img: ""
    property string programming_text: ""
    property int programming_score: 0
    RowLayout {
        height: 75
        Nulo{}
        Image{
            Nulo{}
            Layout.fillHeight: true
            id: programmingImage
            source: programming_img
            fillMode: Image.PreserveAspectFit
        }
        Text {
            Nulo{}
            id: programmingName
            width: 50
            text: programming_text
        }
        Text {
            Nulo{}
            id: programmingScore
            width: 50
            text: String(programming_score) + "/5"
        }
        Image{
            Nulo{}
//            Layout.fillHeight: true
            height: 4
            id: programmingTick
            fillMode: Image.PreserveAspectFit
            source: programming_score >= 3 ? "/../rc/tick.png" : "s/../rc/x.png"
        }
    }

}
