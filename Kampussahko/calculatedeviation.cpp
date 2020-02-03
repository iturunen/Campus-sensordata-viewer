#include "calculatedeviation.h"

CalculateDeviation::CalculateDeviation(QObject *parent) : QObject(parent)
{
    
}

std::shared_ptr<QList<double> > CalculateDeviation::getData(){
    return dataPointer_;
}

void CalculateDeviation::setMax(){
    max_ = dataPointer_->size();
}

void CalculateDeviation::saveData( std::shared_ptr<QList<double>> dataPointer){

    dataPointer_ =dataPointer;
}

double CalculateDeviation::calculateMean(){
    setMax();
    double sum = 0;
    double mean = 0;
    for(int i = 0; i < max_; i++){
        sum += dataPointer_ ->at(i);
    }
    mean = (sum / max_);
    mean_ = mean;
    return mean;
}

double CalculateDeviation::calculateVariance(){
    mean_ = calculateMean();
    double  divergence = 0;
    double variance = 0;
    for(int i = 0; i < max_ ; i++){
        divergence += ( dataPointer_ ->at(i) - mean_) * ( dataPointer_ ->at(i) - mean_) ;
    }
    variance = divergence /max_;
    return variance;
}

double CalculateDeviation::calculateStandardDeviation() {
   double  standardDeviation  =  sqrt(calculateVariance());
    standardDeviation_ = standardDeviation ;
    return standardDeviation ;
}

