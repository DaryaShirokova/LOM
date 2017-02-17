#include "../inc/QEndcapWidget.h"
#include <QPainter>
#include <QBrush>
#include <algorithm>
#include <QGraphicsEllipseItem>
#include <QColor>

#include <math.h>

#include <iostream>

QEndcapWidget::QEndcapWidget(QWidget *parent) : QWidget(parent)
{
    this->sectorColor = QString("red");
}


void QEndcapWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QRectF bkgRect(0, 0, this->width() - 1, this->height() - 1);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bkgColor(255,255,255);
    QBrush bkgBrush(bkgColor, Qt::SolidPattern);
    painter.setBrush(bkgBrush);
    painter.drawRect(bkgRect);

    int d = std::min(width(), height()) - 10;
    int d2 = d / 2;
    int x0 = width()/2;
    int y0 = height()/2;
    QRect rect0(x0 - d2/2, y0 - d2/2, d2, d2);
    QRect rect1(x0 - d/2, y0 - d/2, d, d);

    painter.drawEllipse(rect1);
    painter.drawEllipse(rect0);

    double alpha0 = 0;
    for (int i = 0; i < SECTOR_NUM; i++)
    {
        double alpha = alpha0 + (i * 2 * M_PI / SECTOR_NUM);
        QPoint p0 = GetRayCircleIntersection(x0, y0, d/2, alpha);
        QPoint p1 = GetRayCircleIntersection(x0, y0, d2/2, alpha);
        painter.drawLine(p0, p1);
    }

    filledSector = 10;
    if (filledSector == -1)
        return;

    int sector = SECTOR_NUM - (filledSector - 1);
    double alpha1 = alpha0 + sector * 360 / SECTOR_NUM;
    QPainterPath path;

    path.moveTo(x0, y0);
    path.arcTo(rect1, alpha1, 360 / SECTOR_NUM);
    path.moveTo(x0, y0);
    path.arcTo(rect0, alpha1, 360 / SECTOR_NUM);
    painter.setPen (Qt :: NoPen);
    painter.fillPath (path, QBrush(QColor(sectorColor)));

    int penW = painter.pen().width();
    painter.setBrush(bkgBrush);
    painter.drawEllipse(x0 - d2/2 + penW, y0 - d2/2 + penW, d2 - 2*penW, d2 - 2*penW);
}


void QEndcapWidget::FillSector()
{

}

QPoint QEndcapWidget::GetRayCircleIntersection(int x0, int y0, int r, double alpha)
{
    int x1 = x0 + round(r*cos(alpha));
    int y1 = y0 + round(r*sin(alpha));
    return QPoint(x1, y1);
}
