#ifndef TIMERVIEW_H
#define TIMERVIEW_H

#include "timer/datetimetimer.h"
#include "timer/countdowntimer.h"
#include "timer/chronodowntimer.h"

#include <QDebug>
#include <QWidget>

namespace Ui {
class TimerView;
}

class TimerView : public QWidget{
    Q_OBJECT

public:
    explicit TimerView(QWidget *parent = nullptr);
    ~TimerView();
private slots:
    void timeUpdate();
    void countDownSettingUpdate();
    void chronoDownSettingUpdate();
    void dateTimeSettingUpdate();
    void countDownStatusUpdate();
    void chronoDownStatusUpdate();
    void reset();
private:
    void connectSignal();
    Ui::TimerView *ui;
    DateTimeTimer dateTime;
    CountDownTimer countDown;
    ChronoDownTimer chronoDown;
};

#endif // TIMERVIEW_H
