#include "Worker.h"

Worker::Worker() {}

void Worker::grabSpanshot()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    mCurrentImage = screen->grabWindow(0);
}

void Worker::createHash()
{
    // TODO - write implementations
}

void Worker::compareImages()
{
    // TODO - write implementations
}

void Worker::addToDB()
{
    // TODO - write implementations
}
