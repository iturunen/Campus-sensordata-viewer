# Repository for project Kampussahko

With this program you are able to read data from the meters placed around 
Kampusareena, check their values from two weeks back and analyze data
(correlation, deviaton of different quantities).

## Running the program

In order to run the program, at this moment the user has to download the 
repository to their own device and open the project on QtCreator (preferrably 
Qt version 5.10 or later). There the program can be run like any other project.
 
## Directory tree
```
Kampussahko
├── Images
│       ├── cooler.png
│       ├── energy.png
│       ├── sun.png
│       └── temperature.png
├── AnalysisPage
│       ├── AnalysisButton.qml
│       ├── AnalysisPage.qml
│       ├── AnalysisUpdater.qml
│       ├── DataGraph.qml
│       ├── DatePicker.qml
│       ├── ErrorMessage.qml
│       ├── ErrorPopup.qml
│       ├── QuantitylistAnalysis.qml
│       └── QuantityPickerAnalysis.qml
├── MainPage
│       ├── MainPage.qml
│       ├── Meter.qml
│       ├── MeterList.qml
│       └── QuantitySettings.qml
├── HistoryPage
│       ├── ChartList.qml
│       ├── ChartTemplate.qml
│       └── HistoryPage.qml
├── Kampussahko.pro
├── QuantityList.qml
├── QuantityListModels.qml
├── QuantityPicker.qml
├── analysisdataui.cpp
├── calculatecorrelation.cpp
├── calculatecorrelation.h
├── calculatedeviation.cpp
├── calculatedeviation.h
├── datahandler.cpp
├── datahandler.h
├── datalist.cpp
├── datalist.h
├── datapoint.cpp
├── datapoint.h
├── datarequester.cpp
├── datarequester.h
├── default.json
├── jsondatareader.cpp
├── jsondatareader.h
├── main.cpp
├── main.qml
├── qml.qrc
├── settingsreader.cpp
├── settingsreader.h
└── qtquickcontrols2.conf
```
