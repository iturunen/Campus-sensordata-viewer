#include "jsondatareader.h"
#include <QDebug>

JsonDataReader::JsonDataReader(QByteArray& data)
{
    document_ = QJsonDocument::fromJson(data);
}


QList<DataPoint*> JsonDataReader::parseEntities()
{
    QList<DataPoint*> result;
    if(document_.isArray()){
        QJsonArray arr = document_.array();
        QJsonArray::iterator i;
        for(i=arr.begin();i!=arr.end();++i){
            QJsonValue jval = *i;

            result.push_back(parseEntity(jval.toObject()));
        }
    }
    else{
        QJsonObject obj =  document_.object();
        result.push_back(parseEntity(obj));
    }
    return result;
}

DataPoint* JsonDataReader::parseEntity(QJsonObject obj)
{
    //resulting datapoint
    QList<QString> keyList = {"dateMeasured","measuredValue","unit"};
    QMap<QString,QString> pointData;
    for(auto key:keyList){
        QJsonValue jva = obj.find(key).value();
        pointData[key] = jva.toObject().find("value")->toString();
    }
    DataPoint* result = new DataPoint;

    result->setValue(pointData["measuredValue"].toDouble());
    result->setUnit(pointData["unit"]);
    result->setDate(pointData["dateMeasured"]);
    return result;

}


QList<QString> JsonDataReader::parseContextResponse(QString key)
{
    //get the contextElement
    if(document_.isObject()){
        QJsonArray contextResponse =  document_.object().find("contextResponses")->toArray();
        QJsonObject status = contextResponse[0].toObject().find("statusCode")->toObject();
        if(status.find("code")->toString() == "200"){

            QJsonObject contextElement = contextResponse[0].toObject().find("contextElement")->toObject();
            QJsonArray attributes = contextElement.find("attributes")->toArray();
            QJsonArray values = attributes[0].toObject().find("values")->toArray();
           if( values.isEmpty()){
           qDebug()<<"Kyselyssä ei dataa ";
            return QList<QString>();
           }
           else{
            QList<QString> list;
            for(auto object:values){
                QList<QString> list1 = parseContextElements(object.toObject(),key);
                for(auto elem:list1){
                    list.append(elem);
                }

            }
            return list;
           }
        }else{
            qDebug()<<"Status code: " <<status.find("code")->toString();
            return QList<QString>();
        }
    }
}

const QList<QString> JsonDataReader::parseContextElements(QJsonObject obj,
                                                    QString key)
{
    //at this point the array is array of points
    QList<QString> result;

    //get the id of measurements
    QJsonObject head = obj.find("_id")->toObject();

    QJsonArray arr = obj.find("points")->toArray();
    for(auto point:arr){

        if(key == "occur"){//check if we make string request -> unit

            QString unit = point.toObject().find(key)->toObject().keys().value(0);
            result<<unit;

        }else if(key == "sum"){//now we want the value
            int samples = point.toObject().find("samples")->toInt();
            double value = point.toObject().find(key)->toDouble();

            QString meanValue = QString::number(value/samples);
            result << meanValue;
        }else if(key == "date"){//now we want the date
            //origin date
            QString origin = head.find("origin")->toString();
            QString resolution = head.find("resolution")->toString();
            QString offset = QString::number(point.toObject().find("offset")->toInt());

            int index;
            if(resolution == "month"){
                index = 5;
            }else if(resolution == "day"){
                index = 8;
            }else if(resolution == "hour"){
                index = 11;
            }else if(resolution == "minute"){
               index = 14;
            }
            //set the measurement date with origin and offset
            if(offset.size() == 1){offset.insert(0,'0');}
            origin.replace(index,offset.length(),offset);
            result << origin;
        }

    }
    return result;
}




