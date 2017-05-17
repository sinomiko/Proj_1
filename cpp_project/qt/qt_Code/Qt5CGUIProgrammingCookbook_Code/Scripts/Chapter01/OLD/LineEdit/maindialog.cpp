/*
 * Copyright (c) 2014, Bojan Bizic
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "maindialog.h"
#include "ui_maindialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    QLabel* lblUserName = new QLabel("&User Name:");
    QLabel* lblPassword = new QLabel("&Password:");
    QLabel* lblIpAddress = new QLabel("&IP Address:");

    QLineEdit* leUserName = new QLineEdit();
    QLineEdit* lePassword = new QLineEdit();
    QLineEdit* leIpAddress = new QLineEdit();

    lblUserName->setBuddy(leUserName);
    lblPassword->setBuddy(lePassword);
    lblIpAddress->setBuddy(leIpAddress);

    lePassword->setEchoMode(QLineEdit::Password);
    leIpAddress->setInputMask("000.000.000.000;_");

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->addWidget(lblUserName, 0,0);
    gridLayout->addWidget(leUserName,0,1);
    gridLayout->addWidget(lblPassword,1,0);
    gridLayout->addWidget(lePassword, 1,1);
    gridLayout->addWidget(lblIpAddress, 2,0);
    gridLayout->addWidget(leIpAddress,2,1);

    connect(leUserName, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    connect(leIpAddress, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
}

void MainDialog::onTextChanged(const QString &text)
{
    this->setWindowTitle(text);
}

MainDialog::~MainDialog()
{
    delete ui;
}
