#ifndef DataRequester_H
#define DataRequester_H

#include <QString>
#include <QUrl>
#include <QMap>
#include "datapoint.h"

/*set the quantity you want to ask. The value of latest measurement of the guantity is accessible with getValue method.
 * latest measurement unit is accessible with getUnit. QList contains latest values of all meters that measures that quantity.
 */


class DataRequester
{

public:
    //constructed by giving the quantity and the meter id
    DataRequester(QString quantity,QString id);
    //makes the latest data request
    DataPoint* makeLatestRequest();
    //makes the history data request, makes max request but when parsing, counts
    //mean value
    const QList<DataPoint*> makeHistoryRequest(QString dateFrom, QString dateTo, QString resolution="day");

private:

    //this is the quantity we want to ask from data. Needed for httpRequest
    QString quantity_;
    //id of the meter
    QString id_;
};




#endif // DataRequester_H
