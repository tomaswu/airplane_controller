import QtQuick
import QtQuick.Shapes
import Qt5Compat.GraphicalEffects

Item {
    id:ab
    width:  80
    height: 80
    signal  clicked

    Shape {
        id: shp
        anchors.fill: parent
        //只有FillContains才会逐个路径判断
        //默认是BoundingRectContains根据矩形区域判断
        containsMode: Shape.FillContains
        layer.enabled: true
        layer.samples: 4
        antialiasing: true

        ShapePath {
            id:sp
            capStyle: ShapePath.RoundCap
            joinStyle: ShapePath.RoundJoin
            strokeWidth: 1
            strokeColor: "transparent" //mouse_area.containsMouse ? "red" : "blue"
            fillColor: mouse_area.pressed? "#a003030":"#80303030"
            startX: shp.width/2
            startY: 0
            PathLine{x:shp.width*0.1;y:shp.height*0.45}
            PathLine{x:shp.width*0.3;y:shp.height*0.45}
            PathLine{x:shp.width*0.3;y:shp.height*0.9}
            PathLine{x:shp.width*0.7;y:shp.height*0.9}
            PathLine{x:shp.width*0.7;y:shp.height*0.45}
            PathLine{x:shp.width*0.9;y:shp.height*0.45}
            PathLine{x:sp.startX;y:sp.startY}

        }//end shape path

    }// end shape

    // DropShadow{
    //     anchors.fill: shp
    //     horizontalOffset: 2
    //     verticalOffset: 2
    //     radius: 4.0
    //     color: "#000000"
    //     source: shp
    //     z:shp.z-1
    // }


    MouseArea{
        id:mouse_area
        anchors.fill: parent
        containmentMask: shp
        property var p0: Qt.point(0,0)
        onClicked: function(e){
            console.log(e.x,e.y)
            ab.clicked()
        }

    }

}
