#include "datahandler.h"
#include <QDebug>

DataHandler::DataHandler(QObject *parent) : QObject(parent),updateTimer_(new QTimer(this))
{   

    connect(updateTimer_,SIGNAL(timeout()),this,SLOT(updateLatest()));
    setTimer(1000);
    updateTimer_->start();

    updateLatest();
}

void DataHandler::updateLatest()
{
    for(auto key: meters.keys()){
        for(auto meter: meters[key]){
            DataRequester datareq(key,meter);
            latest_[meter] = datareq.makeLatestRequest();
        }
    }
    emit latestUpdated();
}

void DataHandler::updateHistory(QString dateFrom, QString dateTo)
{
    for(auto key: meters.keys()){
        for(auto meter: meters[key]){
            DataRequester datareq(key,meter);
            QString resolution = setResolution(dateFrom, dateTo);
            QList<DataPoint*> points = datareq.makeHistoryRequest(dateFrom,
                                                                  dateTo,resolution);

            DataList* list = new DataList(this);


            for(auto point:points){
                point->setParent(list);
                list->append(point);
            }
            if(historyData_[meter] != nullptr){delete historyData_[meter]; }
            historyData_[meter] = list;
        }
    }
    emit historyUpdated();
}
QString DataHandler::popupError(){
    return errormessage_;
}

void DataHandler::setPopupError(QString errorMessage){
    errormessage_ = errorMessage;
}

void DataHandler::setTimer(int min)
{
    //update QTimer time
    updateTimer_->setInterval(min*60*3600);
}


DataPoint* DataHandler::latestData(QString id)
{
    if(latest_.find(id) != latest_.end()){
        return latest_[id];
    }
}

DataList* DataHandler::historyData(QString id) const
{

    if(historyData_.find(id)!= historyData_.end()){
        return (historyData_[id]);
    }
    return nullptr;
}

void DataHandler::updateAnalysis(QString dateFrom,QString dateTo,
                                 QString quantityX,QString idX,QString quantityY,QString idY)
{   //if something is missing in QML analysisPages input signal this pervents to send datarequest
    if(quantityX =="" || quantityY =="" || idX=="" || idY ==""){
        return;
    }
    if(dateFrom >= dateTo){
        errormessage_ = "Virhe: aloitusajan on oltava ennen lopetusaikaa.";
        emit errorOccured();
        return;
    }
    else{
        QString resolution = setResolution(dateFrom,dateTo);
        //make datarequest for x-axis
        DataRequester datareq(quantityX,idX);
        if(datareq.makeHistoryRequest(dateFrom,dateTo,resolution).isEmpty()){
            errormessage_ = "Virhe: dataa ei saatavilla tältä ajalta.";
            emit errorOccured();
            return;
        }

        QList<DataPoint*> points = datareq.makeHistoryRequest(dateFrom,dateTo,resolution);
        DataList* analysisDataX = new DataList(this);
        analysisData_["X"]=analysisDataX;
        for(auto point: points){
            point->setParent(analysisDataX);
            analysisData_["X"]->append(point);
        }
        //make datarequest for y-axis
        datareq = DataRequester(quantityY,idY);
        points = datareq.makeHistoryRequest(dateFrom,dateTo,resolution);
        if(points.isEmpty()){
            errormessage_ = "Virhe: dataa ei saatavilla tältä ajalta.";
            emit errorOccured();
            return;
        }
        DataList* analysisDataY = new DataList(this);
        analysisData_["Y"]=analysisDataY;

        for(auto point:points){
            point->setParent(analysisDataY);
            analysisData_["Y"]->append(point);
        }
        CalculateCorrelation correlationAndMean;
        correlationAndMean.saveData(extrctDataList("X"),extrctDataList("Y"));
        double correlation = correlationAndMean.calculateCorrelation();
        meanX_ =correlationAndMean.getMeanX();
        meanY_ =correlationAndMean.getMeanY();
        correlation_ = correlation;
        // clear old data from analysisUI data and replacing it with new qPointFs
        analysisDatapoints_ ={};
        dataToAnalysisUI(uiDataX_,uiDataY_);
    }
    emit analysisUpdated();
}

