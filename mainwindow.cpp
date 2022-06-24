#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    ui->time->setReadOnly(true);

    timer=new QTimer(this);

    timer->setInterval(60000); // one minute

    shutter=new Breaker();

    settings=new Settings(shutter,this);

    action=new QWidgetAction(parent);

    action->setDefaultWidget(settings);

    ui->menuSettings->addAction(action);

    QObject::connect(timer,&QTimer::timeout,this,&MainWindow::update);

    QObject::connect(settings,&Settings::configChange,this,&MainWindow::configChanged);

    update();

    timer->start();

    this->ui->statusbar->showMessage("Running...");
}

void MainWindow::update()
{
    shutter->update();

    this->ui->time->setTime(QTime(shutter->timeToBreak()/60,shutter->timeToBreak()%60));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete shutter;
    delete settings;
    delete action;
}


void MainWindow::on_edit_clicked()
{

}


void MainWindow::on_startstop_clicked()
{

if(timer->isActive())
{
    timer->stop();
    this->ui->startstop->setText("Start");
    this->ui->statusbar->showMessage("Stopped");
}
else
{
    timer->start();
    this->ui->startstop->setText("Stop");
    this->ui->statusbar->showMessage("Running...");
}

}

void MainWindow::configChanged()
{

    shutter->resetTimer();

    this->ui->time->setTime(QTime(shutter->timeToBreak()/60,shutter->timeToBreak()%60));

}

