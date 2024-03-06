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

        DirectionControl{
            width: 160
            height: width
            x:bg.width*0.025
            y:bg.height*0.35
        }

        ArrowButton{
            id:btn_up
            width: 120
            height: 80
            x:bg.width*0.8
            y:bg.height*0.32
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
            x:(bg.width-width)/2
            y:bg.height*0.18
            color: "black"
        }

        ColorImage{
            id:ico_connect
            width: 48
            height: 48
            source: "qrc:/res/icos/connect.svg"
            color: "#80f00f0f"
            x:img_bg.x
            y:10
        }




    }// end bg
}// end item