void DataHandler::dataToAnalysisUI(QVector<double> uiDataX, QVector<double> uiDataY){

    int max = uiDataX.count();

    for(int i =0; i<max; i++){
        double x = uiDataX.at(i);
        double y = uiDataY.at(i);

        QPointF point(x,y);
        analysisDatapoints_.append(point);
    }

}
// extract qvarriantlist to qlist that is used in calculate correlation class
std::shared_ptr<QList<double>> DataHandler::extrctDataList(QString axe)
{
    DataPoint * extrctedPoint = new DataPoint;
    QVariantList listpoints ={};
    QList <double>* analysisData = new QList<double>;
    // CalculateCorrelation uses shared pointers so normal pointer is converted to shared
    if(axe == 'X'){
        uiDataX_ = {};
        listpoints = analysisData_["X"]->data();

        for(QVariantList::iterator  i = listpoints.begin();
            i != listpoints.end();i++){
            extrctedPoint = qvariant_cast<DataPoint*>(*i);
            analysisData->append(extrctedPoint->value());
            uiDataX_.append(extrctedPoint->value());
        }
    }
    else{
        uiDataY_ = {};
        listpoints = analysisData_["Y"]->data();
        for(QVariantList::iterator  i = listpoints.begin();
            i != listpoints.end();i++){
            extrctedPoint = qvariant_cast<DataPoint*>(*i);
            analysisData->append(extrctedPoint->value());
            uiDataY_.append(extrctedPoint->value());
        }
    }
    std::shared_ptr<QList<double>> analysisDataShared (analysisData);
    return analysisDataShared;
}

DataList* DataHandler::analysisData(QString axis)
{
    return analysisData_[axis];
}
//id of meter.
void DataHandler::setQmlId(QString axe,QString id)
{
    if (axe =="X"){
        idX_ = id;
    }
    else{
        idY_ = id;
    }
}
void DataHandler::setQmlQuantity(QString axe,QString quantity)
{
    if (axe =="X"){
        quantityX_ = quantity;
    }
    else{
        quantityY_ = quantity;
    }
}

QString DataHandler::setResolution(QString startDatetimeStr, QString endDatetimeStr){
    QString resolution;
    QDateTime startDatetime = QDateTime::fromString(startDatetimeStr,"yyyy-MM-ddTHH:mm:00.000Z");
    QDateTime endDatetime = QDateTime::fromString(endDatetimeStr,"yyyy-MM-ddTHH:mm:00.000Z");

    int minuteLimit = 1*24*60*60; //if interval is one day or less, set resolution to min
    int hourLimit = 30*60*60*24; // if interval is month or less, set resolution to hour
    int dayLimit = 365*60*60*24*7; //if interval is year or less, set resolution to day
    //else, set resolution to month

    long long int timeInterval;
    timeInterval =  abs(startDatetime.secsTo(endDatetime));

    if(timeInterval <minuteLimit){
        resolution = "minute";
    }
    else if(timeInterval <=hourLimit){
        resolution = "hour";
    }
    else if(timeInterval <=dayLimit){
        resolution = "day";
    }

    else{
        resolution = "month";
    }
    resolution_ = resolution;
    return resolution;
}
void DataHandler::convertQmlDatetimes(QString startDate, QString endDate, QString startTime, QString endTime)
{

    //Here we convert QML:s outputdates to jsonreader form
    QString startDatetimeStr = startDate+" "+startTime;
    QDateTime startDatetime = QDateTime::fromString(startDatetimeStr,"dd.MM.yyyy H:m");
    QString jsonStartDatetime = startDatetime.toString("yyyy-MM-ddTHH:mm:00.000Z");

    QString endDatetimeStr = endDate+" "+endTime;
    QDateTime endDatetime = QDateTime::fromString(endDatetimeStr,"dd.MM.yyyy H:m");
    QString jsonEndDatetime = endDatetime.toString("yyyy-MM-ddTHH:mm:00.000Z");
    jsonStartDatetime_ = jsonStartDatetime;
    jsonEndDatetime_ = jsonEndDatetime;
}

void DataHandler::setDatetimes(QString startDate, QString endDate, QString startTime, QString endTime)
{
    convertQmlDatetimes(startDate, endDate,  startTime, endTime);
}

QString DataHandler::setQmlId(QString axe)
{
    if (axe =="X"){
        return idX_;
    }
    else{
        return idY_;
    }
}

QString DataHandler::setJsonDatetime(QString dateType)
{
    if (dateType == "startDatetime"){
        return jsonStartDatetime_;
    }
    else{
        return jsonEndDatetime_;
    }
}

QString DataHandler::setQmlQuantity(QString axe)
{
    if (axe =="X"){
        return quantityX_;
    }
    else{
        return quantityY_;
    }
}

QString DataHandler::getCorrelation()
{            QString correlation = QString::number(correlation_, 'g', 3);
             if(correlation =="nan") {
                 return correlation = "Ei määritetty" ;
             }
             else{
                 return  correlation;
             }
}
QString DataHandler::getMeanX()
{   QString roundMeanX = QString::number(meanX_, 'g', 3);
    return roundMeanX;
}
QString DataHandler::getMeanY()
{
    QString roundMeanY = QString::number(meanY_, 'g', 3);
    return roundMeanY;
}

QVector<QPointF>DataHandler::getAnalysisData()
{
    return analysisDatapoints_ ;
}
