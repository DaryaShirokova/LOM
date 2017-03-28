#include "../inc/QEndcapWidget.h"
#include "inc/QColorBar.h"

#include <QPainter>
#include <QBrush>
#include <algorithm>
#include <QGraphicsEllipseItem>
#include <QColor>

#include <math.h>
#include <iostream>

QEndcapWidget::QEndcapWidget(QWidget *parent) : QWidget(parent) {
}


void QEndcapWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    // Set up painter.
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fill background.
    QRectF bkgRect(0, 0, this->width() - 1, this->height() - 1);
    QColor bkgColor(255,255,255);
    QBrush bkgBrush(bkgColor, Qt::SolidPattern);
    painter.setBrush(bkgBrush);
    painter.drawRect(bkgRect);

    // Color of numbers.
    QColor numColor[SECTOR_NUM];
    for(int i = 0; i < SECTOR_NUM; i++)
        numColor[i] = Qt::blue;

    // Set up boundaries.
    int d = std::min(width(), height()) - 10;
    int d2 = d / 2;
    int x0 = width()/2;
    int y0 = height()/2;
    QRect rect0(x0 - d2/2, y0 - d2/2, d2, d2);
    QRect rect1(x0 - d/2, y0 - d/2, d, d);
    double alpha0 = 0;

    // Set colors for different sectors.
    painter.setPen (Qt :: NoPen);
    for(int sector = 0; sector < amplitudes.size(); sector++) {
        double alpha1 = alpha0 + (sector + 1) * 360. / SECTOR_NUM;
        QPainterPath path;

        path.moveTo(x0, y0);
        path.arcTo(rect1, -alpha1, 360. / SECTOR_NUM);
        path.moveTo(x0, y0);
        path.arcTo(rect0, -alpha1, 360. / SECTOR_NUM);

        double q = 1 - (amplitudes.at(sector) - MIN_AMPL) / (MAX_AMPL - MIN_AMPL);
        painter.fillPath (path, QBrush(QColorBar::GetColor(q)));

        if(q < 0.5) numColor[sector] = Qt::white;
    }

    // Draw two ellipses (form of endcap).
    painter.setPen(QPen(Qt::black));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(rect1);
    painter.drawEllipse(rect0);

    // Draw lines between sectors.
    for (int i = 0; i < SECTOR_NUM; i++) {
        double alpha = alpha0 + (i * 2 * M_PI / SECTOR_NUM);
        QPoint p0 = GetRayCircleIntersection(x0, y0, d/2, alpha);
        QPoint p1 = GetRayCircleIntersection(x0, y0, d2/2, alpha);
        painter.drawLine(p0, p1);
    }

    // Clean the area.
    int penW = painter.pen().width();
    painter.setBrush(bkgBrush);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(x0 - d2/2 + penW, y0 - d2/2 + penW, d2 - 2*penW, d2 - 2*penW);

    // Set Labels with sectors numbers.
    painter.setBrush(Qt::NoBrush);
    for (int i = 0; i < SECTOR_NUM; i++) {
        painter.setPen(QPen(numColor[i]));
        double alpha = alpha0 + ((i+0.5) * 2 * M_PI / SECTOR_NUM);
        QPoint p = GetRayCircleIntersection(x0, y0, d2/2 + 20, alpha);
        p.setX(p.x() - 6);
        p.setY(p.y() + 6);
        painter.drawText(p, QString::number(i + 1));
    }
}


QPoint QEndcapWidget::GetRayCircleIntersection(int x0, int y0, int r, double alpha) {
    int x1 = x0 + round(r*cos(alpha));
    int y1 = y0 + round(r*sin(alpha));
    return QPoint(x1, y1);
}
