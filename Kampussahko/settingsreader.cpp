#include "settingsreader.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
SettingsReader::SettingsReader(QObject *parent) : QObject(parent),reading_(false)
{
    readSettingsFile();
    readDatalistFile();
    reading_ = true;
    qDebug()<<"Luettu";
}

void SettingsReader::readSettingsFile()
{
    QFile file;
    //file.setFileName(":/default.json");
    file.setFileName("settings.json");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        file.setFileName(":/default.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        qDebug()<<"Default";
    }

    QByteArray jsonData = file.readAll();

    file.close();
    QJsonParseError* err = new QJsonParseError;
    QJsonDocument document = QJsonDocument::fromJson(jsonData,err);
    qWarning()<<err->errorString();
    QJsonObject obj = document.object();
    for(auto key: obj.keys()){
        QJsonObject pageObject  = obj[key].toObject();
        for(auto key1 : pageObject.keys()){
            QJsonValue val = pageObject[key1];
            QList<QString> values;
            if(val.isArray()){
                for(auto arrElement:val.toArray()){
                    values.append(arrElement.toString());
                }
            }else{
                values.append(val.toString());
            }
            setCurrentSettings(key,key1,values);
        }
    }

}


//sets a list of settings
void SettingsReader::setCurrentSettings(QString page, QString key, QList<QString> values)
{
    if(page == "main"){
        mainPageSettings_.insert(key,values);
    }else if(page=="history"){
        historyPageSettings_.insert(key,values);
    }else if(page=="analysis"){
        analysisPageSettings_.insert(key,values);
        
    }
    if(reading_){
        save();
    }

}

void SettingsReader::saveDatalist(){
    // qDebug()<<"in savedatalist method:";
    QStringList list;
    // write data
    QFile fileOut("settings.txt");
    if (fileOut.open(QFile::WriteOnly | QFile::Text)) {
        
        //Saves xData to row 1 and  yData to row 2
        QTextStream stream(&fileOut);
        for(int j = 0; j<datalists_.size();j++){
            if(j==indexX_){
                list = datalists_["X"];
            }
            else if(j ==indexY_){
                list = datalists_["Y"];
            }
            for (int i = 0; i < list.size(); ++i){
                stream <<','<< list.at(i);

            }
            stream<<'\n';
        }
    }

    fileOut.close();
}

//sets single setting
void SettingsReader::setCurrentSettings(QString page, QString key, QString value, int index)
{
    QList<QString> list;
    if(page == "main"){
        list = mainPageSettings_[key];
    }else if(page == "history"){
        list = historyPageSettings_[key];

    }else if(page == "analysis"){
        list = analysisPageSettings_[key];
    }
    if(index < list.size()){
        list[index] = value;

    }
    setCurrentSettings(page,key,list);
}

const QString SettingsReader::getSetting(QString page, QString setting,int index)
{
    
    if(page == "main"){

        if(mainPageSettings_.find(setting) == mainPageSettings_.end()){
            qDebug()<<mainPageSettings_.size();
            return "";
        }else if(mainPageSettings_[setting].size() > index){

            return mainPageSettings_[setting][index];
        }

    }else if(page=="history"){
        if(historyPageSettings_.find(setting)==historyPageSettings_.end()){
            return  "";
        }else if(historyPageSettings_[setting].size() > index){
            return historyPageSettings_[setting][index];
        }

    }else if(page == "analysis"){
        if(analysisPageSettings_.find(setting) == analysisPageSettings_.end()){
            return "";
        }else if(analysisPageSettings_[setting].size() > index){
            return analysisPageSettings_[setting][index];
        }
        return analysisPageSettings_[setting][index];
    }
    return "";
}

void SettingsReader::save()
{
    QJsonObject json;
    QJsonObject obj;
    QMapIterator<QString,QList<QString>> i(mainPageSettings_);
    while(i.hasNext()){
        i.next();
        QJsonArray arr;
        for(auto setting:i.value()){
            arr.append(setting);
        }
        obj.insert(i.key(),QJsonValue(arr));
    }
    json.insert("main",obj);
    obj = QJsonObject();
    i = QMapIterator<QString,QList<QString>>(historyPageSettings_);
    while(i.hasNext()){
        i.next();
        QJsonArray arr;
        for(auto setting:i.value()){
            arr.append(setting);
        }
        obj.insert(i.key(),QJsonValue(arr));
    }
    json.insert("history",obj);
    obj = QJsonObject();
    
    i = QMapIterator<QString,QList<QString>>(analysisPageSettings_);
    while(i.hasNext()){
        i.next();
        QJsonArray arr;
        for(auto setting:i.value()){
            arr.append(setting);
        }
        obj.insert(i.key(),QJsonValue(arr));
    }
    json.insert("analysis",obj);
    
    QFile file;
    file.setFileName("settings.json");
    
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }
    QJsonDocument doc(json);
    file.write(doc.toJson());
    file.close();
}
void SettingsReader::setCurrentDatalist( QList<QString> list, QString key)
{
    datalists_[key] = list;
    if(reading_){
        saveDatalist();
    }
}

const QList<QString> SettingsReader::getDatalist(QString key)
{
    if(key == "X"){
        return datalists_["X"];
    }
    else{
        return datalists_["Y"];
    }
}
void SettingsReader::readDatalistFile()
{

    QFile fileIn("settings.txt");

    if (!fileIn.open(QFile::ReadOnly | QFile::Text)) {
        return;
    } else {
        QTextStream stream(&fileIn);
        int i = 0;
        QStringList datalistX;
        QStringList  datalistY;
        while (!stream.atEnd()){
            QString dataline = stream.readLine();
            QStringList data= dataline.split(",");
            if(i == indexX_){
                datalistX.append(data);
            }
            else if(i == indexY_){
                datalistY.append(data);
            }
            i++;
        }
        // previous stream operation sets "" to first
        //list element so we restructure list before saving it
        if(!datalistX.empty()){
            datalistX.erase(datalistX.begin());
        }
        if(!datalistY.empty()){
            datalistY.erase(datalistY.begin());
        }
        datalists_["X"] =datalistX;
        datalists_["Y"] =datalistY;
    }

    fileIn.close();
}
