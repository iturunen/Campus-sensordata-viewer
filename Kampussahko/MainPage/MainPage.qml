import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Page {

    //Updates the meter values if data is changed or meter is changed
    function updateMeters(i) {

        if (settings.list.pickers[i].initialized) {
            var picker = settings.list.pickers[i].meterPicker
            var meter = meterList.meters[i]
            var current = picker.currentIndex
            var id = picker.model.get(current).meterId
            var data = dataHandler.latestData(id)
            meter.value = data.value
            meter.unit = data.unit
            settingsReader.setCurrentSettings("main", "selectedMeters",
                                              current, i) //save changes
        }
    }

    //hides/shows meter if checkbox is unchecked/checked
    //i is the index of the meter and picker
    function toggleMeters(i) {
        settingsReader.setCurrentSettings(
                    "main", "selectedQuantities",
                    settings.list.pickers[i].quantityChecked.checked, i)

        var meter = meterList.meters[i]
        meter.visible = settingsReader.getSetting("main", "selectedQuantities",
                                                  i) === "true"
    }

    //change the meters to digital/analog
    function changeMeterStyle(style) {

        for (var i = 0; i < meterList.meters.length; i++) {
            var meter = meterList.meters[i]
            meter.state = style
        }
        settingsReader.setCurrentSettings("main", "meterStyle", style, 1)
    }

    //datahandler tells UI to be updated
    Connections {
        target: dataHandler
        onLatestUpdated: {
            for (var i = 0; i < meterList.meters.length; i++) {
                updateMeters(i)
            }
        }
    }
    Connections {
        target: settings.list
        onInitialized: {
            for (var i = 0; i < settings.list.pickers.length; ++i) {
                settings.list.pickers[i].meterPicker.currentIndex = Number(
                            settingsReader.getSetting("main",
                                                      "selectedMeters", i))
                updateMeters(i)
            }
        }
    }

    width: 1080
    height: 720

    //Container for settings
    QuantitySettings {
        id: settings
        width: parent.width * 2 / 7
        height: parent.height
        Component.onCompleted: {
            for (var i = 0; i < list.pickers.length; ++i) {
                list.pickers[i].checkChanged.connect(
                            toggleMeters) //connect the checkboxes to the meters to be shown
                list.pickers[i].meterChanged.connect(
                            updateMeters) //toggle meter to chosen meter
                list.pickers[i].quantityChecked.checked = settingsReader.getSetting(
                            "main", "selectedQuantities", i) === "true"
                toggleMeters(i)
            }
            meterStyleChanged.connect(
                        changeMeterStyle) // connect meter style combobox to meters
        }
    }
    //Container for showing current values of chosen quantities
    MeterList {
        id: meterList
        width: parent.width * 5 / 7
        height: parent.height
        anchors.left: settings.right
    }
}
