import QtQuick 2.0

Item {
    Column {
        id: quantityList
        width: parent.width
        spacing: 4
        QuantityPickerAnalysis {
            width: 150
            id: solarpanels
            currentQuantityChosen: "Aurinkopaneelit"
            comboBoxes.model: ListModel {
                id: solar
                ListElement {
                    text: "Mittari 1"
                    meterId: "pv01_inverter01_totalyield"
                    description: "Energian kulutus"
                    unit: "kWh"
                    quantityString: "solar_panels"
                }
                ListElement {
                    text: "Mittari 2"
                    meterId: "pv01_inverter02_totalyield"
                    description: "Energian kulutus"
                    unit: "kWh"
                    quantityString: "solar_panels"
                }
                ListElement {
                    text: "Mittari 3"
                    meterId: "pv01_inverter03_totalyield"
                    description: "Energian kulutus"
                    unit: "kWh"
                    quantityString: "solar_panels"
                }
                ListElement {
                    text: "Mittari 4"
                    meterId: "pv01_inverter04_totalyield"
                    description: "Energian kulutus"
                    unit: "kWh"
                    quantityString: "solar_panels"
                }
                ListElement {
                    text: "Kaikki"
                    meterId: "lv3_solarpvplant_ep_plus"
                    description: "Energian kulutus"
                    unit: "kWh"
                    quantityString: "solar_panels"
                }
            }
        }
        QuantityPickerAnalysis {
            id: energyConsumption
            width: 150
            currentQuantityChosen: "Energian kulutus"
            comboBoxes.model: ListModel {
                id: energy
                ListElement {
                    text: "Mittari 1"
                    meterId: "pm3255_hkasjk0101_eptot_imp"
                    description: "Energian kulutus"
                    unit: "kWh"
                    quantityString: "energy_consumption"
                }
            }
        }
        QuantityPickerAnalysis {
            id: cooler
            width: 150
            currentQuantityChosen: "Jäähdytys"
            comboBoxes.model: ListModel {
                id: cooling
                ListElement {
                    text: "Mittari 1"
                    meterId: "lv3_ventilation_ep_plus"
                    description: "Energian kulutus"
                    unit: "kWh"
                    quantityString: "cooling_power_usage"
                }
                ListElement {
                    text: "Mittari 2"
                    meterId: "lv3_watercooling02_ep_plus"
                    description: "Energian kulutus"
                    unit: "kWh"
                    quantityString: "cooling_power_usage"
                }
                ListElement {
                    text: "Mittari 3"
                    meterId: "lv3_watercooling01_ep_plus"
                    description: "Energian kulutus"
                    unit: "kWh"
                    quantityString: "cooling_power_usage"
                }
            }
        }
        QuantityPickerAnalysis {
            id: outsideTemperature
            width: 150
            currentQuantityChosen: "Ulkolämpötila"

            comboBoxes.model: ListModel {
                id: temperature
                ListElement {
                    text: "Mittari 1"
                    meterId: "ut01_te00"
                    description: "Lämpötila"
                    unit: "°C"
                    quantityString: "outside_temperature"
                }
                ListElement {
                    text: "Mittari 2"
                    meterId: "leeeroof_hmp155_t"
                    description: "Lämpötila"
                    unit: "°C"
                    quantityString: "outside_temperature"
                }
            }
        }
    }
}
