import QtQuick
import Qt5Compat.GraphicalEffects

Item {
    property string source: ""
    property var color: "#323232"
    property int fillMode: Image.Stretch

    Image{
        id:mask
        anchors.fill: parent
        source: parent.source
        fillMode: parent.fillMode
        mipmap:true
        visible: false
    }

    ColorOverlay {
        anchors.fill: mask
        source: mask
        color: parent.color
    }

}
