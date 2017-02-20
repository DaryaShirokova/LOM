#ifndef ENDCAPWIDGET_H
#define ENDCAPWIDGET_H

#define SECTOR_NUM 16//12

#include <QWidget>
#include <QPoint>
#include <QString>

#include <array>

class QEndcapWidget : public QWidget
{
    Q_OBJECT


public:
    explicit QEndcapWidget(QWidget *parent = 0);
    ~QEndcapWidget() {}

    void SetAmplitudes(std::array<double, 16> amplitudes) { this->amplitudes = amplitudes; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    double maxAmpl;
    double minAmpl;
    std::array<double, 16> amplitudes;
    QPoint GetRayCircleIntersection(int x0, int y0, int r, double alpha);
};

#endif // ENDCAPWIDGET_H
