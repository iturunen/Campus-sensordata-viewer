#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QObject>
#include <QtCharts>
#include <QList>
#include <QTimer>
#include <QMap>
#include <QString>
#include <QQmlListProperty>
#include <QVariantList>
#include <QVariant>
#include <iterator>
#include "datarequester.h"
#include "datalist.h"
#include "calculatecorrelation.h"
#include "settingsreader.h"


//Map to make creating requesters easier. Key is quantity and data is list of ids
const QMap<QString,QList<QString>> meters =
{{"solar_panels",{"pv01_inverter01_totalyield","pv01_inverter02_totalyield",
                  "pv01_inverter03_totalyield","pv01_inverter04_totalyield",
                  "lv3_solarpvplant_ep_plus"}},
 {"energy_consumption",{"pm3255_hkasjk0101_eptot_imp"}},
 {"cooling_power_usage",{"lv3_ventilation_ep_plus",
                         "lv3_watercooling02_ep_plus",
                         "lv3_watercooling01_ep_plus"}},
 {"outside_temperature",{"ut01_te00","leeeroof_hmp155_t"}} };



/*QObject that communicates between qml ui and datarequesters*/

class DataHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getMeanX READ getMeanX NOTIFY analysisUpdated)
    Q_PROPERTY(QString getMeanY READ getMeanY NOTIFY analysisUpdated)
    Q_PROPERTY(QString getCorrelation READ getCorrelation NOTIFY analysisUpdated)
    Q_PROPERTY(QVector<QPointF>getAnalysisData READ getAnalysisData NOTIFY analysisUpdated)
    Q_PROPERTY(QString popupError READ popupError WRITE setPopupError NOTIFY errorOccured)


public:
    explicit DataHandler(QObject *parent = nullptr);
    //returns the latest value of a meter with id

    Q_INVOKABLE DataPoint* latestData(QString id);

    //returns the historydata of a meter with id
    Q_INVOKABLE DataList* historyData(QString id) const;

    //returns the analysisdata with axis being "X" or "Y"
    Q_INVOKABLE DataList* analysisData(QString axis);
//these Q_INVOKABLE methods below set users chosen parametres fand are used to user datarequest
    Q_INVOKABLE void setQmlId(QString axe,QString id);
    Q_INVOKABLE void setQmlQuantity(QString axe,QString quantity);
    Q_INVOKABLE void setDatetimes(QString startDate,
                                   QString endDate,
                                   QString startTime,
                                   QString endTime);
    Q_INVOKABLE void convertQmlDatetimes(QString startDate,
                                         QString endDate,
                                         QString startTime,
                                         QString endTime);
    Q_INVOKABLE QString setQmlId(QString axe);
    Q_INVOKABLE QString setJsonDatetime(QString dateType);
    Q_INVOKABLE QString setQmlQuantity(QString axe);
    QString setResolution(QString startDatetime,QString endDatetime);
    std::shared_ptr<QList<double>> extrctDataList(QString axe);
    QString getMeanY();
    QString getMeanX();
    QString getCorrelation();
    QVector<QPointF>getAnalysisData();
    void dataToAnalysisUI(QVector<double> uiDataX, QVector<double> uiDataY);

    //return to qml errortext
  Q_INVOKABLE   QString popupError();
   Q_INVOKABLE  void setPopupError(QString errorMessage);

signals:
    //this signal is to tell UI to update the values on main page
    Q_INVOKABLE void latestUpdated();
    //this signal is to tell UI to update graphs on history page
    Q_INVOKABLE void historyUpdated();
    //this signal is to tell UI to update graphs in analysispage
    Q_INVOKABLE void analysisUpdated();
    Q_INVOKABLE void errorOccured();



public slots:
    //updates all DataLatestRequester objects in latest_. Joona.
    void updateLatest();
    //this is called when date is chosen in history page. Mikko.
    void updateHistory(QString dateFrom,QString dateTo);

    //this is called when analysis meters and dates is chosen.
    void updateAnalysis(QString dateFrom,QString dateTo,
                        QString quantityX,QString idX,QString quantityY,QString idY);

    //changes the time of the timer. This is used when frequency is changed in UI.
    void setTimer(int min);


private:
    //latest data for all quantities. Joona
    QMap<QString,DataPoint*> latest_;
    //history data for all quantities. Mikko
    QMap<QString,DataList*> historyData_;

    //size 2: 0. element is x-axis and 1. element y-axis. Isto
    QMap<QString,DataList*> analysisData_;
    QVector<QPointF> analysisDatapoints_;
    //this will call the slot updateLatest()
    QTimer* updateTimer_;
    // dateTimes are in form 2016-01-01T00:00:00.000Z
    //Can be used direct to getting historical timeserries
    QString jsonEndDatetime_;
    QString jsonStartDatetime_;
    QString idX_;
    QString idY_;
    QString quantityX_;
    QString quantityY_;
    QVector<double> uiDataX_;
    QVector<double> uiDataY_;
    QString resolution_;
    QString errormessage_;
    double meanX_;
    double meanY_;
    double correlation_;

};

#endif // DATAHANDLER_H
