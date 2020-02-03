import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Item {
    width: 400
    height: 350

    property alias maximum: meterAnalog.maximumValue
    property alias minimum: meterAnalog.minimumValue

    property double value: 0
    property string unit: ""
    property int index
    property alias image: img.source


    onValueChanged: {
        meterAnalog.value = value.toPrecision(3)
        digitValue.text = value.toPrecision(3)
        //if value exceeds meter bounds
        //---0--max--value
        if(value >= meterAnalog.maximumValue && value >= 0){
            meterAnalog.maximumValue = (value*3/2).toPrecision(3)
        }
        //---value--min--0--
        else if(value <= meterAnalog.minimumValue && value <= 0){
            meterAnalog.maximumValue = 10
            meterAnalog.minimumValue = (value*3/2).toPrecision(3) - 5
        }

    }
    onUnitChanged: {
        digitUnit.text = unit
        unitText.text = unit
    }

    states: [
        State {
            name: "analog"
            PropertyChanges {
                target: meterAnalog
                visible: true
            }
            PropertyChanges {
                target: meterDigital
                visible: false
            }
        },
        State {
            name: "digital"
            PropertyChanges {
                target: meterAnalog
                visible: false
            }
            PropertyChanges {
                target: meterDigital
                visible: true
            }
        }
    ]
    state: settingsReader.getSetting("main","meterStyle",1)


    Image {
        id: img
        width: 128
        height: 128
        anchors.verticalCenter: parent.verticalCenter
        sourceSize.width: 128
        sourceSize.height: 128

        //mouse area for opening filedialog
        MouseArea{
            anchors.fill: parent
            onClicked: {
                dialog.visible = true


            }
        }
        //dialog to choose images
        FileDialog{
            id:dialog
            visible:false
            title: "Valitse kuva"
            nameFilters: [ "Image files (*.png *.jpg)"]
            folder: shortcuts.home
            onAccepted: {
                image = fileUrl
                settingsReader.setCurrentSettings("main","images",fileUrl,index)

            }
        }
    }

    Item{
        //this item represents the analog meter
        width: 128
        height: 128
        anchors.left: img.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 30
        Gauge {
            id: meterAnalog
            height: parent.height
            onMaximumValueChanged: {tickmarkStepSize = (maximumValue-minimumValue)/10}
            onMinimumValueChanged: {tickmarkStepSize = (maximumValue-minimumValue)/10}
            formatValue: function(value){
                return value.toPrecision(3)
            }

            Text {
                id: unitText
                text: "unit"
                anchors.left: meterAnalog.right
                anchors.bottom: parent.bottom
                color: "black"
            }
        }
        //This item represents the digital meter
        Item {
            id: meterDigital
            anchors.fill: parent
            Label {
                id: digitValue
                text: ""
                font.pointSize: 18
                anchors.verticalCenter: parent.verticalCenter
                anchors.left:parent.left
            }
            Label {
                id: digitUnit
                text: ""
                font.pointSize: 20
                anchors.verticalCenter: digitValue.verticalCenter
                anchors.left: digitValue.right
                anchors.leftMargin: 5
            }
        }
    }
}
