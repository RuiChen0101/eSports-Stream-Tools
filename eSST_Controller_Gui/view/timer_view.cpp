#include "timer_view.h"
#include "ui_timer_view.h"
#include "file/file_manager.h"
#include "utility/timetick.h"
#include "utility/signal_bus.h"

TimerView::TimerView(QWidget *parent) :
    QWidget(parent), ui(new Ui::TimerView), config("TimerViewConfig.json"){
    ui->setupUi(this);
    loadConfig();
    connectSignal();
    registeOutputFile();
    ui->countdown_target->setDateTime(QDateTime::currentDateTime());
    dateTimeSettingUpdate();
    countDownSettingUpdate();
    chronoDownSettingUpdate();
}

TimerView::~TimerView(){
    saveConfig();
    delete ui;
}

void TimerView::timeUpdate(){
    dateTime.timeUpdate();
    countdown.timeUpdate();
    chronoDown.timeUpdate();
    ui->datetime_live_output->setText(dateTime.getString());
    ui->countdown_live_output->setText(countdown.getString());
    ui->chronodown_live_output->setText(chronoDown.getString());
}


void TimerView::countDownSettingUpdate(){
    countdown.setTarget(ui->countdown_target->dateTime());
    countdown.setFormat(ui->countdown_formate_edit->text());
    countdown.setTimeoutMsg(ui->countdown_timeout_msg_edit->text());
    countdown.setDoubleDigit(ui->countdown_double_digit_check->isChecked());
    ui->countdown_live_output->setText(countdown.getString());
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
        countdown.setStatus(CountDownTimer::START);
        ui->countdown_start_btn->setEnabled(false);
        ui->countdown_stop_btn->setEnabled(true);
    }else if(senderName == ui->countdown_stop_btn->objectName()){
        countdown.setStatus(CountDownTimer::STOP);
        ui->countdown_start_btn->setEnabled(true);
        ui->countdown_stop_btn->setEnabled(false);
    }
    ui->countdown_live_output->setText(countdown.getString());
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

void TimerView::flexOutputSelectChange(int index){
    QString senderName = this->sender()->objectName();
    if(senderName == ui->flex_output1_select->objectName()){
        registeFlexOutputFile(index, "FlexOutput1.txt");
    }else if(senderName == ui->flex_output2_select->objectName()){
        registeFlexOutputFile(index, "FlexOutput2.txt");
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

    connect(ui->flex_output1_select, SIGNAL(currentIndexChanged(int)), this, SLOT(flexOutputSelectChange(int)));
    connect(ui->flex_output2_select, SIGNAL(currentIndexChanged(int)), this, SLOT(flexOutputSelectChange(int)));
}

void TimerView::registeOutputFile(){
    QString dateTimeFilePath = FileManager::inst()->registeTimerFile(&dateTime, "DateTime.txt");
    QString countdownFilePath = FileManager::inst()->registeTimerFile(&countdown, "Countdown.txt");
    QString chronoDownFilePath = FileManager::inst()->registeTimerFile(&chronoDown, "ChronoDown.txt");
    QString flex1FilePath = registeFlexOutputFile(ui->flex_output1_select->currentIndex(), "FlexOutput1.txt");
    QString flex2FilePath = registeFlexOutputFile(ui->flex_output2_select->currentIndex(), "FlexOutput2.txt");
    ui->datetime_output_file->setText(dateTimeFilePath);
    ui->countdown_output_file->setText(countdownFilePath);
    ui->chronodown_output_file->setText(chronoDownFilePath);
    ui->flex_output1_file->setText(flex1FilePath);
    ui->flex_output2_file->setText(flex2FilePath);
}

QString TimerView::registeFlexOutputFile(int index, QString const &fileName){
    QString filePath;
    switch (index) {
    case 0:
        filePath = FileManager::inst()->registeTimerFile(&dateTime, fileName);
        break;
    case 1:
        filePath = FileManager::inst()->registeTimerFile(&countdown, fileName);
        break;
    case 2:
        filePath = FileManager::inst()->registeTimerFile(&chronoDown, fileName);
        break;
    }
    return filePath;
}

void TimerView::loadConfig(){
    if(config.loadFile()){
        try{
            ui->flex_output1_select->setCurrentIndex(config.read("flex1_select").toInt());
            ui->flex_output2_select->setCurrentIndex(config.read("flex2_select").toInt());
            ui->datetime_formate_edit->setText(config.read("date_time_format").toString());
            ui->countdown_formate_edit->setText(config.read("countdown_format").toString());
            ui->countdown_timeout_msg_edit->setText(config.read("countdown_timeout_msg").toString());
            ui->chronodown_formate_edit->setText(config.read("chrono_down_format").toString());
            ui->chronodown_timeout_msg_edit->setText(config.read("chrono_down_timeout_msg").toString());
            ui->chronodown_target->setTime(
                QTime(
                    config.read("chrono_down_target_hour").toInt(),
                    config.read("chrono_down_target_min").toInt(),
                    config.read("chrono_down_target_sec").toInt()
            ));
            return;
        }catch(std::runtime_error &e){
            emit(SignalBus::inst()->systemMessageEvent("TimerView load config fail"));
        }
    }else{
        emit(SignalBus::inst()->systemMessageEvent("TimerView load config fail"));
    }
}

void TimerView::saveConfig(){
    config.insert("flex1_select", ui->flex_output1_select->currentIndex());
    config.insert("flex2_select", ui->flex_output2_select->currentIndex());
    config.insert("date_time_format", ui->datetime_formate_edit->text());
    config.insert("countdown_format", ui->countdown_formate_edit->text());
    config.insert("countdown_timeout_msg", ui->countdown_timeout_msg_edit->text());
    config.insert("chrono_down_format", ui->chronodown_formate_edit->text());
    config.insert("chrono_down_timeout_msg",ui->chronodown_timeout_msg_edit->text());
    config.insert("chrono_down_target_hour", ui->chronodown_target->time().hour());
    config.insert("chrono_down_target_min", ui->chronodown_target->time().minute());
    config.insert("chrono_down_target_sec", ui->chronodown_target->time().second());
}
