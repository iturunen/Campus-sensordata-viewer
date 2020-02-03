#ifndef DATAREADER_H
#define DATAREADER_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include <QList>
#include <QString>

#include "datapoint.h"



class JsonDataReader{

public:
    JsonDataReader(QByteArray& data);

    //returns the value of json object with keyword key: keys to be used: dateMeasured, unit, measuredValue,
    QList<DataPoint*> parseEntities();
    //returns the list of "points" in response data
    QList<QString> parseContextResponse(QString key);
private:
    //parse entity is for latest request
    DataPoint* parseEntity(QJsonObject obj);

    //these functions are for history
    const QList<QString> parseContextElements(QJsonObject obj, QString key);

    QJsonDocument document_;
};

#endif // DATAREADER_H
