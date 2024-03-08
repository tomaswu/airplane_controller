import QtQuick

Window {
    width: 960
    height: 480
    visible: true
    title: qsTr("airplane controller")
    ControllerUi{
        id:index
        anchors.fill: parent
    }
}
