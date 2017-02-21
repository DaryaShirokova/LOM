#ifndef ENDCAPWIDGET_H
#define ENDCAPWIDGET_H

#define SECTOR_NUM 16//12

#include <QWidget>
#include <QPoint>
#include <QString>
#include <QVector>

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
    double maxAmpl;
    double minAmpl;
    QVector<double> amplitudes;
    QPoint GetRayCircleIntersection(int x0, int y0, int r, double alpha);
};

#endif // ENDCAPWIDGET_H
