#include "inc/QHistPlot.h"
#include "ui_QHistPlot.h"

QHistPlot::QHistPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QHistPlot) {

    ui->setupUi(this);
    SetEnableFavorite(true);
    h = NULL;
}

QHistPlot::~QHistPlot() {
    delete ui;
}

void QHistPlot::resizeEvent(QResizeEvent *event) {

    QWidget::resizeEvent(event);

    ui->labelTitle->resize(this->width(), 25);
    ui->labelTitle->move(0, 0);

    ui->widgetHist->resize(this->width(), this->height() - 60);
    ui->widgetHist->move(0, 30);

    ui->chBoxFavorite->resize(this->width(), 25);
    ui->chBoxFavorite->move(0, this->height() - 30);

}

void QHistPlot::SetHist(Hist *h) {
    this->h = h;

    // Set favorite.
    //ui->chBoxFavorite->setChecked(h->IsFavorite());

    // Set labels and axis.
    ui->labelTitle->setText(h->GetTitle());
    ui->widgetHist->xAxis->setLabel(h->GetXTitle());
    ui->widgetHist->xAxis->setRange(h->GetX0(), h->GetX1());
    ui->widgetHist->yAxis->setLabel(h->GetYTitle());
    ui->widgetHist->yAxis->setRange(0, 1.0 * h->GetMax());

    if(h == NULL)
        return;
    qDebug() << "ss2";

    // Set plot style;
    QPen pen;
    pen.setColor(QColor("red"));
    ui->widgetHist->addGraph();
    ui->widgetHist->graph(0)->setPen(pen);
    ui->widgetHist->graph(0)->setLineStyle(QCPGraph::lsStepCenter);

    // Assign data.
    ui->widgetHist->graph(0)->setData(h->GetXValues(), h->GetHistDouble());

    ui->widgetHist->replot();

}

void QHistPlot::SetEnableFavorite(bool val) {
    ui->chBoxFavorite->setEnabled(val);
}

void QHistPlot::SetFavorite(bool val) {
    if(h != NULL)
        h->SetFavorite(val);
}

void QHistPlot::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
}
