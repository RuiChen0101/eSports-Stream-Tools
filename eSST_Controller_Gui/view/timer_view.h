#ifndef TIMERVIEW_H
#define TIMERVIEW_H

#include "timer/date_time_timer.h"
#include "timer/countdown_timer.h"
#include "timer/chrono_down_timer.h"
#include "file/config_file.h"

#include <QDebug>
#include <QWidget>

namespace Ui {
class TimerView;
}

class TimerView : public QWidget{
    Q_OBJECT

public:
    TimerView(QWidget *parent = nullptr);
    ~TimerView();

private slots:
    void timeUpdate();
    void countDownSettingUpdate();
    void chronoDownSettingUpdate();
    void dateTimeSettingUpdate();
    void countDownStatusUpdate();
    void chronoDownStatusUpdate();
    void flexOutputSelectChange(int);
    void reset();

private:
    void initShareConfig();
    void connectSignal();
    void registeOutputFile();
    void loadConfig();
    void saveConfig();
    QString registeFlexOutputFile(int, QString const &);
    Ui::TimerView *ui;
    DateTimeTimer dateTime;
    CountDownTimer countdown;
    ChronoDownTimer chronoDown;
    ConfigFile config;
};

#endif // TIMERVIEW_H
