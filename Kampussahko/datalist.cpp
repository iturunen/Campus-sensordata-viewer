#include "datalist.h"
#include <QDebug>
DataList::DataList(QObject* parent):QObject(parent)
{
}



void DataList::append(DataPoint *point)
{
    m_list.append(point);
}

void DataList::empty()
{
    if(!m_list.isEmpty()){
        for(auto elem:m_list){
            delete elem;
        }
        m_list.clear();
    }
}

QVariantList DataList::data() const
{
    QVariantList list;
    for(auto point: m_list){
        list.append(QVariant::fromValue(point));
    }
    return list;
}

double DataList::min()
{
    double min = INT_MAX;
    for(auto point: m_list){
        if(point->value() < min){
            min = point->value();
        }
    }
    return min;
}

double DataList::max()
{
    double max = INT_MIN;
    for(auto point: m_list){
        if(point->value() > max){
            max = point->value();
        }
    }
    return max;
}
