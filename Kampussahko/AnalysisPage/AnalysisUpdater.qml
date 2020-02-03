import QtQuick 2.0

Item {
    //this item updates analysys datagraph if user has chosen quantity x and y and picked dateinterval
    id: updateCurrentAnalysis
    function allowUpdate() {
        if (analysisUi.xIsPicked && analysisUi.yIsPicked
                && analysisUi.datesArePicked) {
            dataHandler.updateAnalysis(
                        dataHandler.setJsonDatetime("startDatetime"),
                        dataHandler.setJsonDatetime("endDatetime"),
                        dataHandler.setQmlQuantity("X"),
                        dataHandler.setQmlId("X"),
                        dataHandler.setQmlQuantity("Y"),
                        dataHandler.setQmlId("Y"))

            valueX.text = dataHandler.getMeanX
            valueY.text = dataHandler.getMeanY
            correlationValue.text = dataHandler.getCorrelation

            settingsReader.setCurrentSettings("analysis", "meanX",
                                              valueX.text.toString(), 0)

            settingsReader.setCurrentSettings("analysis", "meanY",
                                              valueY.text.toString(), 0)

            settingsReader.setCurrentSettings("analysis", "correlation",
                                              correlationValue.text.toString(),
                                              0)
        }
    }
    Connections {
        target: analysisUi
        onXPicked: {
            analysisUi.pickX(true)
            updateCurrentAnalysis.allowUpdate()
        }
    }

    Connections {
        target: analysisUi
        onYPicked: {
            analysisUi.pickY(true)
            updateCurrentAnalysis.allowUpdate()
        }
    }
    Connections {
        target: analysisUi
        onDatesPicked: {
            analysisUi.pickDates(true)
            updateCurrentAnalysis.allowUpdate()
        }
    }
}
