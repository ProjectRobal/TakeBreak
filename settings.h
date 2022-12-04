#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QShowEvent>
#include "breaker.h"

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT
    Breaker *breaker;
public:
    explicit Settings(Breaker* _break,QWidget *parent = nullptr);

    void showEvent(QShowEvent* event);

    ~Settings();

signals:

void configChange();

private slots:
    void on_save_clicked();

    void on_reset_clicked();

    void on_timestamp_userTimeChanged(const QTime &time);

    void on_break_2_userTimeChanged(const QTime &time);

    void on_to_shutdown_stateChanged(int arg1);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
