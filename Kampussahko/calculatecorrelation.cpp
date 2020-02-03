#include "calculatecorrelation.h"

//CalculateCorrelation *CalculateCorrelation::instance_ = NULL;

CalculateCorrelation::CalculateCorrelation(QObject *parent) : QObject(parent){

}

//CalculateCorrelation*CalculateCorrelation::getInstance(){
//    return instance_;
//}

void CalculateCorrelation::saveData(std::shared_ptr<QList<double> > dataPointerX, std::shared_ptr<QList<double> > dataPointerY)
{
    //assert that datapointers saved are not empty
    if(dataPointerX->isEmpty()){
        QList<double> xList;
        double x = NAN;
        xList.append(x);
        std::shared_ptr<QList<double>> dataPointerX(new QList<double>);
        dataPointerX->append( xList);
    }
    else if(dataPointerY->isEmpty()){
        QList<double> yList;
        double y = NAN;
        yList.append(y);
        std::shared_ptr<QList<double>> dataPointerY(new QList<double>);
        dataPointerY->append( yList);
    }
    std::shared_ptr<CalculateDeviation> deviationPointerX(new CalculateDeviation);
    std::shared_ptr<CalculateDeviation> deviationPointerY(new CalculateDeviation);

    deviationX_= deviationPointerX;
    deviationY_ = deviationPointerY;
    deviationX_->saveData(dataPointerX);
    deviationY_->saveData(dataPointerY);
    dataPointerX_=dataPointerX;
    dataPointerY_=dataPointerY;
}
void CalculateCorrelation::setMax(){
    max_ = dataPointerX_->size();
}

double CalculateCorrelation::calculateCovariance()
{
    double xMean = deviationX_->calculateMean();
    double yMean = deviationY_->calculateMean();
    double total = 0;
    for(int i = 0; i < max_; i++){
        total += (dataPointerX_->at(i) - xMean) * (dataPointerY_->at(i) - yMean);

    }
    return total / max_;
}

double CalculateCorrelation::calculateCorrelation()
{
    setMax();
    double covariance = calculateCovariance();
    double deviationX = deviationX_->calculateStandardDeviation();
    double deviationY = deviationY_->calculateStandardDeviation();
    double correlation = covariance / (deviationX*deviationY);
    correlation_ = correlation;
    return correlation;
}

double CalculateCorrelation::getMeanX(){
    double meanX = deviationX_->calculateMean();
    return meanX;
}
double CalculateCorrelation::getMeanY(){
    double meanY = deviationY_->calculateMean();
    return meanY;
}
