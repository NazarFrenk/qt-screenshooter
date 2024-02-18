#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QtSql>
#include <QTimer>
#include <QCryptographicHash>

class Worker : public QThread
{
    Q_OBJECT
public:
    Worker();

private:
    void grabSpanshot(); // take a screenshot of the desktop
    void createHash(); // create md5 of image
    void compareImages(); // compare images
    void addToDB(); // add new item to database
};

#endif // WORKER_H
