import QtQuick 2.0
import QtQuick.Controls 2.2


//whole list of quantitypickers.

Item {
    //List of pickers
    property list<QuantityPicker> pickers:[QuantityPicker{},QuantityPicker{},QuantityPicker{},QuantityPicker{}]

    //list of picker texts
    property var pickerTexts : ["Aurinkopaneelit","Energiankulutus","Ilmastointi","Ulkolämpötila"]
    //list of models to be assigned in list elements
    property var models: QuantityListModels{}

    signal initialized()
    //function to initialize list elements
    function initialize(){
        for(var i = 0;i < pickers.length;i++){
            var picker = pickers[i]
            picker.index = i
            picker.width = width
            picker.height =  30
            picker.quantityChecked.text = pickerTexts[i]
            picker.meterPicker.model = models.models[i]
            picker.initialized = true
        }
        initialized()
    }
    //when completed, call this
    Component.onCompleted: {
        //add the pickers to column
        initialize()
    }

    Rectangle {
        anchors.fill: parent
        border.color: "lightgray"
        border.width: 1
    }
    Flickable {
        id: list
        anchors.fill: parent
        anchors.margins: 2
        Column {
            id: column
            width: parent.width
            spacing: 4
            children: pickers
        }
    }
}
