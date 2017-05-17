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

#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::setShape(Shape shape){
    this->m_shape = shape;
}

void RenderArea::setPen(const QPen &pen){
    this->m_pen = pen;
}

void RenderArea::setBrush(const QBrush &brush){
    this->m_brush = brush;
}

void RenderArea::setAntialiased(bool antialiased)
{
    this->m_antialiased = antialiased;
    update();
}

void RenderArea::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        int x = event->x();
        int y = event->y();

        DrawableElement element;
        element.shape = this->m_shape;
        element.points[0] = QPoint(x, y + 70);
        element.points[1] = QPoint(x +10, y );
        element.points[2] = QPoint(x + 80, y +20);
        element.points[3] = QPoint(x + 90, y + 80);
        element.brush = this->m_brush;
        element.pen = this->m_pen;

        this->m_elemets.append(element);
        update();
    }
}

void RenderArea::paintEvent(QPaintEvent *event){
    QPainterPath path;
    path.moveTo(20, 80);
    path.lineTo(20, 30);
    path.cubicTo(80, 0, 50, 50, 80, 80);

    int startAngle = 20 * 16;
    int arcLength = 120 * 16;

    QPainter painter(this);

    painter.save();

    if (m_antialiased)
        painter.setRenderHint(QPainter::Antialiasing, true);

    foreach(DrawableElement element, m_elemets){
        painter.setPen(element.pen);
        painter.setBrush(element.brush);

        QRect rect(element.points[1].x(), element.points[1].y(), 100, 100);
        switch(element.shape){
            case Line:
                painter.drawLine(rect.bottomLeft(), rect.topRight());
                break;
            case Points:
                painter.drawPoints(element.points, 4);
                break;
            case Polyline:
                painter.drawPolyline(element.points, 4);
                break;
            case Polygon:
                painter.drawPolygon(element.points, 4);
                break;
            case Rect:
                painter.drawRect(rect);
                break;
            case RoundedRect:
                painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
                break;
            case Ellipse:
                painter.drawEllipse(rect);
                break;
            case Arc:
                painter.drawArc(rect, startAngle, arcLength);
                break;
            case Chord:
                painter.drawChord(rect, startAngle, arcLength);
                break;
            case Pie:
                painter.drawPie(rect, startAngle, arcLength);
                break;
            case Path:
                painter.drawPath(path);
                break;
            case Text:
                painter.drawText(rect, Qt::AlignCenter, tr("Drawing text!"));
                break;
        }
    }

    painter.restore();
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
