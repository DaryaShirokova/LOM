#ifndef QHISTPOOLWIDGET_H
#define QHISTPOOLWIDGET_H

#include <QWidget>
#include <QVector>

#include "inc/QHistPlot.h"

namespace Ui {
class QHistPoolWidget;
}

class QHistPoolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QHistPoolWidget(QWidget *parent = 0);
    ~QHistPoolWidget();
    void SetModel(LOMHistograms* histPool);
protected:
    //! Paint event.
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *) override;
private:
    Ui::QHistPoolWidget *ui;
    QVector<QHistPlot*> plotsPool;
    LOMHistograms* histPool;
    QStringList activeHist;
    QStringList GetFavorite();
    int GetPagesNumber();
    int curPage;
    void SetLabel();

public slots:
    void UpdateHists();
    void ShowPrevious();
    void ShowNext();
    void CheckFavotite();
};

#endif // QHISTPOOLWIDGET_H
