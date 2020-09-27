#ifndef TIMERVIEW_H
#define TIMERVIEW_H

#include "timer/date_time_timer.h"
#include "timer/countdown_timer.h"
#include "timer/chrono_down_timer.h"

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
    void flexOutputSelectChange(int);
    void reset();

private:
    void connectSignal();
    void registeOutputFile();
    QString registeFlexOutputFile(int, QString const &);
    Ui::TimerView *ui;
    DateTimeTimer dateTime;
    CountDownTimer countdown;
    ChronoDownTimer chronoDown;
};

#endif // TIMERVIEW_H
