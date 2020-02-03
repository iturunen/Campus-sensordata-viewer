import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls 2.4

Column {
    property alias endDateChosen: endDate
    property alias startDateChosen: startDate
    property alias endTimeChosen: endTime
    property alias startTimeChosen: startTime
    property alias startHoursChosen: startHours
    property alias endHoursChosen: endHours
    property alias startMinutesChosen: startMinutes
    property alias endMinutesChosen: endMinutes

    id: mainColumn
    spacing: 5
    width: 400
    height: 85
    property alias datePicked: calendarPopup

    Button {
        id: openStartCal
        y: 0
        Text {
            anchors.centerIn: parent
            text: "Valitse aikaväli"
        }
        onClicked: {
            calendarPopup.open()
            chooseDateText.text = "Valitse aloituspäivä"
        }
    }
    Row {
        Text {
            text: "Aloitus:"
            width: 100
        }
        Text {
            text: "Lopetus:"
        }
    }

    Row {
        Column {
            TextField {
                id: startDate
                activeFocusOnPress: false
                width: 100
                text: {
                    var setting = settingsReader.getSetting("analysis",
                                                            "startDate", 0)
                    if (setting === "") {
                        return Qt.formatDate(startCal.selectedDate,
                                             "dd.MM.yyyy")
                    } else {
                        return setting
                    }
                }
            }
            TextField {
                id: startTime
                activeFocusOnPress: false
                width: 100
                text: startHours.currentText + ":" + startMinutes.currentText
            }
        }

        Column {
            TextField {
                id: endDate
                activeFocusOnPress: false
                width: 100
                text: {
                    var setting = settingsReader.getSetting("analysis",
                                                            "endDate", 0)
                    if (setting === "") {
                        return Qt.formatDate(startCal.selectedDate,
                                             "dd.MM.yyyy")
                    } else {
                        return setting
                    }
                }
            }

            TextField {
                id: endTime
                activeFocusOnPress: false
                width: 100
                text: endHours.currentText + ":" + endMinutes.currentText
            }
        }
    }

    Popup {
        id: calendarPopup

        // Only closes when both dates are chosen
        // and popupClose button is clicked
        closePolicy: "NoAutoClose"
        height: 500
        width: 320

        // opens over every item
        parent: Overlay.overlay

        // disables other actions when popup is open
        modal: true

        x: 200
        y: 20

        Item {
            anchors.fill: parent

            Button {
                id: popupClose

                Text {
                    id: readyText
                    anchors.centerIn: parent
                    text: "Valmis"
                    color: "lightgray"
                }

                anchors.bottom: parent.bottom
                anchors.right: parent.right
                enabled: false
                onClicked: {
                    calendarPopup.close()
                    endCal.visible = false
                    popupClose.enabled = false
                    readyText.color = "lightgray"

                    // Can't choose earlier endTime if startDate == endDate
                    if (startDate.text === endDate.text) {
                        if (startHoursChosen.currentIndex >= endHoursChosen.currentIndex) {
                            endHours.currentIndex = startHours.currentIndex
                            if (startMinutes.currentIndex > endMinutes.currentIndex) {
                                endMinutes.currentIndex = startMinutes.currentIndex
                            }
                        }
                    }
                    settingsReader.setCurrentSettings(
                                "analysis", "startMinutes",
                                startMinutes.currentIndex.toString(), 0)
                    settingsReader.setCurrentSettings(
                                "analysis", "endMinutes",
                                endMinutes.currentIndex.toString(), 0)
                    settingsReader.setCurrentSettings(
                                "analysis", "startHours",
                                startHours.currentIndex.toString(), 0)
                    settingsReader.setCurrentSettings(
                                "analysis", "endHours",
                                endHours.currentIndex.toString(), 0)
                }
            }

            Text {
                id: chooseDateText
                x: 100
                text: "Valitse aloituspäivä"
            }

            Calendar {
                id: startCal

                y: 20

                width: 300
                height: 300
                // new Date() equivalent to current date
                maximumDate: new Date()
                minimumDate: new Date(new Date().setDate(
                                          new Date().getDate() - 14))
                onClicked: {
                    startDate.text = Qt.formatDate(startCal.selectedDate,
                                                   "dd.MM.yyyy")
                    settingsReader.setCurrentSettings(
                                "analysis", "startDate",
                                startDate.text.toString(), 0)
                    endCal.visible = true
                    chooseDateText.text = "Valitse lopetuspäivä"
                }
            }

            Calendar {
                id: endCal

                y: 20

                width: 300
                height: 300
                visible: false
                minimumDate: startCal.selectedDate
                maximumDate: new Date()
                onClicked: {
                    endDate.text = Qt.formatDate(endCal.selectedDate,
                                                 "dd.MM.yyyy")
                    settingsReader.setCurrentSettings("analysis", "endDate",
                                                      endDate.text.toString(),
                                                      0)
                    popupClose.enabled = true
                    readyText.color = "black"
                }
            }

            Rectangle {
                id: startTimePicker
                y: 330
                height: 80

                Text {
                    x: 10
                    y: 10
                    text: "Valitse aloitusaika"
                }

                ComboBox {
                    id: startHours
                    currentIndex: {
                        return Number(settingsReader.getSetting("analysis",
                                                                "startHours",
                                                                0))
                    }
                    y: 30
                    model: 24
                    width: 90
                }
                ComboBox {
                    id: startMinutes
                    currentIndex: {
                        return Number(settingsReader.getSetting("analysis",
                                                                "startMinutes",
                                                                0))
                    }
                    y: 30
                    model: 60
                    width: 90

                    anchors.left: startHours.right
                }
            }

            Rectangle {
                id: endTimePicker
                anchors.top: startTimePicker.bottom

                Text {
                    x: 10
                    y: 10
                    text: "Valitse lopetusaika"
                }

                ComboBox {
                    id: endHours
                    currentIndex: {
                        return Number(settingsReader.getSetting("analysis",
                                                                "endHours", 0))
                    }
                    y: 30
                    model: 24
                    width: 90
                }
                ComboBox {
                    id: endMinutes
                    y: 30
                    currentIndex: {
                        return Number(settingsReader.getSetting("analysis",
                                                                "endMinutes",
                                                                0))
                    }
                    model: 60
                    width: 90

                    anchors.left: endHours.right
                }
            }
        }
    }
}
