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
};

#endif // WORKER_H
