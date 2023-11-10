import QtQuick
import QtQuick.Window
import QtQuick.Controls
import com.dima.GPIOListModel

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: "Raspberry Pi GPIO"
    color: "#000000"

    component PinDelegate: Rectangle{
        id: delegateRectangle
        required property string gpioName
        required property int gpioNumber
        required property int index
        required property bool gpioState
        required property int gpioMode

        width: leftListView.width
        height: (((index+delegateRectangle.ListView.view.position) % 2) === 0)?leftListView.height/20:0
//        border.color: "blue"
//        border.width: 1
        visible: ((index+delegateRectangle.ListView.view.position) % 2) === 0
        color: mainWindow.color

        Row{
            anchors.fill: parent
            layoutDirection: (delegateRectangle.ListView.view.position === 0) ? Qt.RightToLeft : Qt.LeftToRight
            Rectangle{
                id: itemPinCircle
                height: parent.height
                width: parent.height
                color: "grey"
                Rectangle{
                    height: parent.height * 0.7
                    width: parent.width * 0.7
                    radius: height/2
                    anchors.centerIn: parent
                    color: gpioState?"green":"blue"
                }
                Text {
                    anchors.centerIn: parent
                    width: parent.width
                    height: parent.height
                    id: textPinNumber
                    color: "white"
                    text: index+1
                    font.pixelSize: parent.height * 0.5
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Item{
                id: itemPinName
                height: parent.height
                width: height*3.5
                Text {
                    width: parent.width
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    color:  gpioNumber < 0 ? (gpioName === "GND" ?"#88f":"red")  : "white"
                    text: gpioNumber < 0 ? gpioName : "GPIO" + gpioNumber
                    font.bold: true
                    font.pixelSize: parent.height * 0.8
                    leftPadding: parent.height * 0.2
                    rightPadding: parent.height * 0.2
                    horizontalAlignment: (delegateRectangle.ListView.view.position === 0) ? Text.AlignRight : Text.AlignLeft
                }
            }
            Item{
                id: itemComboBox
                height: parent.height
                width: height*3
                ComboBox{
                    visible: gpioNumber >= 0
                    anchors.centerIn: parent
                    width: parent.width
                    height: parent.height * 0.9
                    font.pixelSize: parent.height * 0.8
                    textRole: "text"
                    valueRole: "value"
                    model: [
                        { value: 0, text: "IN"},
                        { value: 1, text: "OUT" },
                    ]
                    onActivated: GPIOListModel.changeMode(delegateRectangle.index, currentValue)
                    Component.onCompleted: currentIndex = gpioMode
                }
            }
            Item{
                id: modeButtons
                height: parent.height
                width: height * 3
                anchors.leftMargin: height * 0.2
                anchors.rightMargin: height * 0.2
                visible: gpioNumber >= 0 && gpioMode === 1

                Button{
                    id: btnOn
                    anchors.leftMargin: height * 0.2
                    height: parent.height * 0.9
                    width: height * 1.5
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: gpioState
                    text: "ON"
                    onClicked: {
                        GPIOListModel.setGPIOout(gpioNumber, true)
                    }
                }
                Button{
                    id: btnOff
                    anchors.rightMargin: height * 0.2
                    height: parent.height * 0.9
                    width: height * 1.5
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: !gpioState
                    text: "OFF"
                    onClicked: {
                        GPIOListModel.setGPIOout(gpioNumber, false)
                    }
                }
            }
        }
    }

    Item{
        id: topItem
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: parent.height * 0.025
    }
    Item{
        anchors{
            top: topItem.bottom
            left: parent.left
            right: parent.right
        }
        height: parent.height * 0.95
        width: parent.width
        ListView{
            id: leftListView
            anchors{
                top: parent.top
                bottom: parent.bottom
                left: parent.left
            }
            width: parent.width/2
            interactive: false
            model: GPIOListModel
            property int position: 0
            delegate: PinDelegate{}
        }

        ListView{
            id: rightListView
            anchors{
                top: parent.top
                bottom: parent.bottom
                right: parent.right
            }
            width: parent.width/2
            interactive: false
            model: GPIOListModel
            property int position: 1
            delegate: PinDelegate{}
        }
    }

}
