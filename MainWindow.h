#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
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

private:
    void closeEvent(QCloseEvent *event) override;

    Ui::MainWindow *ui;

    Worker* mWorker = nullptr;
};
#endif // MAINWINDOW_H
