#include "analysisdataui.h"
#include <QtCore/QtMath>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)
Q_DECLARE_METATYPE(QLineSeries*)

AnalysisDataUI::AnalysisDataUI(QObject *parent) : QObject(parent),mXy_({}),series_ (new QLineSeries)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();
    qRegisterMetaType<QLineSeries*>();


}


/*QAbstractSeries* AnalysisDataUI::xy()
{

    return series_;
} */
/*
void AnalysisDataUI::update(QAbstractSeries *series)
{ /*DataHandler analysisData;
   std::shared_ptr<QList<double>> datapointerX (new QList<double>);
   qDebug()<<"Extract: ";
   datapointerX = analysisData.extrctDataList("X");
  qDebug()<<"datapointerX->size(): ";
   qDebug()<<datapointerX->size();

    qDebug()<< "UI data";
   qDebug()<< mXy_;

    QList<QPointF> points;
    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        if(mXy_.isEmpty()){
            QList<QPointF> mPoints;
            QPointF point1(1,1);
            QPointF point2(2,2);
            mPoints.append(point1);
            mPoints.append(point2);//returnPoint();
            for(auto point: mPoints){
                points.append(point);
            }
        }
        else{
            QList<QPointF> mPoints;
            mPoints = mXy_;
            for(auto point: mPoints){
                mPoints.append(point);
            }
        }
        qDebug()<<"mPoints Created!";
        qDebug()<<points;
        // Use replace instead of clear + append, it's optimized for performance
        xySeries->replace(points);

    } emit xyChanged();
}*/


QLineSeries *AnalysisDataUI::xy()
{
    qDebug()<<series_->at(0);
    return series_;
}


void AnalysisDataUI::setXy(QLineSeries *xy)
{
   // if(mXy_ == xy) return;
   // if(mXy_)
       /* if(mXy_->parent() == this) // is owner
            delete mXy_; */
   // mXy_ = xy;
qDebug()<<"mXy_ data 0 pisteessä:";

if(mXy_.isEmpty()){
        double x1 = 1;
        double x2 = 2;
        double y1 = 1;
        double y2 = 2;
        xy->append(x1,y1);
        xy->append(x2,y2);
        xy->append(xc,yc);

}
else{
    xy->replace(mXy_);
}



    // Use replace instead of clear + append, it's optimized for performance

   // emit xyChanged();
}

void AnalysisDataUI::newData(qreal x, qreal y){
         qDebug()<<"new data:";
         QPointF point(x,y);
        mXy_.append(point);
        xc = 6;
        yc =6;

        series_->append(x,y);
emit xyChanged();


}

void AnalysisDataUI::mouseClick()
{
    qDebug() << "CustomItem::mouseClick()";

    emit click();
}

double AnalysisDataUI::returnPointX()
{   qDebug()<<"return x: ";
    qDebug()<<x_;
    return x_;
}

double AnalysisDataUI::returnPointY()
{
    return y_;
}


/*void AnalysisDataUI::getData(QList<double> Xdata, QList<double> Ydata){
    //  QList<QPointF> analysisUI ;
    // mXy_= analysisUI;

    assert(Xdata.size() ==Ydata.size());
    int indexMax = Xdata.size();
    int index =0;
    double x = 0;
    double y = 0;
    QList<QPointF*>pointerList;
    for (index =0; index < indexMax; index++){
        x = Xdata.at(index);
        y= Ydata.at(index);
        QPointF dataPoint(x,y);
        mXy_.append(dataPoint);
        x_ = x;

       // xyData_->append(dataPoint.x(),dataPoint.y());
       // series_->append(dataPoint);
        pointerList.append(&dataPoint);
    }
    // emit xyChanged();
}*/
