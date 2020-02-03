#include "datarequester.h"
#include "jsondatareader.h"
#include <QDebug>

#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QIODevice>
#include <QNetworkAccessManager>
#include <iomanip>
#include <iostream>

#include <stdio.h>
#include <math.h>

DataRequester::DataRequester(QString quantity, QString id):quantity_(quantity),id_(id)
{

}

//make the https request and update the data to unit_ and value_
DataPoint* DataRequester::makeLatestRequest()
{
    QString url = "https://test.ain.rd.tut.fi:1026/fiware/v2/entities";
    QByteArray header = "FIWARE-Service";
    //this is mostly from course slides
    QNetworkAccessManager mgr;
    QEventLoop eventLoop;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)),
    &eventLoop, SLOT(quit()));

    //create new network request
    QNetworkRequest req;
    req.setUrl(QUrl(url+"/"+id_));
    req.setRawHeader(header, quantity_.toUtf8());

    //get the reply
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks until "finished()

    //check if there was an error
    if (reply->error() == QNetworkReply::NoError) {
        QIODevice* dev = dynamic_cast<QIODevice*>(reply);
        QByteArray data = dev->readAll();
        JsonDataReader reader(data);

        //this parses the unit of the measured data
//        QList<QString> unit = reader.parseEntities("unit");
        //this parses the value of the m
        DataPoint* point = reader.parseEntities().at(0);
        //put the data in datapoint struct

        return point;
    }else{
        //If request is not valid.
        qDebug()<<"Request error.";
        DataPoint* dataPoint = new DataPoint;
        dataPoint->setUnit("Error");
        dataPoint->setValue(1.0);
        dataPoint->setDate("");
        return dataPoint;
    }
}

//returns the max values of one step
const QList<DataPoint*> DataRequester::makeHistoryRequest(QString dateFrom, QString dateTo,QString resolution)
{
    //construct the url
    //example: http://<sth-host>:<sth-port>/STH/v1/contextEntities/type/<entityType>/id/<entityId>/attributes/<attrName>?hLimit=3&hOffset=0&dateFrom=2016-01-01T00:00:00.000Z&dateTo=2016-01-31T23:59:59.999Z
    QString url;

    QString sth_host = "https://test.ain.rd.tut.fi";
    QString sth_port = ":8666";
    QString path = "/fiware/STH/v1/contextEntities/type/Measurement/id/"+id_+"/attributes/";

    QByteArray serviceHeader = "FIWARE-Service";
    QByteArray servicePathHeader = "Fiware-Servicepath";
    //make measured value request
    url = sth_host+sth_port+path+"/measuredValue?"+"aggrMethod=sum&aggrPeriod="
            +resolution+"&dateFrom="+dateFrom+"&dateTo="+dateTo;

    QNetworkAccessManager mgr;
    QEventLoop eventLoop;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)),
    &eventLoop, SLOT(quit()));

    //make new request
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setRawHeader(serviceHeader,quantity_.toUtf8());
    req.setRawHeader(servicePathHeader,QByteArray("/"));

    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks until "finished()
    QList<QString> values;
    QList<QString> dates;
    if(reply->error() == QNetworkReply::NoError){
        QIODevice* dev = dynamic_cast<QIODevice*>(reply);
        QByteArray data = dev->readAll();
        JsonDataReader reader(data);

        values = reader.parseContextResponse("sum");
        dates = reader.parseContextResponse("date");
        if(values.empty()){
            return QList<DataPoint*>();
        }

    }else{
        qDebug()<<"History request error.";
        return QList<DataPoint*>();
    }    //make unit request
    url = sth_host+sth_port+path+"/unit?"+"aggrMethod=occur&aggrPeriod="
            +resolution+"&dateFrom="+dateFrom+"&dateTo="+dateTo;
    req.setUrl(QUrl(url));
    req.setRawHeader(serviceHeader,quantity_.toUtf8());
    req.setRawHeader(servicePathHeader,QByteArray("/"));

    reply = mgr.get(req);
    eventLoop.exec();// blocks until "finished()

    QList<QString> units;
    if(reply->error() == QNetworkReply::NoError){
        QIODevice* dev = dynamic_cast<QIODevice*>(reply);
        QByteArray data = dev->readAll();
        JsonDataReader reader(data);

        units = reader.parseContextResponse("occur");
    }
    QList<DataPoint*> result;
    for(int i=0;i<values.size() and i<units.size() and i<units.size();++i){

       double diff = values.at(i).toDouble();

        ///uncomment this bit, to take cumulative values into accounts
       if(i != 0 and quantity_ != "outside_temperature"){
         double last = values.at(i-1).toDouble();

        diff = diff -last;
       }


        DataPoint* point = new DataPoint;
        point->setValue(diff);
        point->setUnit(units.at(i));
        point->setDate(dates.at(i));
        result.push_back(point);
    }
    if(result.size() > 1){
        delete *result.begin();
        result.erase(result.begin());
    }

    return result;
}




