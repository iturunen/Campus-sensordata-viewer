import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.0
import "MainPage/"
import "AnalysisPage/"
import "HistoryPage/"

ApplicationWindow {

    visible: true
    width: 1080
    height: 720
    title: qsTr("Kampussähkö")
    minimumHeight: height
    maximumHeight: height
    minimumWidth: width
    maximumWidth: width

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        MainPage {
        }

        HistoryPage {
        }

        AnalysisPage {
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Aloitussivu")
        }
        TabButton {
            text: qsTr("Historia")
        }
        TabButton {
            text: qsTr("Analyysi")
        }
    }
}
