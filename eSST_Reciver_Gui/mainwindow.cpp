#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    menuBar = new MenuBar(this);
    statusBar = new StatusBar(ui->status_bar, this);

    ui->main_layout->addWidget(new NetworkView(this));
    connectSignal();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::connectSignal(){
    connect(ui->action_github_page, SIGNAL(triggered()), menuBar, SLOT(githubPageToggled()));
}
