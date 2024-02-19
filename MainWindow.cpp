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
    if(mWorker == nullptr)
    {
        QSqlQuery query;
        query.prepare("SELECT MAX(id) FROM data");
        query.exec();

        if(query.next())
        {
            mLastId = query.value(0).toInt();
        }

        mWorker = new Worker(mLastId);
        connect(this, SIGNAL(stop()), mWorker, SLOT(stop()));
        connect(mWorker, SIGNAL(newRecord(int)), this, SLOT(getNewRecord(int)));
        mWorker->start();
        ui->statusbar->showMessage("Grab: active");
    }
    else
    {
        emit stop();
        mWorker->terminate();
        mWorker = nullptr;
        ui->statusbar->showMessage("Grab: stopped");
    }
}

void MainWindow::getNewRecord(int newId)
{
    mLastId = newId;
    QSqlQuery query;
    query.prepare("SELECT * FROM data WHERE id = (:id)");
    query.bindValue(":id", mLastId);
    query.exec();

    QPixmap image;
    QByteArray imageData;
    QListWidgetItem *item;

    while (query.next()) {
        imageData = query.value("data").toByteArray();
        image.loadFromData(imageData, "PNG");

        QString id = query.value("percentage").toString();
        item = new QListWidgetItem(QIcon(image), id);

        ui->listWidget->insertItem(0, item);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(mWorker && mWorker->isRunning())
    {
        emit stop();
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
    int records = -1; // number of records in table

    QSqlQuery query;
    query.prepare("SELECT COUNT (*) FROM data");
    query.exec();

    if(query.next())
    {
        records = query.value(0).toInt();
    }

    qDebug() << records;

    query.prepare("SELECT MAX(id) FROM data");
    query.exec();

    if(query.next())
    {
        mLastId = query.value(0).toInt();
    }

    qDebug() << mLastId;

    query.prepare("SELECT * FROM data ORDER BY id DESC");
    query.exec();

    QPixmap image;
    QByteArray imageData;
    QListWidgetItem *item;

    ui->listWidget->setIconSize(QSize(800, 600));
    ui->listWidget->setResizeMode(QListWidget::Adjust);

    while (query.next()) {
        imageData = query.value("data").toByteArray();
        image.loadFromData(imageData, "PNG");

        QString id = query.value("percentage").toString();
        item = new QListWidgetItem(QIcon(image), id);

        ui->listWidget->addItem(item);
    }
}
