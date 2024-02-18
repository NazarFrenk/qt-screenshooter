#include "Worker.h"

Worker::Worker(int id)
{
    // TODO - add timer
    // just for test
    mLastId = id;
    qDebug() << "ID from MainWindow" << mLastId;

    mTimer = new QTimer();
    connect(mTimer, &QTimer::timeout, this, &Worker::processing);
    mTimer->start(1000); // TODO - set to 60000
}

void Worker::processing()
{
    grabSpanshot();
    createHash();
    addToDB();
}

void Worker::stop()
{
    mTimer->stop();
}

void Worker::grabSpanshot()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    mCurrentImage = screen->grabWindow(0);
}

void Worker::createHash()
{
    // TODO - write implementations
    QCryptographicHash md5(QCryptographicHash::Md5);
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    mCurrentImage.save(&buffer, "PNG");
    md5.addData(bArray);
    QString Md5Str = md5.result().toHex();
    qDebug() << Md5Str << bArray.count();
}

void Worker::compareImages()
{
    // TODO - write implementations
}

void Worker::addToDB()
{
    // TODO - write implementations
    // there are some records in DB
    if (mLastId > 0)
    {
        mLastId++;
    }
    // it will be first
    else
    {
        mLastId = 1;
    }

    qDebug() << "Inserted id:" << mLastId;
}
