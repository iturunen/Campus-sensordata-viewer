import QtQuick 2.0

Item {
    //You can access the charts from here
    property list<ChartTemplate> charts: [
        ChartTemplate {
        },
        ChartTemplate {
        },
        ChartTemplate {
        },
        ChartTemplate {
        }
    ]
    property var titles: ["Aurinkopaneelit", "Energiankulutus", "Jäähdytys", "Ulkolämpötila"]
    Component.onCompleted: {
        for (var i = 0; i < charts.length; ++i) {
            var chart = charts[i]
            chart.quantity.title = titles[i]
        }
    }

    Rectangle {
        anchors.fill: parent
        border.color: "lightgray"
        border.width: 1
        anchors.margins: 10
    }
    Grid {
        id: currentGrid
        anchors.fill: parent
        anchors.margins: 12
        spacing: 2
        columns: 2
        children: charts
    }
}
