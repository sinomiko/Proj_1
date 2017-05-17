#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gridLayout->addWidget( new QPushButton( "Foo" ), 0, 0,1 ,2);
    ui->gridLayout->addWidget( new QPushButton( "Bar" ), 1, 0 );
    ui->gridLayout->addWidget( new QPushButton( "Do XYZ" ), 1, 1 );
}

MainWindow::~MainWindow()
{
    delete ui;
}
