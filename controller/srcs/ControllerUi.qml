import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import QtQuick.Shapes

Item {
    id:controllerui
    width: 18*50
    height: 9*50
    antialiasing: true

    function controlDc(){
        con.steering(dcl.v,dcl.h,dcr.v,dcr.h)
    }

    Rectangle{
        id:bg
        anchors.fill: parent
        color: "lightgray"

        DirectionControl{
            id: dcl
            objectName: "dcl"
            width: 160
            height: width
            x:bg.width*0.05
            y:bg.height*0.35
            onVChanged: controlDc()
            onHChanged: controlDc()
        }

        DirectionControl{
            id: dcr
            objectName: "dcr"
            width: 160
            height: width
            x:bg.width*0.95-width
            y:bg.height*0.35
            onVChanged: controlDc()
            onHChanged: controlDc()
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
            width: 36
            height: 36
            source: "qrc:/res/icos/connect.svg"
            color: "#80303030"
            property bool isOpen: false
            x:100
            y:16
            Connections{
                target: con
                function onUavConnected(){
                    ico_connect.color="green"
                    ico_connect.isOpen=true
                }
                function onUavDisconnected(){
                    ico_connect.color="#80303030"
                    ico_connect.isOpen=false
                }
            }
        }

        Battery{
            id:bty
            width: 60
            height: 24
            x:ico_connect.x+ico_connect.width+20
            y:ico_connect.y+(ico_connect.height-height)/2
        }

        Button{
            id:btn_connect
            x:bty.x+bty.width+20
            y:ico_connect.y+(ico_connect.height-height)/2
            Text{
                anchors.centerIn: parent
                text: ico_connect.isOpen? "断开":"连接"
            }
            onClicked: {
                con.connectUav(combox_connecttype.currentText)
            }

        }

        ComboBox{
            id:combox_connecttype
            model:["蓝牙","wifi"]
            x: btn_connect.x+btn_connect.width+20
            y:ico_connect.y+(ico_connect.height-height)/2
        }

        Grid{
            rows: 2
            columns: 5
            rowSpacing: 10
            columnSpacing: 10
            x:combox_connecttype.x+combox_connecttype.width+20
            y:ico_connect.y+(ico_connect.height-height)/2
            CheckBox{
                id:rd5
                text:"radio 5"
                onCheckStateChanged: con.switchRadio(5,checked)
            }
            CheckBox{
                id:rd6
                text:"radio 6"
                onCheckStateChanged: con.switchRadio(6,checked)
            }
            CheckBox{
                id:rd7
                text:"radio 7"
                onCheckStateChanged: con.switchRadio(7,checked)
            }
            CheckBox{
                id:rd8
                text:"radio 8"
                onCheckStateChanged: con.switchRadio(8,checked)
            }
            CheckBox{
                id:rd9
                text:"radio 9"
                onCheckStateChanged: con.switchRadio(9,checked)
            }
            CheckBox{
                id:rd10
                text:"radio 10"
                onCheckStateChanged: con.switchRadio(10,checked)
            }
            CheckBox{
                id:rd11
                text:"radio 11"
                onCheckStateChanged: con.switchRadio(11,checked)
            }
            CheckBox{
                id:rd12
                text:"radio 12"
                onCheckStateChanged: con.switchRadio(12,checked)
            }
            CheckBox{
                id:rd13
                text:"radio 13"
                onCheckStateChanged: con.switchRadio(13,checked)
            }
            CheckBox{
                id:rd4
                text:"radio 14"
                onCheckStateChanged: con.switchRadio(14,checked)
            }

        }

        CheckBox{
            id:debug
            text:"debug"
            x:bg.width-width-20
            anchors.verticalCenter: combox_connecttype.verticalCenter
            checked: true
        }

        ScrollView {
            id:debug_scroll
            anchors.fill: img_bg
            visible: debug.checked
            // ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            // ScrollBar.vertical.position:1

            TextArea{
                id:debuginfo
                anchors.fill: parent
                text:"debug info\n"

                Connections{
                    target: con
                    function onLog(s){
                        debuginfo.text+=s
                        debug_scroll.ScrollBar.vertical.position = 1-debug_scroll.ScrollBar.vertical.size
                    }
                }
            }

        }



    }// end bg
}// end item
