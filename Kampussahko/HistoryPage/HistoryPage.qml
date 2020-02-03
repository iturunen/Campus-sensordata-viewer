import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtCharts 2.2
import "../"

Page {
    id: historyPage
    width: 1080
    height: 720

    Connections {
        target: dataHandler
        onHistoryUpdated: {
            for (var i = 0; i < chartList.charts.length; ++i) {
                updateCharts(i, historyPicker.startDateChosen,
                             historyPicker.endDateChosen)
            }
        }
    }
    function changeMeter(i) {
        updateCharts(i, historyPicker.startDateChosen,
                     historyPicker.endDateChosen)
    }

    //hides the chart with i being the index
    function toggleCharts(i) {
        settingsReader.setCurrentSettings(
                    "history", "selectedQuantities",
                    historyQuantityList.pickers[i].quantityChecked.checked, i)
        var chart = chartList.charts[i]
        chart.visible = settingsReader.getSetting("history",
                                                  "selectedQuantities",
                                                  i) === "true"
    }
    //Updates the charts if data is updated or meter is changed
    function updateCharts(i, dateFrom, dateTo) {
        if (historyQuantityList.pickers[i].initialized) {
            var picker = historyQuantityList.pickers[i].meterPicker
            var chart = chartList.charts[i]
            var current = picker.currentIndex

            var id = picker.model.get(current).meterId

            var data = dataHandler.historyData(id)
            if (data !== null) {
                chart.dataPoints.clear()
                // add each historyData point to LineSeries
                var list = data.data()
                settingsReader.setCurrentSettings("history", "selectedMeters",
                                                  current, i)
                for (var j = 0; j < list.length; ++j) {

                    chart.dataPoints.append(toMsecsSinceEpoch(list[j].date),
                                            list[j].value)
                    chart.dataPoints.axisX.min = dataHandler.setJsonDatetime(
                                "startDatetime")
                    chart.dataPoints.axisX.max = dataHandler.setJsonDatetime(
                                "endDatetime")
                    chart.dataPoints.axisY.min = data.min() - 1
                    chart.dataPoints.axisY.max = data.max() + 1
                }
            }
        }
    }

    function toMsecsSinceEpoch(date) {
        var msecs = date.getTime()
        return msecs
    }
    Connections {
        target: historyQuantityList
        onInitialized: {
            for (var i = 0; i < historyQuantityList.pickers.length; ++i) {
                historyQuantityList.pickers[i].meterPicker.currentIndex = Number(
                            settingsReader.getSetting("history",
                                                      "selectedMeters", i))
            }
        }
    }

    //Container for settings
    Item {
        id: settings
        width: parent.width * 2 / 7
        height: parent.height

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
            //connect each picker to a chart
            Component.onCompleted: {
                for (var i = 0; i < historyQuantityList.pickers.length; ++i) {
                    historyQuantityList.pickers[i].checkChanged.connect(
                                toggleCharts)
                    historyQuantityList.pickers[i].meterChanged.connect(
                                changeMeter)
                    historyQuantityList.pickers[i].quantityChecked.checked
                            = settingsReader.getSetting("history",
                                                        "selectedQuantities",
                                                        i) === "true"
                    toggleCharts(i)
                }
            }
            QuantityList {
                id: historyQuantityList
                width: parent.width
                height: 160
            }
            DatePicker {
                id: historyPicker
                datePicked.onClosed: {
                    dataHandler.setDatetimes(startDateChosen.text,
                                             endDateChosen.text,
                                             startTimeChosen.text,
                                             endTimeChosen.text)

                    dataHandler.updateHistory(
                                dataHandler.setJsonDatetime("startDatetime"),
                                dataHandler.setJsonDatetime("endDatetime"))
                }
            }
        }
    }
    //Container for chosen graphs
    ChartList {
        id: chartList
        width: parent.width * 5 / 7
        height: parent.height
        anchors.left: settings.right
    }
}
