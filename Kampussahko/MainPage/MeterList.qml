import QtQuick 2.0

Item {
    //you can access the meters with this
    property list<Meter> meters: [Meter{},Meter{},Meter{},Meter{}]


    Component.onCompleted: {
        //initialize meters
        for(var i = 0;i < meters.length; ++i){
            var meter = meters[i]
            meter.image = settingsReader.getSetting("main","images",i)
            meter.maximum = 5
            meter.minimum = 0
            meter.index  = i

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
        children: meters

    }
}
