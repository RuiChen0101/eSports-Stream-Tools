#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file/file_manager.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    FileManager::changeRootFolder("/eSST/eSST_Receiver");

    menuBar = new MenuBar(this);
    statusBar = new StatusBar(ui->status_bar, this);

    ui->main_layout->addWidget(new NetworkView(this));
    connectSignal();
}

MainWindow::~MainWindow(){
    delete ui;
    delete menuBar;
    delete statusBar;
}

void MainWindow::connectSignal(){
    connect(ui->action_github_page, SIGNAL(triggered()), menuBar, SLOT(githubPageToggled()));
    connect(ui->action_show_file_folder, SIGNAL(triggered()), menuBar, SLOT(showFileFolderToggled()));
}
