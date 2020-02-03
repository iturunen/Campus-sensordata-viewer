#include "analysisui.h"

AnalysisUi::AnalysisUi(QObject *parent) : QObject(parent),xSet_(false),ySet_(false),datesSet_(false)
{

}

QVector<double> AnalysisUi::updateSeries(QVector<QPointF> points, QAbstractSeries *series)
{
    QVector<double> borders;
    QVector<double> xData;
    QVector<double> yData;
    QVector<double> extractedPoint;
    int max =  points.count();
    for(int index =0;index <max; index++){
        //returns points x and y value in vector
        extractedPoint =extrctPointVector(points,index);
        xData.append(extractedPoint.at(0));
        yData.append(extractedPoint.at(1));
    }
    //Factors are added to qml analysis data view if values are large
    // to make view better
    if (series) {
        double factorX =1;
        double factorY=1;
        double minX = *std::min_element(xData.begin(), xData.end());
        double maxX = *std::max_element(xData.begin(), xData.end());
        double minY = *std::min_element(yData.begin(), yData.end());
        double maxY = *std::max_element(yData.begin(), yData.end());

        //Next scalingfactors are calculated for each datapoint paced on points dataset min value
        if(minX < pow(10,6)){
            factorX = 1;
        }
        else if( minX >= pow(10,6) && minX < pow(10,9)){
            factorX = pow(10,6);
            xData.clear();
            for(int index =0;index <max; index++){
                //returns points x and y value in vector
                extractedPoint =extrctPointVector(points,index);
                xData.append(extractedPoint.at(0)/factorX);
            }
        }
        else if( minX >= pow(10,9) && minX < pow(10,12)){
            factorX = pow(10,9);
            xData.clear();
            for(int index =0;index <max; index++){
                extractedPoint =extrctPointVector(points,index);
                xData.append(extractedPoint.at(0)/factorX);
            }
        }
        else if (minX >= pow(10,12) && minX < pow(10,15)){
            factorX = pow(10,12);
            xData.clear();
            for(int index =0;index <max; index++){
                extractedPoint =extrctPointVector(points,index);
                xData.append(extractedPoint.at(1)/factorX);
            }
        }
        else{
            factorX = pow(10,15);
            xData.clear();
            for(int index =0;index <max; index++){
                extractedPoint =extrctPointVector(points,index);
                xData.append(extractedPoint.at(0)/factorX);
            }
        }

        if(minY < pow(10,6)){
            factorY = 1;
        }
        else if( minY >= pow(10,6) && minY< pow(10,9)){
            factorY = pow(10,6);
            yData.clear();
            for(int index =0;index <max; index++){
                extractedPoint =extrctPointVector(points,index);
                yData.append(extractedPoint.at(1)/factorY);
            }
        }
        else if( minY >= pow(10,9) && minY < pow(10,12)){
            factorX = pow(10,9);
            yData.clear();
            for(int index =0;index <max; index++){
                extractedPoint =extrctPointVector(points,index);
                yData.append(extractedPoint.at(1)/factorY);
            }
        }
        else if (minY >= pow(10,12) && minY < pow(10,15)){
            factorY = pow(10,12);
            yData.clear();
            for(int index =0;index <max; index++){
                extractedPoint =extrctPointVector(points,index);
                yData.append(extractedPoint.at(1)/factorY);
            }
        }
        else{factorY = pow(10,15);
            yData.clear();
            for(int index =0;index <max; index++){
                extractedPoint =extrctPointVector(points,index);
                yData.append(extractedPoint.at(1)/factorY);
            }
        }
        //at the end we append modified points for serries.
        points.clear();
        double x ;
        double y;
        QPointF point;
        SettingsReader settings;
        QList<QString> yStrings;
        QList<QString> xStrings;
        QString yS;
        QString xS;

        for(int index =0;index <max; index++){
            xS = QString::number(xData.at(index));
            yS = QString::number(yData.at(index));
            xStrings.append(xS);
            yStrings.append(yS);

            x = xData.at(index);
            y = yData.at(index);
            point.setX(x);
            point.setY(y);
            points.append(point);
        }
        settings.setCurrentDatalist(xStrings,"X");
        settings.setCurrentDatalist(yStrings,"Y");
        //settings.setCurrentSettings("analysis","currentPointsY",yStrings);


        minX = *std::min_element(xData.begin(), xData.end());
        maxX = *std::max_element(xData.begin(), xData.end());
        minY = *std::min_element(yData.begin(), yData.end());
        maxY = *std::max_element(yData.begin(), yData.end());
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        xySeries->replace(points);
        //if datapoints have really big value we divide them with factor and return factor to qml: analysisview.
        borders<<minX<<maxX<<minY<<maxY;
        if(factorX == 1){
            factorX_ = "";
        }
        else{
            factorX_ = " *"+ QString::number(factorX,'g',1);
        }
        if(factorY == 1){
            factorY_ = "";
        }
        else{
            factorY_ = " *"+ QString::number(factorY,'g',1);
        }
    }
    return borders;
}

QVector<double> AnalysisUi::extrctPointVector(QVector<QPointF> points, int index){
    double x;
    double y;
    QVector<double> extractedXy ={} ;
    x = points.at(index).x();
    y = points.at(index).y();
    extractedXy.append(x);
    extractedXy.append(y);

    return extractedXy;
}

QString AnalysisUi::getFactorX()
{
    return factorX_;
}

QString AnalysisUi::getFactorY()
{
    return factorY_;
}

void AnalysisUi::pickX(bool value)
{
    xSet_ = value;
}

void AnalysisUi::pickY(bool value)
{
    ySet_ = value;
}
void AnalysisUi::pickDates(bool value)
{
    datesSet_ = value;
}

bool AnalysisUi::xIsPicked()
{
    return xSet_;
}

bool AnalysisUi::yIsPicked()
{
    return ySet_;
}

bool  AnalysisUi::datesArePicked()
{
    return datesSet_;
}
