#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QDir>
#include <QListWidgetItem>
#include "Worker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void grabProcess();
    void getNewRecord(int newId);

signals:
    void stop();

private:
    void closeEvent(QCloseEvent *event) override;
    void createDB(); // create table if not exists
    void loadData(); // load data to listview

    Ui::MainWindow *ui;

    Worker* mWorker = nullptr;
    int mLastId = -1; // id of the latest image in DB
};
#endif // MAINWINDOW_H
