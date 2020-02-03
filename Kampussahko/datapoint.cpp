#include "datapoint.h"
#include <QDebug>
DataPoint::DataPoint(QObject* parent): QObject(parent)
{

}


double DataPoint::value() const
{
    return m_value;

}

QString DataPoint::unit() const
{
    return m_unit;
}

QDateTime DataPoint::date() const
{
    return m_date;
}

void DataPoint::setValue(double value)
{
    m_value = value;
}

void DataPoint::setUnit(QString unit)
{
    m_unit = unit;
}

void DataPoint::setDate(QString date)
{

    //modify string to QDateTime object
    int year = date.left(4).toInt();
    int month = date.mid(5,2).toInt();
    int day = date.mid(8,2).toInt();

    int hour = date.mid(11,2).toInt();
    int minute = date.mid(14,2).toInt();
    QDate d(year,month,day);
    QTime t(hour,minute);
    QDateTime dt(d,t);

    m_date = dt;
}
