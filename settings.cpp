#include "settings.h"
#include "ui_settings.h"
#include <QTime>

Settings::Settings(Breaker* _break,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    breaker=_break;
}

void Settings::showEvent(QShowEvent* event)
{
    Q_UNUSED(event);
ui->timestamp->setTime(QTime(breaker->getTimestamp()/60,breaker->getTimestamp()%60));
ui->break_2->setTime(QTime(breaker->getBreaktime()/60,breaker->getBreaktime()%60));

}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_save_clicked()
{
breaker->saveConfiguration();
emit configChange();
}


void Settings::on_reset_clicked()
{
breaker->setDefault();
ui->timestamp->setTime(QTime(breaker->getTimestamp()/60,breaker->getTimestamp()%60));
ui->break_2->setTime(QTime(breaker->getBreaktime()/60,breaker->getBreaktime()%60));
emit configChange();
}


void Settings::on_timestamp_userTimeChanged(const QTime &time)
{
breaker->setTimestamp((time.second()/60)+time.minute()+(time.hour()*60));
}


void Settings::on_break_2_userTimeChanged(const QTime &time)
{
breaker->setBreaktime((time.second()/60)+time.minute()+(time.hour()*60));
}

