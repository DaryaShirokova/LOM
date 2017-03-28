#ifndef QHISTPLOT_H
#define QHISTPLOT_H

#include <QWidget>

#include "inc/LOMHistograms.h"

namespace Ui {
class QHistPlot;
}

//! Histogram plotter.
class QHistPlot : public QWidget {
    Q_OBJECT

public:
    /*!
     * \brief QHistPlot Constructor.
     * \param parent    parent.
     */
    explicit QHistPlot(QWidget *parent = 0);
    ~QHistPlot();

    /*!
     * \brief SetHist   set target histogram.
     * \param h         histogram.
     */
    void SetHist(Hist* h);

    /*!
     * \brief SetEnableFavorite allow configuring histogram as favorite.
     * \param val   enable/disable.
     */
    void SetEnableFavorite(bool val);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::QHistPlot *ui; /*!< GUI. */
    Hist* h;    /*!< Histogram. */

public slots:
    /*!
     * \brief SetFavorite   Mark histogram as favorite.
     * \param val           true/false.
     */
    void SetFavorite(bool val);

signals:
    /*!
     * \brief HistChecked   Favorite status is changed.
     */
    void HistChecked();
};

#endif // QHISTPLOT_H
