#ifndef ENDCAPWIDGET_H
#define ENDCAPWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QVector>
#include "inc/Constants.h"

//! Widget for drawing endcap parts of the Belle II calorimeter.
class QEndcapWidget : public QWidget
{
    Q_OBJECT


public:
    //! Constructor.
    explicit QEndcapWidget(QWidget *parent = 0);

    //! Destructor.
    ~QEndcapWidget() {}

    /*!
     * \brief SetAmplitudes setters.
     * \param amplitudes    max value of amplitude in each sector.
     */
    void SetAmplitudes(QVector<double> amplitudes) { this->amplitudes = amplitudes; }

protected:
    //! Paint event.
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<double> amplitudes; /*!< Max value of amplitude in each sector.*/

    /*!
     * \brief GetRayCircleIntersection Get intersection point of ray from the center of circle and circle.
     * \param x0    center of cicle (x coord).
     * \param y0    center of cicle (y coord).
     * \param r     radius of the circle.
     * \param alpha the direction of the ray.
     * \return  the intersection point.
     */
    QPoint GetRayCircleIntersection(int x0, int y0, int r, double alpha);
};

#endif // ENDCAPWIDGET_H
