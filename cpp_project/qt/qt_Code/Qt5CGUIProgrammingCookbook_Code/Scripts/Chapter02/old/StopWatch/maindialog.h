#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "stopwatch.h"


namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private:
    Ui::MainDialog *ui;
    Stopwatch* m_stopWatch;
    QPushButton* m_btnStart;
    QPushButton* m_btnStop;

private slots:
    void startStopwatch();
    void stopStopwatch();

};

#endif // MAINDIALOG_H
