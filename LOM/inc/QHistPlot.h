#ifndef QHISTPLOT_H
#define QHISTPLOT_H

#include <QWidget>
#include "inc/LOMHistograms.h"

namespace Ui {
class QHistPlot;
}

class QHistPlot : public QWidget
{
    Q_OBJECT

public:
    explicit QHistPlot(QWidget *parent = 0);
    ~QHistPlot();

    void SetHist(Hist* h);
    void SetEnableFavorite(bool val);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::QHistPlot *ui;
    Hist* h;
public slots:
    void SetFavorite(bool val);
};

#endif // QHISTPLOT_H
