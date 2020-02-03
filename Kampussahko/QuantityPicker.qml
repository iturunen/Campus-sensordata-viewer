import QtQuick 2.0
import QtQuick.Controls 2.2


//Item to be listed
Item {


    property alias quantityChecked: check
    property alias meterPicker: meterPicker
    property int index
    property bool initialized: false

    signal checkChanged(int index)
    signal meterChanged(int index)
    CheckBox {
        id: check
        text: qsTr("")
        padding: 5
        onCheckStateChanged: checkChanged(index)
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (quantityChecked.checked == true) {
                quantityChecked.checked = false
            } else {
                quantityChecked.checked = true
            }
        }
    }
    ComboBox {
        id: meterPicker
        anchors.margins: 2
        anchors.right: parent.right
        anchors.verticalCenter: check.verticalCenter
        textRole: "text"
        onCurrentIndexChanged: meterChanged(index)
    }
}
