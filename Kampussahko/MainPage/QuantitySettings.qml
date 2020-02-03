import QtQuick 2.0
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "../"

Item {
    property alias list: quantityList
    signal meterStyleChanged(var style)

    Rectangle {
        id: border
        anchors.fill: parent
        border.color: "lightgray"
        border.width: 1
        anchors.margins: 10
    }
    Column {
        anchors.fill: parent
        spacing: 2
        anchors.margins: 12

        //List that contains pickers
        QuantityList {
            id: quantityList
            width: parent.width
            height: 160
        }
        //combobox for choosing between analog and digital meters
        ComboBox {
            id: meterStyle
            anchors.margins: 2
            textRole: "text"
            currentIndex: settingsReader.getSetting("main", "meterStyle", 0)
            model: ListModel {
                id: cbItems
                ListElement {
                    text: "Analoginen"
                    style: "analog"
                }
                ListElement {
                    text: "Digitaalinen"
                    style: "digital"
                }
            }
            //if meter style is wanted to change, signal it
            onCurrentIndexChanged: {
                meterStyleChanged(cbItems.get(currentIndex).style)
                settingsReader.setCurrentSettings("main", "meterStyle",
                                                  currentIndex, 0)
            }
        }

        //this row is for the update frequency
        Row {
            anchors.margins: 2
            spacing: 2
            Text {
                text: "Taajuus (min):"
                padding: 5
            }
            SpinBox {
                id: updateFreqBox
                style: SpinBoxStyle {
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 20
                        border.color: "gray"
                        radius: 2
                    }
                }
                width: 90
                height: 30
                value: Number(settingsReader.getSetting("main",
                                                        "updateFrequency", 0))
                maximumValue: 10
                minimumValue: 1

                onValueChanged: {
                    dataHandler.setTimer(value)
                    settingsReader.setCurrentSettings("main",
                                                      "updateFrequency", value,
                                                      0)
                }
            }
        }
        //updates the latest values
        Button {
            text: "Päivitä"
            onClicked: {
                dataHandler.updateLatest()
            }
        }
    }
}
