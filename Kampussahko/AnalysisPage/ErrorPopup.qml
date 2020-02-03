import QtQuick.Controls 2.2
import QtQuick 2.4

Item {
    id: errorItem

    Connections {
        target: dataHandler
        onErrorOccured: {
            errorPopup.open()
        }
    }

    Popup {
        id: errorPopup
        width: 0
        height: 0
        x: 250
        y: 250

        TextMetrics {
            id: textMetrics
            font.family: "Arial"
            font.pixelSize: 20
            text: ""
        }
        Rectangle {
            id: errorRect
            height: textMetrics.height + 20
            width: textMetrics.width + 20
            border.color: "red"
            Text {
                id: errorText
                color: "red"
                text: textMetrics.text
                font: textMetrics.font
                x: errorRect.x + 10
                y: errorRect.y + 10
            }
        }
        onOpened: textMetrics.text = dataHandler.popupError
    }
}
