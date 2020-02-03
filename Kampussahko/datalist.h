#ifndef DATALIST_H
#define DATALIST_H

#include <QObject>
#include <QList>
#include <QQmlListProperty>
#include "datapoint.h"
class DataList:public QObject
{
    Q_OBJECT

public:
    explicit DataList(QObject* parent = nullptr);
    void append(DataPoint* point);
    void empty();
    //must be QVariantList to get access through qml
    Q_INVOKABLE QVariantList data() const;
    Q_INVOKABLE double min();
    Q_INVOKABLE double max();
private:
    //QVariantList m_list;
    QList<DataPoint*> m_list;
};

#endif // DATALIST_H
