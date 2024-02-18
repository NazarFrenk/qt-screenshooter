#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startStopBtn, &QPushButton::clicked, this, &MainWindow::grabProcess);

    createDB();
    loadData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::grabProcess()
{
    // TODO - write implementations
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(mWorker && mWorker->isRunning())
    {
        mWorker->terminate();
    }
}

void MainWindow::createDB()
{
    // TODO - write implementations
}

void MainWindow::loadData()
{
    // TODO - write implementations
}
