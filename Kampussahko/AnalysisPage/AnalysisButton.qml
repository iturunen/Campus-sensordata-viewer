import QtQuick 2.0
import QtQuick.Controls 2.2


//popupButton needed to display set x- and y-data
Item {
    property alias popupButtonText: popupButton.text
    property alias popupButtonParrent: popupButton.parent
    property alias popupItem: popup

    Button {
        id: popupButton
        text: "text"
        anchors.fill: parent
        onClicked: popup.open()

        Popup {
            id: popup
            width: quantityBox.width
            height: quantityBox.height
            x: quantityBox.x
            y: quantityBox.y - 100
            QuantityListAnalysis {
            }
        }
    }
}
