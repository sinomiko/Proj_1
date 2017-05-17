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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QGridLayout>

const int IdRole = Qt::UserRole;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLabel* shapeLabel = new QLabel(tr("Shape: "));
    ui->mainToolBar->addWidget(shapeLabel);
    shapeComboBox = new QComboBox;
    shapeComboBox->addItem(tr("Polygon"), RenderArea::Polygon);
    shapeComboBox->addItem(tr("Rectangle"), RenderArea::Rect);
    shapeComboBox->addItem(tr("Rounded Rectangle"), RenderArea::RoundedRect);
    shapeComboBox->addItem(tr("Ellipse"), RenderArea::Ellipse);
    shapeComboBox->addItem(tr("Pie"), RenderArea::Pie);
    shapeComboBox->addItem(tr("Chord"), RenderArea::Chord);
    shapeComboBox->addItem(tr("Path"), RenderArea::Path);
    shapeComboBox->addItem(tr("Line"), RenderArea::Line);
    shapeComboBox->addItem(tr("Polyline"), RenderArea::Polyline);
    shapeComboBox->addItem(tr("Arc"), RenderArea::Arc);
    shapeComboBox->addItem(tr("Points"), RenderArea::Points);
    shapeComboBox->addItem(tr("Text"), RenderArea::Text);
    ui->mainToolBar->addWidget(shapeComboBox);
    ui->mainToolBar->addSeparator();


    QLabel* penWidthLabel = new QLabel(tr("Pen Width: "));
    ui->mainToolBar->addWidget(penWidthLabel);
    penWidthSpinBox = new QSpinBox;
    penWidthSpinBox->setRange(0, 20);
    ui->mainToolBar->addWidget(penWidthSpinBox);
    ui->mainToolBar->addSeparator();

    penStyleComboBox = new QComboBox;
    penStyleComboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidLine));
    penStyleComboBox->addItem(tr("Dash"), static_cast<int>(Qt::DashLine));
    penStyleComboBox->addItem(tr("Dot"), static_cast<int>(Qt::DotLine));
    penStyleComboBox->addItem(tr("Dash Dot"), static_cast<int>(Qt::DashDotLine));
    penStyleComboBox->addItem(tr("Dash Dot Dot"), static_cast<int>(Qt::DashDotDotLine));
    penStyleComboBox->addItem(tr("None"), static_cast<int>(Qt::NoPen));
    QLabel* penStyleLabel = new QLabel(tr("Pen Style: "));
    ui->mainToolBar->addWidget(penStyleLabel);
    ui->mainToolBar->addWidget(penStyleComboBox);
    ui->mainToolBar->addSeparator();

    brushStyleComboBox = new QComboBox;
    brushStyleComboBox->addItem(tr("Linear Gradient"),
            static_cast<int>(Qt::LinearGradientPattern));
    brushStyleComboBox->addItem(tr("Radial Gradient"),
            static_cast<int>(Qt::RadialGradientPattern));
    brushStyleComboBox->addItem(tr("Conical Gradient"),
            static_cast<int>(Qt::ConicalGradientPattern));
    brushStyleComboBox->addItem(tr("Texture"), static_cast<int>(Qt::TexturePattern));
    brushStyleComboBox->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
    brushStyleComboBox->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
    brushStyleComboBox->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
    brushStyleComboBox->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
    brushStyleComboBox->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
    brushStyleComboBox->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
    brushStyleComboBox->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
    brushStyleComboBox->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
    brushStyleComboBox->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
    brushStyleComboBox->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
    brushStyleComboBox->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
    brushStyleComboBox->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
    brushStyleComboBox->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
    brushStyleComboBox->addItem(tr("Dense 7"), static_cast<int>(Qt::Dense7Pattern));
    brushStyleComboBox->addItem(tr("None"), static_cast<int>(Qt::NoBrush));

    QLabel* brushStyleLabel = new QLabel(tr("Brush: "));
    ui->mainToolBar->addWidget(brushStyleLabel);
    ui->mainToolBar->addWidget(brushStyleComboBox);
    ui->mainToolBar->addSeparator();

    antialiasingCheckBox = new QCheckBox(tr("Antialiasing"));
    ui->mainToolBar->addWidget(antialiasingCheckBox);


    renderArea = new RenderArea();
    QGridLayout* grid = new QGridLayout();
    grid->addWidget(renderArea,0,0);

    ui->centralWidget->setLayout(grid);

    connect(shapeComboBox, SIGNAL(activated(int)), this, SLOT(shapeChanged()));
    connect(penWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(penChanged()));
    connect(penStyleComboBox, SIGNAL(activated(int)),this, SLOT(penChanged()));
    connect(brushStyleComboBox, SIGNAL(activated(int)), this, SLOT(brushChanged()));
    connect(antialiasingCheckBox, SIGNAL(toggled(bool)), renderArea, SLOT(setAntialiased(bool)));

    shapeChanged();
    penChanged();
    brushChanged();

    setWindowTitle(tr("Drawing with QPainter"));
}

void MainWindow::shapeChanged(){
    RenderArea::Shape shape = RenderArea::Shape(shapeComboBox->itemData(
            shapeComboBox->currentIndex(), IdRole).toInt());
    renderArea->setShape(shape);
}

void MainWindow::penChanged(){
    int width = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(
            penStyleComboBox->currentIndex(), IdRole).toInt());
    Qt::PenCapStyle cap = Qt::RoundCap;
    Qt::PenJoinStyle join = Qt::RoundJoin;

    renderArea->setPen(QPen(Qt::blue, width, style, cap, join));
}

void MainWindow::brushChanged(){
    Qt::BrushStyle style = Qt::BrushStyle(brushStyleComboBox->itemData(
            brushStyleComboBox->currentIndex(), IdRole).toInt());

    if (style == Qt::LinearGradientPattern) {
        QLinearGradient linearGradient(0,0, 1, 1);
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, Qt::blue);
        linearGradient.setColorAt(1.0, Qt::black);
        linearGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        renderArea->setBrush(linearGradient);
    } else if (style == Qt::RadialGradientPattern) {
        QRadialGradient radialGradient(0,0, 1, 5, 5);
        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(0.2, Qt::green);
        radialGradient.setColorAt(1.0, Qt::black);
        radialGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        renderArea->setBrush(radialGradient);
    } else if (style == Qt::ConicalGradientPattern) {
        QConicalGradient conicalGradient(0,0, 0);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.7, Qt::red);
        conicalGradient.setColorAt(1.0, Qt::black);
        conicalGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        renderArea->setBrush(conicalGradient);
    } else if (style == Qt::TexturePattern) {
        renderArea->setBrush(QBrush(QPixmap(":/Images/green-grass-texture.png")));
    } else {
        renderArea->setBrush(QBrush(Qt::green, style));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
