#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QWidgetAction>
#include <QLabel>
#include "breaker.h"
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Breaker *shutter;
    QTimer *timer;
    QWidgetAction *action;
    Settings *settings;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void update();

private slots:
    void on_edit_clicked();

    void on_startstop_clicked();

    void configChanged();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
