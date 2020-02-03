import QtQuick 2.0
import QtQuick.Controls 2.2


//QuantityPickerAnalysis picks quantitys data needed to analysisBox, dataGraph and in future to c++ dataHandler
Item {
    id: quantityPickerAnalysis
    width: parent.width
    height: 30
    property alias currentQuantityChosen: textBox.text
    property alias comboBoxes: comboBox
    property string idX: "X"
    property string idY: "Y"
    property string quantityX: "X"
    property string quantityY: "Y"
    property string popupButtonTextX: ""
    property string popupButtonTextY: ""
    property string currentTitleX: ""
    property string currentTitleY: ""

    Rectangle {
        id: rectBox
        height: textBox.height
        width: parent.width
        Text {
            id: textBox
            text: qsTr("text")
            width: 150
            height: 100
        }
    }

    ComboBox {
        id: comboBox
        anchors.margins: 2
        anchors.left: rectBox.right
        anchors.top: rectBox.top
        textRole: "text"
        property string titleX: ""
        property string titleY: ""
        onActivated: {

            if (popupButtonParrent == buttonX) {
                popupButtonText = "X: " + currentQuantityChosen
                quantityXChosen.text = "X: " + currentText + ":"

                if (currentQuantityChosen == "Ulkolämpötila") {
                    unitX.text = temperature.get(currentIndex).unit
                    idX = temperature.get(currentIndex).meterId
                    quantityX = temperature.get(currentIndex).quantityString
                } else if (currentQuantityChosen == "Jäähdytys") {
                    unitX.text = cooling.get(currentIndex).unit
                    idX = cooling.get(currentIndex).meterId
                    quantityX = cooling.get(currentIndex).quantityString
                } else if (currentQuantityChosen == "Aurinkopaneelit") {
                    unitX.text = solar.get(currentIndex).unit
                    idX = solar.get(currentIndex).meterId
                    quantityX = solar.get(currentIndex).quantityString
                } else if (currentQuantityChosen == "Energian kulutus") {
                    unitX.text = energy.get(currentIndex).unit
                    idX = energy.get(currentIndex).meterId
                    quantityX = energy.get(currentIndex).quantityString
                }

                dataHandler.setQmlId("X", idX)
                dataHandler.setQmlQuantity("X", quantityX)
                titleX = currentQuantityChosen + ": " + currentText + ":" + " (" + unitX.text + ")"
                dataGraph.axisXTitle = titleX
                settingsReader.setCurrentSettings("analysis", "axisTitleX",
                                                  titleX, 0)
                settingsReader.setCurrentSettings("analysis", "meterX",
                                                  currentQuantityChosen, 0)
                analysisUi.xPicked()
            }

            if (popupButtonParrent == buttonY) {
                popupButtonText = "Y: " + currentQuantityChosen
                quantityYChosen.text = "Y: " + currentText + ":"
                if (currentQuantityChosen == "Ulkolämpötila") {
                    unitY.text = temperature.get(currentIndex).unit
                    idY = temperature.get(currentIndex).meterId
                    quantityY = temperature.get(currentIndex).quantityString
                } else if (currentQuantityChosen == "Jäähdytys") {
                    unitY.text = cooling.get(currentIndex).unit
                    idY = cooling.get(currentIndex).meterId
                    quantityY = cooling.get(currentIndex).quantityString
                } else if (currentQuantityChosen == "Aurinkopaneelit") {
                    unitY.text = solar.get(currentIndex).unit
                    idY = solar.get(currentIndex).meterId
                    quantityY = solar.get(currentIndex).quantityString
                } else if (currentQuantityChosen == "Energian kulutus") {
                    unitY.text = energy.get(currentIndex).unit
                    idY = energy.get(currentIndex).meterId
                    quantityY = energy.get(currentIndex).quantityString
                }

                dataHandler.setQmlId("Y", idY)
                dataHandler.setQmlQuantity("Y", quantityY)
                titleY = currentQuantityChosen + ": " + currentText + ":" + " (" + unitY.text + ")"
                dataGraph.axisYTitle = titleY
                settingsReader.setCurrentSettings("analysis", "axisTitleY",
                                                  titleY, 0)
                settingsReader.setCurrentSettings("analysis", "meterY",
                                                  currentQuantityChosen, 0)
                analysisUi.yPicked()
            }
        }
    }
}
