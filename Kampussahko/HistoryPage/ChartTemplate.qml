import QtQuick 2.0
import QtCharts 2.2
import QtQuick.Controls 2.2

Item {
    property alias quantity: quantity
    property alias dataPoints: dataSeries

    height: 330
    width: 375

    ChartView {
        id: quantity
        anchors.fill: parent
        antialiasing: true

        legend.visible: false

        LineSeries {
            id: dataSeries
            axisX: DateTimeAxis {
                format: "dd.MM hh:mm"
                labelsAngle: 75
            }
            axisY: ValueAxis {
                min: 0
                max: 150
            }
        }
    }
}
