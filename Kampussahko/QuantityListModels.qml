import QtQuick 2.0

Item {
    property list<ListModel> models: [
        ListModel {
            ListElement {
                text: "Mittari 1"
                meterId: "pv01_inverter01_totalyield"
            }
            ListElement {
                text: "Mittari 2"
                meterId: "pv01_inverter02_totalyield"
            }
            ListElement {
                text: "Mittari 3"
                meterId: "pv01_inverter03_totalyield"
            }
            ListElement {
                text: "Mittari 4"
                meterId: "pv01_inverter04_totalyield"
            }
            ListElement {
                text: "Kaikki"
                meterId: "lv3_solarpvplant_ep_plus"
            }
        },
        ListModel {
            ListElement {
                text: "Mittari 1"
                meterId: "pm3255_hkasjk0101_eptot_imp"
            }
        },
        ListModel {
            ListElement {
                text: "Mittari 1"
                meterId: "lv3_ventilation_ep_plus"
            }
            ListElement {
                text: "Mittari 2"
                meterId: "lv3_watercooling02_ep_plus"
            }
            ListElement {
                text: "Mittari 3"
                meterId: "lv3_watercooling01_ep_plus"
            }
        },
        ListModel {
            ListElement {
                text: "Mittari 1"
                meterId: "ut01_te00"
            }
            ListElement {
                text: "Mittari 2"
                meterId: "leeeroof_hmp155_t"
            }
        }
    ]
}
