#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    ui->timer_tab_layout->addWidget(new TimerView(this));
    menuBar = new MenuBar(this);
    connectSignal();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::connectSignal(){
    connect(ui->action_github_page, SIGNAL(triggered()), menuBar, SLOT(githubPageToggled()));
    connect(ui->action_show_file_folder, SIGNAL(triggered()), menuBar, SLOT(showFileFolderToggled()));
}
