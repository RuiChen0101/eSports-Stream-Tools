#include "timerview.h"
#include "ui_timerview.h"
#include "utility/timetick.h"

TimerView::TimerView(QWidget *parent) :
    QWidget(parent), ui(new Ui::TimerView){
    ui->setupUi(this);
    connectSignal();
    ui->countdown_target->setDateTime(QDateTime::currentDateTime());
    dateTimeSettingUpdate();
    countDownSettingUpdate();
    chronoDownSettingUpdate();
}

TimerView::~TimerView(){
    delete ui;
}

void TimerView::timeUpdate(){
    dateTime.timeUpdate();
    countDown.timeUpdate();
    chronoDown.timeUpdate();
    ui->datetime_live_output->setText(dateTime.getString());
    ui->countdown_live_output->setText(countDown.getString());
    ui->chronodown_live_output->setText(chronoDown.getString());
}


void TimerView::countDownSettingUpdate(){
    countDown.setTarget(ui->countdown_target->dateTime());
    countDown.setFormat(ui->countdown_formate_edit->text());
    countDown.setTimeoutMsg(ui->countdown_timeout_msg_edit->text());
    countDown.setDoubleDigit(ui->countdown_double_digit_check->isChecked());
    ui->countdown_live_output->setText(countDown.getString());
}

void TimerView::chronoDownSettingUpdate(){
    chronoDown.setTarget(ui->chronodown_target->time());
    chronoDown.setFormat(ui->chronodown_formate_edit->text());
    chronoDown.setTimeoutMsg(ui->chronodown_timeout_msg_edit->text());
    chronoDown.setDoubleDigit(ui->chronodown_double_digit_check->isChecked());
    ui->chronodown_live_output->setText(chronoDown.getString());
}

void TimerView::dateTimeSettingUpdate(){
    dateTime.setFormat(ui->datetime_formate_edit->text());
    ui->datetime_live_output->setText(dateTime.getString());
}

void TimerView::countDownStatusUpdate(){
    QString senderName = this->sender()->objectName();
    if(senderName == ui->countdown_start_btn->objectName()){
        countDown.setStatus(CountDownTimer::START);
        ui->countdown_start_btn->setEnabled(false);
        ui->countdown_stop_btn->setEnabled(true);
    }else if(senderName == ui->countdown_stop_btn->objectName()){
        countDown.setStatus(CountDownTimer::STOP);
        ui->countdown_start_btn->setEnabled(true);
        ui->countdown_stop_btn->setEnabled(false);
    }
    ui->countdown_live_output->setText(countDown.getString());
}

void TimerView::chronoDownStatusUpdate(){
    QString senderName = this->sender()->objectName();
    if(senderName == ui->chronodown_function_btn->objectName() && ui->chronodown_function_btn->text() == "Start"){
        chronoDown.setStatus(ChronoDownTimer::START);
        ui->chronodown_stop_btn->setEnabled(true);
        ui->chronodown_function_btn->setText("Pause");
    }else if(senderName == ui->chronodown_function_btn->objectName() && ui->chronodown_function_btn->text() == "Pause"){
        chronoDown.setStatus(ChronoDownTimer::PAUSE);
        ui->chronodown_function_btn->setText("Resume");
    }else if(senderName == ui->chronodown_function_btn->objectName() && ui->chronodown_function_btn->text() == "Resume"){
        chronoDown.setStatus(ChronoDownTimer::RESUME);
        ui->chronodown_function_btn->setText("Pause");
    }else if(senderName == ui->chronodown_stop_btn->objectName()){
        chronoDown.setStatus(ChronoDownTimer::STOP);
        ui->chronodown_stop_btn->setEnabled(false);
        ui->chronodown_function_btn->setText("Start");
    }
    ui->chronodown_live_output->setText(chronoDown.getString());
}

void TimerView::reset(){
    QString senderName = this->sender()->objectName();
    if(senderName == ui->countdown_formate_edit_reset->objectName()){
        ui->countdown_formate_edit->setText("$m:$s");
    }else if(senderName == ui->countdown_target_reset->objectName()){
        ui->countdown_target->setDateTime(QDateTime::currentDateTime());
    }else if(senderName == ui->chronodown_formate_edit_reset->objectName()){
        ui->chronodown_formate_edit->setText("$h:$m:$s");
    }else if(senderName == ui->chronodown_target_reset->objectName()){
        ui->chronodown_target->setTime(QTime(0, 0, 0));
    }
}

void TimerView::connectSignal(){
    connect(TimeTick::inst(), SIGNAL(timeUpdate()), this, SLOT(timeUpdate()));

    connect(ui->datetime_formate_edit, SIGNAL(textChanged(QString)), this, SLOT(dateTimeSettingUpdate()));

    connect(ui->countdown_target, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(countDownSettingUpdate()));
    connect(ui->countdown_formate_edit, SIGNAL(textChanged(QString)), this, SLOT(countDownSettingUpdate()));
    connect(ui->countdown_timeout_msg_edit, SIGNAL(textChanged(QString)), this, SLOT(countDownSettingUpdate()));
    connect(ui->countdown_double_digit_check, SIGNAL(stateChanged(int)), this, SLOT(countDownSettingUpdate()));

    connect(ui->chronodown_target, SIGNAL(timeChanged(QTime)), this, SLOT(chronoDownSettingUpdate()));
    connect(ui->chronodown_formate_edit, SIGNAL(textChanged(QString)), this, SLOT(chronoDownSettingUpdate()));
    connect(ui->chronodown_timeout_msg_edit, SIGNAL(textChanged(QString)), this, SLOT(chronoDownSettingUpdate()));
    connect(ui->chronodown_double_digit_check, SIGNAL(stateChanged(int)), this, SLOT(chronoDownSettingUpdate()));

    connect(ui->countdown_start_btn, SIGNAL(clicked(bool)), this, SLOT(countDownStatusUpdate()));
    connect(ui->countdown_stop_btn, SIGNAL(clicked(bool)), this, SLOT(countDownStatusUpdate()));

    connect(ui->chronodown_function_btn, SIGNAL(clicked(bool)), this, SLOT(chronoDownStatusUpdate()));
    connect(ui->chronodown_stop_btn, SIGNAL(clicked(bool)), this, SLOT(chronoDownStatusUpdate()));

    connect(ui->countdown_formate_edit_reset, SIGNAL(clicked(bool)), this, SLOT(reset()));
    connect(ui->countdown_target_reset, SIGNAL(clicked(bool)), this, SLOT(reset()));
    connect(ui->chronodown_formate_edit_reset, SIGNAL(clicked(bool)), this, SLOT(reset()));
    connect(ui->chronodown_target_reset, SIGNAL(clicked(bool)), this, SLOT(reset()));
}
