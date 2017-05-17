#include "maindialog.h"
#include "ui_maindialog.h"
#include <QTime>
#include <QPushButton>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    m_stopWatch = new Stopwatch();
    m_btnStart = new QPushButton("Start");
    m_btnStop = new QPushButton("Stop");

    ui->gridLayout->addWidget(m_stopWatch, 0, 0, 0, 2);
    ui->gridLayout->addWidget(m_btnStart, 1,0);
    ui->gridLayout->addWidget(m_btnStop, 1, 1);

    connect(m_btnStart, SIGNAL(clicked()), this, SLOT(startStopwatch()));
    connect(m_btnStop, SIGNAL(clicked()), this, SLOT(stopStopwatch()));
}

void MainDialog::startStopwatch(){
    m_stopWatch->Start();
}

void MainDialog::stopStopwatch(){
    m_stopWatch->Stop();
}

MainDialog::~MainDialog()
{
    delete ui;
}
