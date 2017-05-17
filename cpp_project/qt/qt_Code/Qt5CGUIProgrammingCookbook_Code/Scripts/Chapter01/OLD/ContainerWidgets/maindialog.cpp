#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::on_btnToggle_clicked()
{
    if(ui->groupBox->isHidden())
    {
        ui->groupBox->show();
    }
    else
    {
        ui->groupBox->hide();
    }
}
