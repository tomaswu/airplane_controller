import QtQuick

Item {
    id: bty
    width: 80*3
    height: 20*3
    property real value: 100
    onValueChanged: cvs.requestPaint()

    Canvas{
        id:cvs
        anchors.fill: parent
        antialiasing: true
        onPaint: {
            var c = getContext("2d")
            var w = width
            var h = height
            var m = 0.5
            c.clearRect(0,0,w,h)
            c.strokeStyle = "#60303030"
            c.lineWidth=m*2
            c.beginPath()
            c.moveTo(m,m)
            c.lineTo(w*0.92,m)
            c.lineTo(w*0.92,h*0.3)
            c.lineTo(w-m,h*0.3)
            c.lineTo(w-m,h*0.7)
            c.lineTo(w*0.92,h*0.7)
            c.lineTo(w*0.92,h-m)
            c.lineTo(m,h-m)
            c.lineTo(m,m)
            c.stroke()
            c.beginPath()
            c.fillStyle = bty.value>=20? "lightgreen":'orange'
            if(bty.value<=10)c.fillStyle="red"
            c.strokeStyle="transparent"
            var x = (w-2*m)*bty.value/100
            c.moveTo(m,m)
            if(x<w*0.92){
                c.lineTo(x,m)
                c.lineTo(x,h-m)
                c.lineTo(m,h-m)
            }else{
                c.lineTo(w*0.92,m)
                c.lineTo(w*0.92,h*0.3)
                c.lineTo(x,h*0.3)
                c.lineTo(x,h*0.7)
                c.lineTo(w*0.92,h*0.7)
                c.lineTo(w*0.92,h-m)
                c.lineTo(m,h-m)
            }
            c.lineTo(m,m)
            c.fill()
        }
    }

    //test
    Timer{
        interval: 50
        repeat: true
        running: true
        onTriggered: {
            var dp=bty.value>80?0.2:1
            var p=bty.value-dp
            if (p<0)p=100
            bty.value=p
        }
    }




}
