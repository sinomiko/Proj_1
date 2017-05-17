#include "maindialog.h"
#include "ui_maindialog.h"

#include <QFileSystemModel>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    ui->treeView->setModel(model);
}

MainDialog::~MainDialog()
{
    delete ui;
}
