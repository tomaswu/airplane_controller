import QtQuick
import QtQuick.Shapes

Item {
    id:dc
    width:  200
    height: 200
    property real v: 0
    property real h: 0

    Shape {
        id: ctr
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
            fillColor: "#80303030"
            startX: ctr.width/2+pa.radiusX
            startY: ctr.height/2
            PathAngleArc{
               id:pa
               centerX: ctr.width/2
               centerY: ctr.height/2
               moveToStart: true
               radiusX: ctr.width/2
               radiusY: radiusX
               startAngle: 0
               sweepAngle: 360
            }
        }//end shape path

    }// end shape

    Rectangle{
        id:indictor
        width: dc.width*0.2
        height: width
        x:(dc.width-width)/2
        y:(dc.height-height)/2
        radius:width/2
        color:"#30ffffff"
    }

    MouseArea{
        id:mouse_area
        anchors.fill: parent
        containmentMask: ctr
        property var p0: Qt.point(0,0)
        onPositionChanged: function(e){
            var ox = ctr.x+ctr.width/2
            var oy = ctr.y+ctr.height/2
            var r = pa.radiusX-indictor.width/2
            var v = [e.x-ox,e.y-oy]
            var vl = norm(v)
            if(vl<=r){
                indictor.x = e.x-indictor.width/2
                indictor.y = e.y-indictor.height/2
            }
            else{
                var nv = [v[0]/vl,v[1]/vl]
                var p = [nv[0]*r,nv[1]*r]
                indictor.x = p[0]+ox-indictor.width/2
                indictor.y = p[1]+oy-indictor.height/2
            }
            var ix = indictor.x+indictor.width/2
            var iy = indictor.y+indictor.height/2
            var cx = (ix-ox)*100/r*1.41421356
            var cy = (oy-iy)*100/r*1.41421356
            cx = cx>100? 100:cx
            cy = cy>100? 100:cy
            dc.v = cx
            dc.h = cy
        }
        onReleased: function(e){
            indictor.x=(dc.width-indictor.width)/2
            indictor.y=(dc.height-indictor.height)/2
            dc.v = 0
            dc.h = 0
        }
    }

    function norm(n){
        return Math.sqrt(n[0]**2+n[1]**2)
    }
}
