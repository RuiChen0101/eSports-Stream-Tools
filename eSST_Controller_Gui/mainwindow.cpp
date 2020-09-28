#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    menuBar = new MenuBar(this);
    statusBar = new StatusBar(ui->status_bar, this);

    ui->timer_tab_layout->addWidget(new TimerView(this));
    ui->score_tab_layout->addWidget(new ScoreBoardView(this));
    connectSignal();
}

MainWindow::~MainWindow(){
    delete ui;
    delete menuBar;
    delete statusBar;
}

void MainWindow::connectSignal(){
    connect(ui->action_github_page, SIGNAL(triggered()), menuBar, SLOT(githubPageToggled()));
    connect(ui->action_show_timer_file_folder, SIGNAL(triggered()), menuBar, SLOT(showTimerFileFolderToggled()));
    connect(ui->action_show_score_file_folder, SIGNAL(triggered()), menuBar, SLOT(showScoreFileFolderToggled()));
}
