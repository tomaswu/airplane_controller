import QtQuick
import QtQuick.Controls

Item {
    id:controllerui
    width: 18*50
    height: 9*50
    Rectangle{
        id:bg
        anchors.fill: parent
        color: "lightgray"

        Text {
            id: title
            text: qsTr("controller")
            font.pointSize: 36
            x:(bg.width-width)/2
            y:bg.height*0.05
            color:"green"
            font.family: "JetBrains Mono"
        }


    }// end bg
}// end item
