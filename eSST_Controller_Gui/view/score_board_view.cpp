#include "score_board_view.h"
#include "ui_score_board_view.h"
#include "utility/signal_bus.h"

ScoreBoardView::ScoreBoardView(QWidget *parent) :
    QWidget(parent), ui(new Ui::ScoreBoardView), team1("team1"), team2("team2"), config("ScoreBoardViewConfig.json"){
    ui->setupUi(this);
    loadConfig();
    registeFiles();
    connectSignal();
    teamNameUpdate();
    scoreBoardSettingUpdate();
    useDoubleDigitUpdate(ui->use_digits_check->checkState());
}

ScoreBoardView::~ScoreBoardView(){
    saveConfig();
    delete ui;
}

void ScoreBoardView::team1Update(){
    ui->team1_point_display->display(team1.getPoint());
    ui->team1_round_point_display->setText(team1.getRound());
}

void ScoreBoardView::team2Update(){
    ui->team2_point_display->display(team2.getPoint());
    ui->team2_round_point_display->setText(team2.getRound());
}

void ScoreBoardView::teamNameUpdate(){
    team1.setTeamName(ui->team1_name_edit->text());
    team2.setTeamName(ui->team2_name_edit->text());
}

void ScoreBoardView::scoreBoardSettingUpdate(){
    team1.setInvert(ui->team1_round_invert_check->isChecked());
    team2.setInvert(ui->team2_round_invert_check->isChecked());

    Round::setBestOf(ui->best_of_edit->text().toInt());
    Round::setFormat(ui->round_format->text());

    team1.settingUpdate();
    team2.settingUpdate();
}

void ScoreBoardView::useDoubleDigitUpdate(int status){
    if(status == Qt::Checked){
        ui->round_format->setEnabled(false);
        Round::setUseDigit(true);
    }else if(status == Qt::Unchecked){
        ui->round_format->setEnabled(true);
        Round::setUseDigit(false);
    }

    team1.settingUpdate();
    team2.settingUpdate();
}

void ScoreBoardView::registeFiles(){
    ui->team1_name_output_file->setText(team1.registeNameFile());
    ui->team1_points_output_file->setText(team1.registePointFile());
    ui->team1_round_points_output_file->setText(team1.registeRoundFile());

    ui->team2_name_output_file->setText(team2.registeNameFile());
    ui->team2_points_output_file->setText(team2.registePointFile());
    ui->team2_round_points_output_file->setText(team2.registeRoundFile());
}

void ScoreBoardView::connectSignal(){
    connect(ui->team1_add_point, SIGNAL(clicked(bool)), &team1, SLOT(addPoint()));
    connect(ui->team1_add_round, SIGNAL(clicked(bool)), &team1, SLOT(addRound()));
    connect(ui->clear_point, SIGNAL(clicked(bool)), &team1, SLOT(resetPoint()));
    connect(ui->clear_round, SIGNAL(clicked(bool)), &team1, SLOT(resetRound()));
    connect(&team1, SIGNAL(contentUpdate()), this, SLOT(team1Update()));

    connect(ui->team2_add_point, SIGNAL(clicked(bool)), &team2, SLOT(addPoint()));
    connect(ui->team2_add_round, SIGNAL(clicked(bool)), &team2, SLOT(addRound()));
    connect(ui->clear_point, SIGNAL(clicked(bool)), &team2, SLOT(resetPoint()));
    connect(ui->clear_round, SIGNAL(clicked(bool)), &team2, SLOT(resetRound()));
    connect(&team2, SIGNAL(contentUpdate()), this, SLOT(team2Update()));

    connect(ui->team1_name_edit, SIGNAL(textChanged(QString)), this, SLOT(teamNameUpdate()));
    connect(ui->team2_name_edit, SIGNAL(textChanged(QString)), this, SLOT(teamNameUpdate()));

    connect(ui->best_of_edit, SIGNAL(textChanged(QString)), this, SLOT(scoreBoardSettingUpdate()));
    connect(ui->round_format, SIGNAL(textChanged(QString)), this, SLOT(scoreBoardSettingUpdate()));
    connect(ui->team1_round_invert_check, SIGNAL(stateChanged(int)), this, SLOT(scoreBoardSettingUpdate()));
    connect(ui->team2_round_invert_check, SIGNAL(stateChanged(int)), this, SLOT(scoreBoardSettingUpdate()));

    connect(ui->use_digits_check, SIGNAL(stateChanged(int)), this, SLOT(useDoubleDigitUpdate(int)));
}

void ScoreBoardView::loadConfig(){
    if(config.loadFile()){
        try{
            ui->team1_name_edit->setText(config.read("team1_name").toString());
            ui->team2_name_edit->setText(config.read("team2_name").toString());
            ui->use_digits_check->setChecked(config.read("use_digits").toBool());
            ui->round_format->setText(config.read("round_format").toString());
            ui->team1_round_invert_check->setChecked(config.read("team1_round_invert").toBool());
            ui->team2_round_invert_check->setChecked(config.read("team2_round_invert").toBool());
            ui->best_of_edit->setText(config.read("best_of").toString());
            return;
        }catch(std::runtime_error &e){
            emit(SignalBus::inst()->systemMessageEvent("ScoreBoardView load config fail"));
        }
    }else{
        emit(SignalBus::inst()->systemMessageEvent("ScoreBoardView load config fail"));
    }

}

void ScoreBoardView::saveConfig(){
    config.insert("team1_name", ui->team1_name_edit->text());
    config.insert("team2_name", ui->team1_name_edit->text());
    config.insert("use_digits", ui->use_digits_check->isChecked());
    config.insert("round_format", ui->round_format->text());
    config.insert("team1_round_invert", ui->team1_round_invert_check->isChecked());
    config.insert("team2_round_invert", ui->team2_round_invert_check->isChecked());
    config.insert("best_of", ui->best_of_edit->text());
}
