#include "maindialog.h"
#include "ui_maindialog.h"

#include <QDir>
#include <QDirIterator>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    QDir dir("/Users");
     dir.setFilter(QDir::Dirs | QDir::Hidden | QDir::NoSymLinks);

     QIcon icon;
     icon.addFile(":/icons/Folder.ico");

     QDirIterator iterator(dir.absolutePath(), QDirIterator::NoIteratorFlags);
       while (iterator.hasNext()) {
          iterator.next();
          if (iterator.fileInfo().isDir()) {
             QString filePath = iterator.filePath();
             QListWidgetItem* item = new QListWidgetItem(icon, filePath);
             ui->listWidget->addItem(item);
          }
       }
}

MainDialog::~MainDialog()
{
    delete ui;
}
