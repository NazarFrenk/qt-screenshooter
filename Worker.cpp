#include "Worker.h"

Worker::Worker(int id)
{
    mLastId = id;
    qDebug() << "ID from MainWindow" << mLastId;

    mTimer = new QTimer();
    connect(mTimer, &QTimer::timeout, this, &Worker::processing);
    mTimer->start(5000);
}

void Worker::processing()
{
    grabSpanshot();
    createHash();
    compareImages();
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
    QCryptographicHash md5(QCryptographicHash::Md5);
    QBuffer buffer(&mImageData);
    buffer.open(QIODevice::WriteOnly);
    mCurrentImage.save(&buffer, "BMP");
    md5.addData(mImageData);
    mMd5Str = md5.result().toHex();
    qDebug() << mMd5Str << mImageData.count();
}

void Worker::compareImages()
{
    if (mLastId > 1)
    {
        QSqlQuery query;
        query.prepare("SELECT data FROM data WHERE id = (:id)");
        query.bindValue(":id", mLastId - 1);
        query.exec();

        QByteArray prevImageData;

        while (query.next()) {
            prevImageData = query.value("data").toByteArray();
        }

        QImage temp = QImage::fromData(prevImageData);

        cv::Mat prevImageMat = cv::Mat(temp.width(), temp.height(), CV_8UC3, prevImageData.data());
        cv::Mat curImageMat = cv::Mat(mCurrentImage.width(), mCurrentImage.height(), CV_8UC3, mImageData.data());double errorL2 = cv::norm(curImageMat, prevImageMat, cv::NORM_L2, cv::noArray());

        mSimilarity = (1 - errorL2 / (mCurrentImage.width() * mCurrentImage.height())) * 100;
    }
    // it will be first
    else
    {
        mSimilarity = 0;
    }
}

void Worker::addToDB()
{
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
    query.bindValue(":percentage", mSimilarity);
    query.exec();

    qDebug() << "Inserted id:" << mLastId;

    emit newRecord(mLastId);
}
