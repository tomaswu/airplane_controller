import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import QtQuick.Shapes

Item {
    id:controllerui
    width: 18*50
    height: 9*50
    antialiasing: true
    Rectangle{
        id:bg
        anchors.fill: parent
        color: "lightgray"

        Text {
            id: title
            text: qsTr("controller")
            font.pointSize: 36
            x:(bg.width-width)/2
            y:bg.height*0.02
            color:"green"
            font.family: "JetBrains Mono"
        }

        DirectionControl{
            width: 160
            height: width
            x:bg.width*0.08
            y:bg.height*0.35
        }

        ArrowButton{
            id:btn_up
            width: 120
            height: 80
            x:bg.width*0.82
            y:bg.height*0.3
        }

        ArrowButton{
            id:btn_down
            width: btn_up.width
            height: btn_up.height
            x:btn_up.x
            y:btn_up.y+btn_up.height+10
            rotation: 180
        }

        Rectangle {
            id: img_bg
            width: bg.width*0.45
            height: width*0.75
            x:(bg.width-width)/2+bg.width*0.05
            y:bg.height*0.18
            color: "black"

        }


    }// end bg
}// end item
