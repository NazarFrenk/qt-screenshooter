#include "Worker.h"

Worker::Worker()
{
    // TODO - add timer
    // just for test
    grabSpanshot();
    createHash();
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
}
