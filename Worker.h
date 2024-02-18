#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QSqlQuery>
#include <QTimer>
#include <QCryptographicHash>
#include <QScreen>
#include <QGuiApplication>
#include <QPixmap>
#include <QBuffer>
#include <QDebug>

class Worker : public QThread
{
    Q_OBJECT
public:
    Worker(int id);

private slots:
    void processing();
    void stop();

private:
    void grabSpanshot(); // take a screenshot of the desktop
    void createHash(); // create md5 of image
    void compareImages(); // compare images
    void addToDB(); // add new item to database

    int mLastId = -1;
    QByteArray mImageData;
    QString mMd5Str = "";
    QPixmap mCurrentImage;
    QTimer* mTimer = nullptr;
};

#endif // WORKER_H
