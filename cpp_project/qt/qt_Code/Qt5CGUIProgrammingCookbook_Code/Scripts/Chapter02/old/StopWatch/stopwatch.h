#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QLCDNumber>
#include <QTimer>
#include <QTime>

class Stopwatch : public QLCDNumber
{
    Q_OBJECT
public:
    explicit Stopwatch(QWidget *parent = 0);
    void Start();
    void Stop();

signals:

public slots:

private:
    QTimer*  m_timer;
    QTime   m_startTime;
    void setText();
private slots:
    void updateElapsed();

};

#endif // STOPWATCH_H
