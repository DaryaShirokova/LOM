#include "inc/QColorBar.h"

#include <QPainter>

QColorBar::QColorBar(QWidget *parent) : QWidget(parent)
{

}

QColor QColorBar::GetColor(double val)
{
    if(val >= 1.)
        return QColor(255, 255, 255);
    else if(val <= 0)
        return QColor(0, 0, 0);
    else if (val <= 1/3.)
        return QColor(int(std::round(255 * val * 3)), 0, 0);
    else if (val <= 2/3.)
        return QColor(255, int(std::round(255 * (val - 1/3.) * 3.)), 0);
    else return QColor(255, 255, int(std::round(255 * (val - 2/3.) * 3.)));
}

void QColorBar::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setPen (Qt :: NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    int xwidth = this->width();
    int ywidth = this->height();

    for (int i = 0; i < shadesNumber; i++)
    {
        double y0 = i * ywidth / shadesNumber;
        double y1 = (i + 1) * ywidth / shadesNumber;
        QRect rect(0, y0, xwidth, y1);

        QBrush brush(GetColor(i * 1. / shadesNumber), Qt::SolidPattern);
        painter.setBrush(brush);
        painter.drawRect(rect);
    }




}

