#ifndef CALCULATECORRELATION_H
#define CALCULATECORRELATION_H

#include <QList>
#include <QObject>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <functional>
#include <memory>
#include <iostream>
#include <map>
#include <QDebug>
#include <iostream>

#include"calculatedeviation.h"

//CalculateCorrelation calculates all varriables that need two datasets. Datasets are taken from class CalculateDeviation
class CalculateCorrelation : public QObject
{
    Q_OBJECT
public:
    explicit CalculateCorrelation(QObject *parent = nullptr);
    void saveData(std::shared_ptr<QList <double>> dataPointerX,std::shared_ptr<QList <double>> dataPointerY);
    double calculateCovariance();
    double calculateCorrelation();
    void setMax();
    double getMeanY();
    double getMeanX();

private:

    QList<double> dataX_;
    QList<double> dataY_;
    int max_;
    std::shared_ptr<CalculateDeviation> deviationX_;
    std::shared_ptr<CalculateDeviation>  deviationY_;
    std::shared_ptr<QList<double> > dataPointerX_;
    std::shared_ptr<QList <double>> dataPointerY_;
    QString correlation_;
};

#endif // CALCULATECORRELATION_H
