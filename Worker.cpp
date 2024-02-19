#include "Worker.h"

Worker::Worker(int id)
{
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
    QBuffer buffer(&mImageData);
    buffer.open(QIODevice::WriteOnly);
    mCurrentImage.save(&buffer, "PNG");
    md5.addData(mImageData);
    mMd5Str = md5.result().toHex();
    qDebug() << mMd5Str << mImageData.count();
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

    QSqlQuery query;
    query.prepare("INSERT INTO data (id, data, hash, percentage) "
                "VALUES (:id, :data, :hash, :percentage)");
    query.bindValue(":id", mLastId);
    query.bindValue(":data", mImageData);
    query.bindValue(":hash", mMd5Str);
    query.bindValue(":percentage", 0); // TODO - replace by variable
    query.exec();

    qDebug() << "Inserted id:" << mLastId;

    emit newRecord(mLastId);
}
