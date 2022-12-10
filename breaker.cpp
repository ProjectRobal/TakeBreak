#include "breaker.h"
#include <QProcess>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <QDateTime>

Breaker::Breaker()
{
    currentTime=0;

    if(!readConfiguration())
    {

    setDefault();

    QMessageBox err;
    err.setText("Cannot read configuration switching to default");
    err.setIcon(QMessageBox::Warning);
    err.exec();

    }

}

Breaker::Breaker(uint32_t _timestamp,uint32_t _breaktime)
    : Breaker()
{
    timestamp=_timestamp;
    breaktime=_breaktime;

    saveConfiguration();
}


void Breaker::update()
{

if(Break)
{

    if(currentTime>=5)
    {
        shutdown();
    }

}
else
{
if(currentTime>=timestamp)
{


    if(!saveConfiguration())
    {
        QMessageBox err;
        err.setText("Cannot save configuration!!");
        err.setIcon(QMessageBox::Critical);
        err.exec();
    }

    shutdown();

    currentTime=0;
}
}


++currentTime;

}

void Breaker::shutdown() const
{

#ifdef WIN32

    if(Sleep)
    {

QProcess::execute("psshutdown -d -t 0");

    }
    else
    {

QProcess::execute("shutdown /s");

    }

qDebug()<<"Take Break you idiot!";

#elif UNIX
    if(Sleep)
    {

QProcess::execute("pm-suspend");

    }
    else {


QProcess::execute("shutdown now");

    }
#else

#error "Unknown platform!!"

#endif

}

bool Breaker::readConfiguration()
{
    QFile config("./config.json");

    if(!config.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Cannot open config file";

        return false;
    }

    QJsonDocument json=QJsonDocument::fromJson(config.readAll());

    QJsonObject obj=json.object();

    if(!obj.contains("timestamp"))
    {
        return false;
    }

    if(!obj.contains("breaktime"))
    {
        return false;
    }

    if(!obj.contains("time"))
    {
        return false;
    }

    if(!obj.contains("break"))
    {
        return false;
    }

    if(!obj.contains("on_shutdown"))
    {
        return false;
    }

    timestamp=obj["timestamp"].toInt(TIMESTAMP_DEFAULT);

    breaktime=obj["breaktime"].toInt(BREAKTIME_DEFAULT);

    Break=obj["break"].toBool();

    Sleep=obj["on_shutdown"].toBool();

    if(Break)
    {

    uint32_t epoch=QDateTime::currentSecsSinceEpoch();
    uint32_t time=obj["time"].toInt();

    if(((epoch-time)/60)>=breaktime)
    {
        Break=false;

        config.close();

        saveConfiguration();
    }

    }

    config.close();

    return true;
}


bool Breaker::saveConfiguration()
{
    QFile config("./config.json");

    if(!config.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Cannot create config file";

        return false;
    }

    QJsonObject obj;

    obj["timestamp"]=static_cast<qint64>(getTimestamp());
    obj["breaktime"]=static_cast<qint64>(getBreaktime());
    obj["time"]=QDateTime::currentSecsSinceEpoch();
    obj["break"]=Break;
    obj["on_shutdown"]=Sleep;


    QJsonDocument json(obj);

    config.write(json.toJson());

    config.close();

    return true;
}

uint32_t Breaker::timeToBreak() const
{
    if(Break)
    {
        return 5-currentTime;
    }

    return timestamp-currentTime;
}

void Breaker::setDefault()
{
timestamp=TIMESTAMP_DEFAULT;
breaktime=BREAKTIME_DEFAULT;
currentTime=0;
Break=false;
Sleep=true;
saveConfiguration();
}

void Breaker::resetTimer()
{
currentTime=0;
}
