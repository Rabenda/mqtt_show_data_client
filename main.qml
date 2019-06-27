import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.3

Window {
    id: window
    visible: true
    width: 480
    height: 320
    title: qsTr("Hello World")

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    Text {
        id: element
        x: 150
        y: 86
        width: 199
        height: 106
        text: qsTr("Hello World")
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }

    Button {
        id: button
        x: 378
        y: 278
        text: qsTr("Button")
        onClicked: {
            element.text = qsTr("23333")
        }
    }

    Button {
        id: button1
        x: 2
        y: 2
        text: qsTr("Button")
    }
}
