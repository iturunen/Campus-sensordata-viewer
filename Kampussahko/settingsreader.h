#ifndef SETTINGSREADER_H
#define SETTINGSREADER_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QTextStream>
#include <cstdlib>
#include <iostream>

//At the start of the program, this reader reads settingsfile and, with it, recovers
//last session
//And during use of program, updates the current settings and saves them to json file
class SettingsReader : public QObject
{
    Q_OBJECT
public:
    explicit SettingsReader(QObject *parent = nullptr);
    void readSettingsFile();

    Q_INVOKABLE void setCurrentSettings(QString page,QString key,QList<QString> values);
    Q_INVOKABLE void setCurrentSettings(QString page,QString key,QString value,int index);
    Q_INVOKABLE const QString getSetting(QString page, QString setting,int index=0);
    void save();
    // This method reads data from file to QList
    void readDatalistFile();
    // This method saves QList to file
    void saveDatalist();
    Q_INVOKABLE  void setCurrentDatalist( QList<QString> list, QString key);
    Q_INVOKABLE const   QList<QString> getDatalist(QString key);
private:
    QMap<QString,QList<QString>> mainPageSettings_;
    QMap<QString,QList<QString>> historyPageSettings_;
    QMap<QString,QList<QString>> analysisPageSettings_;
    QMap<QString,QList<QString>> datalists_;
    const int indexX_=0;
    const int indexY_=1;
    bool reading_;
};

#endif // SETTINGSREADER_H
