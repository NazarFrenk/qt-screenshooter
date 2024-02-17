#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QtSql>

class Worker : public QThread
{
    Q_OBJECT
public:
    Worker();
};

#endif // WORKER_H
