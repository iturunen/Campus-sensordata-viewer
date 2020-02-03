#ifndef ANALYSISUI_H
#define ANALYSISUI_H

#include <QObject>
#include <QList>
#include <QString>
#include <QtCharts>
#include <settingsreader.h>

class AnalysisUi : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool  xIsPicked READ xIsPicked  WRITE pickX NOTIFY xPicked)
    Q_PROPERTY(bool  yIsPicked READ yIsPicked  WRITE pickY NOTIFY yPicked)
    Q_PROPERTY(bool  datesArePicked READ datesArePicked   WRITE pickDates NOTIFY datesPicked)
public:
    explicit AnalysisUi(QObject *parent = nullptr);
    Q_INVOKABLE QString getFactorX();
    Q_INVOKABLE QString getFactorY();
    QVector<double> extrctPointVector(QVector<QPointF> points, int index);

    //These methods tel qml analysispage when its possible to update data based on user inputs
    bool  xIsPicked();
    bool yIsPicked();
    bool datesArePicked();
    Q_INVOKABLE  void pickX(bool value);
    Q_INVOKABLE   void pickY(bool value);
    Q_INVOKABLE  void pickDates(bool value);


signals:
    Q_INVOKABLE void xPicked();
    Q_INVOKABLE void yPicked();
    Q_INVOKABLE void datesPicked();

public slots:
    QVector<double> updateSeries(QVector<QPointF> points, QAbstractSeries *series);

private:
    bool xSet_;
    bool  ySet_;
    bool  datesSet_;
    QVector<QPointF> analysisDatapoints_;
    QString factorX_;
    QString  factorY_;


};

#endif // ANALYSISUI_H
