#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <calculatedeviation.h>
#include <calculatecorrelation.h>
#include <datahandler.h>
#include <datapoint.h>
#include <datalist.h>
#include "settingsreader.h"
#include <QtQuick/QQuickView>
#include <analysisui.h>
#include <calculatecorrelation.h>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    qmlRegisterType<DataPoint>();
    qmlRegisterType<DataList>();



    AnalysisUi UI;
    DataHandler* handler = new DataHandler(&app);
    SettingsReader* settings = new SettingsReader(&app);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("dataHandler",handler);
    engine.rootContext()->setContextProperty("settingsReader",settings);
             engine.rootContext()->setContextProperty("analysisUi",&UI);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
