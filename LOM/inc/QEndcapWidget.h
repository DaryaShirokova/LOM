#ifndef ENDCAPWIDGET_H
#define ENDCAPWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QString>
#include <QVector>
#include "inc/constants.h"

class QEndcapWidget : public QWidget
{
    Q_OBJECT


public:
    explicit QEndcapWidget(QWidget *parent = 0);
    ~QEndcapWidget() {}

    void SetAmplitudes(QVector<double> amplitudes) { this->amplitudes = amplitudes; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<double> amplitudes;
    QPoint GetRayCircleIntersection(int x0, int y0, int r, double alpha);
};

#endif // ENDCAPWIDGET_H
