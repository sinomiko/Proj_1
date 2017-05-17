#include "stopwatch.h"


Stopwatch::Stopwatch(QWidget *parent) :
    QLCDNumber(parent)
{
    this->setDigitCount(12);
    m_timer = new QTimer();
    m_timer->setInterval(60);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateElapsed()));
    setText();
}

void Stopwatch::Start(){
    m_startTime = QTime::currentTime();
    m_timer->start();
}

void Stopwatch::Stop(){
    m_timer->stop();
}

void Stopwatch::updateElapsed(){
    setText();
}

void Stopwatch::setText(){
    int elapsedMiliseconds = m_startTime.msecsTo(QTime::currentTime());
    QTime time = QTime::fromMSecsSinceStartOfDay(elapsedMiliseconds);
    QString text = time.toString("hh:mm:ss:zzz");
    display(text);
}
