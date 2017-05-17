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

#include <QRadioButton>
#include <QButtonGroup>
#include <QGridLayout>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    QRadioButton* btnBlue = new QRadioButton("Blue");
    QRadioButton* btnRed = new QRadioButton("Red");
    QRadioButton* btnGreen = new QRadioButton("Green");
    btnBlue->setChecked(true);

    QRadioButton* btnUp = new QRadioButton("&Up");
    QRadioButton* btnDown = new QRadioButton("&Down");
    btnUp->setChecked(true);


    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->addWidget(btnBlue, 0,0);
    gridLayout->addWidget(btnRed, 1,0);
    gridLayout->addWidget(btnGreen, 2,0);
    gridLayout->addWidget(btnUp, 0,1);
    gridLayout->addWidget(btnDown, 1,1);

    QButtonGroup* colorsGroup = new QButtonGroup();
    colorsGroup->addButton(btnBlue);
    colorsGroup->addButton(btnRed);
    colorsGroup->addButton(btnGreen);

    QButtonGroup* upDownGroup = new QButtonGroup();
    upDownGroup->addButton(btnUp);
    upDownGroup->addButton(btnDown);
}

MainDialog::~MainDialog()
{
    delete ui;
}
