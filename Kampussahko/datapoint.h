#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <QString>
#include <QObject>
#include <QDateTime>

class DataPoint: public QObject
{
    Q_OBJECT
    Q_PROPERTY(double value READ value)
    Q_PROPERTY(QString unit READ unit)
    Q_PROPERTY(QDateTime date READ date)
public:
    explicit DataPoint(QObject* parent=nullptr);
    double value() const;
    QString unit() const;
    QDateTime date() const;
    void setValue(double value);
    void setUnit(QString unit);
    void setDate(QString date);
private:
    double m_value; //measuredValue
    QString m_unit; //unit
    QDateTime m_date; //yyyy-mm-ddThh:mmZ
};

#endif // DATAPOINT_H
