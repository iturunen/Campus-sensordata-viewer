import QtQuick.Controls 2.2
import QtQuick.Controls 1.4
import QtCharts 2.2
import QtQuick 2.4

Item {
    //Datalists to simulate working of DataGraph
    //property alias dataX: dataGraph(dataHandler.returnAnalysisDataX)
    // property alias dataY: dataGraph(dataHandler.returnAnalysisDataY)
    anchors.fill: parent
    property var borders: []
    property alias axisXTitle: valueAxisX.titleText
    property alias axisYTitle: valueAxisY.titleText
    property string factorX: ""
    property string factorY: ""

    Connections {
        target: dataHandler
        onAnalysisUpdated: {
            series1.insertData()
        }
    }

    ChartView {

        id: chartView
        title: "Kuvaaja"
        anchors.fill: parent
        antialiasing: true
        property bool openGL: true

        ValueAxis {
            id: valueAxisX
            titleText: "XX"

            min: -10
            max: 10
            tickCount: 10
        }
        ValueAxis {
            id: valueAxisY
            titleText: "YY"
            min: -10
            max: 10
            tickCount: 10
        }

        ScatterSeries {
            property var dataListX: []
            property var dataListY: []

            id: series1
            axisX: valueAxisX
            axisY: valueAxisY
            useOpenGL: chartView.openGL
            //returns series from last session
            Component.onCompleted: {
                //if serriesdata is readed from settings file it is intialized here to serries.
                series1.markerSize = 5
                var maxX = settingsReader.getSetting("analysis", "maxX", 0)
                var minX = settingsReader.getSetting("analysis", "minX", 0)
                var maxY = settingsReader.getSetting("analysis", "maxY", 0)
                var minY = settingsReader.getSetting("analysis", "minY", 0)
                if (maxX !== "") {
                    axisX.max = Number(maxX)
                } else {
                    axisX.max = 10
                }
                if (minX !== "") {
                    axisX.min = Number(minX)
                } else {
                    axisX.max = -10
                }
                if (maxY !== "") {
                    axisY.max = Number(maxY)
                } else {
                    axisY.max = 10
                }
                if (minY !== "") {
                    axisY.min = Number(minY)
                } else {
                    axisY.min = -10
                }

                dataListX = settingsReader.getDatalist("X")
                dataListY = settingsReader.getDatalist("Y")

                if (dataListX.length > 0 && dataListY.length > 0) {
                    for (var i = 0; i < dataListX.length; i++) {

                        var x = Number(dataListX[i])
                        var y = Number(dataListY[i])
                        series1.append(x, y)
                    }
                }
            }
            function insertData() {

                borders = analysisUi.updateSeries(dataHandler.getAnalysisData,
                                                  series1)
                series1.markerSize = 5
                series1.useOpenGL = chartView.openGL
                //factor is for qml axistitle if datavalues are so large they have divided with certain factor in updatrseries method
                //If factor is already set in graph this asserts its not saved again
                if (factorX !== analysisUi.getFactorX()) {
                    factorX = analysisUi.getFactorX()
                } else {
                    factorX = ""
                }
                if (factorY !== analysisUi.getFactorY()) {
                    factorY = analysisUi.getFactorY()
                } else {
                    factorY = ""
                }
                var settingX = factorX
                settingsReader.setCurrentSettings("analysis", "factorX",
                                                  settingX.toString(), 0)
                var settingY = factorY
                settingsReader.setCurrentSettings("analysis", "factorY",
                                                  settingY.toString(), 0)
                axisXTitle = axisXTitle + factorX
                axisYTitle = axisYTitle + factorY
                //setold factor to string
                factorX = analysisUi.getFactorX()
                factorY = analysisUi.getFactorY()
                //Borders  from c++ method that returned [Xmin,Xmax,Ymin,Ymax]
                var intervalX = borders[1] - borders[0]
                var intervalY = borders[3] - borders[2]

                // scaling axis: because grid is seperatet to 10 intervals
                // scaling of plot bordes is done *1/10 scalefactor so points wont come
                // out of axis.
                if (intervalX == 0) {
                    axisX.min = borders[0] - 1
                    axisX.max = borders[0] + 1
                } else {
                    axisX.min = borders[0] - intervalX / 10
                    axisX.max = borders[1] + intervalX / 10
                }

                if (intervalY == 0) {
                    axisY.min = borders[2] - 1
                    axisY.max = borders[2] + 1
                } else {
                    axisY.min = borders[2] - intervalY / 10
                    axisY.max = borders[3] + intervalY / 10
                }

                var minY = axisY.min
                var maxY = axisY.max
                var minX = axisX.min
                var maxX = axisX.max

                settingsReader.setCurrentSettings("analysis", "minX",
                                                  minX.toString(), 0)
                settingsReader.setCurrentSettings("analysis", "maxX",
                                                  maxX.toString(), 0)
                settingsReader.setCurrentSettings("analysis", "minY",
                                                  minY.toString(), 0)
                settingsReader.setCurrentSettings("analysis", "maxY",
                                                  maxY.toString(), 0)
            }
        }
    }
}
