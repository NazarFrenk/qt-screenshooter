#ifndef WORKER_H
#define WORKER_H

#include <QThread>

class Worker : public QThread
{
    Q_OBJECT
public:
    Worker();
};

#endif // WORKER_H
