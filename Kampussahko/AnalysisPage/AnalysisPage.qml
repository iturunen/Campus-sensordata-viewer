import QtQuick.Controls 2.2
import QtQuick 2.4


// 2/3 page's height is used by datagraph and the rest is reserved to analysis tools. Analysistool is split to quantityBox, timeBox and analysisBox
Page {
    property alias quantityYChosen: quantityY
    property alias quantityXChosen: quantityX
    property alias valueYChosen: valueY
    property alias valueXChosen: valueX
    property alias correlationValueText: correlationValue.text
    property alias axisXTitle: dataGraph

    id: analysisPage
    width: 1080
    height: 720

    Item {

        id: pageItem
        property double graphHeightPropotion: 2 / 3
        property double graphWidthPropotion: 2 / 5
        width: parent.width
        height: parent.height
        anchors.fill: parent
        anchors.margins: 10

        AnalysisUpdater {
        }

        ErrorMessage {
            id: errorMessage
        }
        Rectangle {
            //in graphBorder is everything needed to display DataGraph
            id: graphBorder
            anchors.right: parent.right
            anchors.top: parent.top
            width: parent.width
            height: parent.height
            border.color: "lightgray"
            border.width: 1
            Rectangle {
                id: displayGraph
                anchors.top: parent.top
                anchors.right: parent.right
                width: parent.width
                height: parent.height * pageItem.graphHeightPropotion
                border.color: "lightgray"
                border.width: 1

                DataGraph {
                    id: dataGraph
                    axisXTitle: {

                        var setting = settingsReader.getSetting("analysis",
                                                                "axisTitleX", 0)
                        var setting2 = settingsReader.getSetting("analysis",
                                                                 "factorX", 0)

                        if (setting === "") {
                            return "X"
                        } else {

                            return "X: " + setting + setting2
                        }
                    }
                    axisYTitle: {

                        var setting = settingsReader.getSetting("analysis",
                                                                "axisTitleY", 0)
                        var setting2 = settingsReader.getSetting("analysis",
                                                                 "factorY", 0)

                        if (setting === "") {
                            return "Y"
                        } else {

                            return "Y: " + setting + setting2
                        }
                    }
                }
            }
            Rectangle {
                id: settingsBox
                anchors.top: displayGraph.bottom
                width: parent.width
                height: parent.height - displayGraph.height
                border.color: "lightgray"
                border.width: 1
                // in quantityBox  user can set meters he/she wants analyze
                Rectangle {
                    id: quantityBox
                    anchors.top: parent.top
                    anchors.left: parent.left
                    width: parent.width * pageItem.graphWidthPropotion
                    height: parent.height
                    Column {
                        spacing: 10
                        Rectangle {
                            id: headerBox
                            width: quantityBox.width
                            height: quantityBoxHeader.height
                            Text {
                                id: quantityBoxHeader
                                text: "Valitse suureet:"
                                font.pixelSize: 20
                            }
                        }
                        //Buttons pick up current text, units and quantities displayed in modlel and transmits them to analysisBox and  dataGraph
                        AnalysisButton {
                            id: buttonX
                            popupButtonText: {

                                var setting = settingsReader.getSetting(
                                            "analysis", "meterX", 0)

                                if (setting === "") {
                                    return "Valitse X"
                                } else {

                                    return "X: " + setting
                                }
                            }
                            width: quantityBox.width / 3 //parent.width
                            height: (quantityBox.height - headerBox.height) / 3 //parent.height
                        }
                        AnalysisButton {
                            id: buttonY
                            popupButtonText: {
                                var setting = settingsReader.getSetting(
                                            "analysis", "meterY", 0)
                                if (setting === "") {
                                    return "Valitse Y"
                                } else {
                                    return "Y: " + setting
                                }
                            }

                            width: quantityBox.width / 3 //parent.width
                            height: (quantityBox.height - headerBox.height) / 3 //parent.height
                        }
                    }
                }
                // in timeBox  user can set timespan he/she for analysisdata
                Rectangle {
                    id: timeBox
                    width: parent.width * pageItem.graphWidthPropotion
                    height: parent.height
                    anchors.left: quantityBox.right
                    Text {
                        id: timeText
                        anchors.left: parent.left
                        anchors.top: parent.top

                        text: "Valitse aikaväli:"
                        font.pixelSize: 20
                    }

                    DatePicker {
                        //Picks up current date chosen. If date is not valid it wont be save for the updateAnalysis
                        id: analysisPicker
                        anchors.margins: 20
                        anchors.top: timeText.bottom

                        datePicked.onClosed: {
                            if (startDateChosen.text === endDateChosen.text) {
                                if (startHoursChosen.currentIndex > endHoursChosen.currentIndex) {
                                    dataHandler.setPopupError(
                                                "Virhe: aloitusajan on oltava suurempaa kuin lopetusajan")
                                    dataHandler.errorOccured()
                                } else {
                                    if (startMinutesChosen.currentIndex
                                            >= endMinutesChosen.currentIndex) {
                                        dataHandler.setPopupError(
                                                    "Virhe: aloitusajan on oltava suurempaa kuin lopetusajan")
                                        dataHandler.errorOccured()
                                    } else {
                                        dataHandler.setDatetimes(
                                                    startDateChosen.text,
                                                    endDateChosen.text,
                                                    startTimeChosen.text,
                                                    endTimeChosen.text)
                                        analysisUi.datesPicked()
                                    }
                                }
                            } else {
                                dataHandler.setDatetimes(startDateChosen.text,
                                                         endDateChosen.text,
                                                         startTimeChosen.text,
                                                         endTimeChosen.text)
                                analysisUi.datesPicked()
                            }
                        }
                    }

                    //analysisBox displays analyzed quantities mean and correlation
                    Rectangle {
                        id: analysisBox
                        width: parent.width - timeBox.width - quantityBox.width
                        height: parent.height
                        anchors.left: timeBox.right
                        border.color: "lightgray"

                        Column {
                            anchors.top: parent.top
                            anchors.margins: 10
                            spacing: 10
                            width: parent.width
                            height: parent.height

                            Label {
                                height: parent.height * 1 / 5
                                width: parent.width
                                anchors.left: parent.left
                                anchors.margins: 5

                                Text {
                                    id: meanText
                                    text: qsTr("Keskiarvot: ")
                                    font.pointSize: 15
                                    font.bold: true
                                }
                            }
                            Row {
                                height: parent.height * 1 / 5
                                width: parent.width
                                spacing: 5
                                anchors.left: parent.left
                                anchors.margins: 5
                                Text {
                                    id: quantityX
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: "X-muuttuja"
                                }
                                Text {
                                    id: valueX
                                    font.pointSize: 10
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: {
                                        var setting = settingsReader.getSetting(
                                                    "analysis", "meanX", 0)
                                        if (setting === "") {
                                            return ""
                                        } else {
                                            return setting
                                        }
                                    }
                                }
                                Text {
                                    id: unitX
                                    visible: true
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: ""
                                }
                            }
                            Row {
                                height: parent.height * 1 / 5
                                width: parent.width
                                spacing: 2
                                anchors.left: parent.left
                                anchors.margins: 5

                                Text {
                                    id: quantityY
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: "Y-muuttuja "
                                }
                                Text {
                                    id: valueY
                                    font.pointSize: 10
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: {
                                        var setting = settingsReader.getSetting(
                                                    "analysis", "meanY", 0)
                                        if (setting === "") {
                                            return ""
                                        } else {
                                            return setting
                                        }
                                    }
                                }

                                Text {
                                    id: unitY
                                    visible: true
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: ""
                                }
                            }
                            Row {
                                height: parent.height * 1 / 5
                                width: parent.width
                                spacing: 2
                                anchors.left: parent.left
                                anchors.margins: 5

                                Text {
                                    id: correlationXY
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: qsTr("Korrelaatio: ")
                                    font.pointSize: 15
                                    font.bold: true
                                }
                                Label {

                                    id: correlationValue
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.leftMargin: 4
                                    font.pointSize: 10
                                    text: {
                                        var setting = settingsReader.getSetting(
                                                    "analysis",
                                                    "correlation", 0)
                                        if (setting === "") {
                                            return ""
                                        } else {
                                            return setting
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
