#ifndef ANALYSISTOOL_H
#define ANALYSISTOOL_H
#include <QList>
#include <QObject>
#include <stdio.h>
#include <math.h>

#include <vector>
#include <functional>
#include <memory>
#include <iostream>
#include <map>

//CalculateDeviation calculates all varriables that need only one dataset. Mean and deviation are saved to class
class CalculateDeviation : public QObject
{
    Q_OBJECT
    /* struct analysisData {
        double meanX;
        double meanY;
        double correlationXY;
        std::shared_ptr<QList <int>> xData;
        std::shared_ptr<QList <int>> yData;
    };*/

public:
    explicit CalculateDeviation(QObject *parent = nullptr);
    std::shared_ptr<QList <double>> getData();
    void setMax();
    double calculateMean();
    double calculateStandardDeviation();
    double calculateVariance();
    void saveData(std::shared_ptr<QList<double> > dataPointer);
signals:

public slots:

private:
    double mean_;
    double standardDeviation_;
    int max_;
    std::shared_ptr<QList <double>> dataPointer_;
    QList<double> data_;
};

#endif // ANALYSISTOOL_H
