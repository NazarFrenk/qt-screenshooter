#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->startStopBtn, &QPushButton::clicked, this, &MainWindow::grabProcess);

    ui->statusbar->showMessage("Grab: stopped");

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
    if(mWorker == nullptr)
    {
        mWorker = new Worker();
        mWorker->start();
        ui->statusbar->showMessage("Grab: active");
    }
    else
    {
        mWorker->terminate();
        mWorker = nullptr;
        ui->statusbar->showMessage("Grab: stopped");
    }
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
    QDir databasePath;
    QString path = databasePath.currentPath() + "/data.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS data (id INTEGER NOT NULL PRIMARY KEY, data BLOB, hash TEXT, percentage REAL);");
    query.exec();
}

void MainWindow::loadData()
{
    // TODO - write implementations
}
