#include "inc/QHistPoolWidget.h"
#include "ui_QHistPoolWidget.h"

#include <QPainter>
#include <QDebug>
QHistPoolWidget::QHistPoolWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QHistPoolWidget) {
    ui->setupUi(this);

    histPool = NULL;

    for(int i = 0; i < 4; i++) {
        QHistPlot* hp = new QHistPlot(this);
       hp->setObjectName("widget" + QString::number(i));
       connect(hp, SIGNAL(HistChecked()), this, SLOT(CheckFavotite()));
       plotsPool.push_back(hp);
    }
    curPage = 0;
    SetLabel();
    UpdateHists();
}

void QHistPoolWidget::SetLabel() {
    ui->labelPage->setText("Page "+QString::number(curPage) + "/" + QString::number(GetPagesNumber()));
}

QHistPoolWidget::~QHistPoolWidget() {
    delete ui;
}

void QHistPoolWidget::resizeEvent(QResizeEvent *event) {

    QWidget::resizeEvent(event);

    // Hist plots.
    int deltaH = 20 + ui->pbPrevious->height() + ui->labelPage->height();
    int indentY = 10;
    int indentX = 10;
    int xPlotSize = width() / 2 - 2 * indentX;
    int yPlotSize = (height() - deltaH) / 2 - 2*indentY;

    for(int i = 0; i < plotsPool.size(); i++)
        plotsPool.at(i)->resize(xPlotSize, yPlotSize);


    plotsPool.at(0)->move(indentX, indentY);
    plotsPool.at(1)->move(3 * indentX + xPlotSize, indentY);
    plotsPool.at(2)->move(indentX, 2 * indentY + yPlotSize);
    plotsPool.at(3)->move(3 * indentX + xPlotSize, 2 * indentY + yPlotSize);

    for(int i = 0; i < plotsPool.size(); i++)
        plotsPool.at(i)->show();

    // Push buttons prev/next and label.
    ui->pbPrevious->move(width() / 2 - ui->pbPrevious->width() - 5,
                         height() - 5 - ui->pbPrevious->height());
    ui->pbNext->move(width() / 2 + 5, height() - 5 - ui->pbPrevious->height());

    ui->labelPage->move(width() / 2 - ui->labelPage->width()/2,
                        height() - 15 - ui->pbPrevious->height() - ui->labelPage->height());

    // Push buttons Update/Save
    ui->pbUpdate->move(width() - indentX - ui->pbUpdate->width(),
                       2 * indentY + 2* yPlotSize);
    ui->pbSave->move(width() - indentX - ui->pbSave->width(),
                       2 * indentY + 2* yPlotSize + 5 + ui->pbUpdate->height());

    for(int i = 0; i < plotsPool.size(); i++)
        plotsPool.at(i)->raise();
}

void QHistPoolWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

}

void QHistPoolWidget::UpdateHists() {
    for(QHistPlot* hp : plotsPool) {
        hp->setVisible(false);
        hp->repaint();
    }

    if(histPool == NULL)
        return;

    int i = 0;
    int favoriteN = GetFavorite().size();
    for(i = 0; i < activeHist.size(); i++) {
        plotsPool.at(i)->SetHist(histPool->GetHists().value(activeHist.at(i)));
        plotsPool.at(i)->setVisible(true);
        if(favoriteN < 4)
            plotsPool.at(i)->SetEnableFavorite(true);
        else if(!histPool->GetHists().value(activeHist.at(i))->IsFavorite())
            plotsPool.at(i)->SetEnableFavorite(false);
        else plotsPool.at(i)->SetEnableFavorite(true);

    }
}

void QHistPoolWidget::ShowPrevious() {
    if(curPage == 2) {
        activeHist = GetFavorite();
        curPage = 1;
    }
    else {
        if(curPage == 1)
            curPage = GetPagesNumber();
        else curPage--;
        activeHist.clear();
        for(int i = (curPage-2)*4; i < (curPage-1)* 4; i++)
            activeHist.push_back(histPool->GetHists().keys().at(i));
    }
    if(activeHist.size() == 0 && GetPagesNumber() > 1)
        ShowPrevious();
    UpdateHists();
    SetLabel();
}

void QHistPoolWidget::ShowNext() {
    if(curPage == GetPagesNumber()) {
        activeHist = GetFavorite();
        curPage = 1;
    }
    else {
        activeHist.clear();
        for(int i = (curPage-1)*4; i < curPage * 4; i++)
            activeHist.push_back(histPool->GetHists().keys().at(i));
        curPage++;
    }
    if(activeHist.size() == 0 && GetPagesNumber() > 1)
        ShowNext();
    UpdateHists();
    SetLabel();
}

int QHistPoolWidget::GetPagesNumber() {
    if(histPool == NULL)
        return 0;
    if(histPool->GetHists().size() <= 4)
        return 1;
    return std::ceil(1.0 * histPool->GetHists().size() / 4.0) + 1;
}

QStringList QHistPoolWidget::GetFavorite(){
    QStringList list;
    QMap<QString, Hist*> map = histPool->GetHists();
    QMap<QString, Hist*>::iterator i;

    for (i = map.begin(); i != map.end(); ++i)
        if(list.size() < 4 && i.value()->IsFavorite())
            list.push_back(i.key());


    return list;
}

void QHistPoolWidget::SetModel(LOMHistograms *histPool) {
    this->histPool = histPool;
    curPage = 1;
    SetLabel();
    if(histPool == NULL)
        return;

    activeHist.clear();
    activeHist = GetFavorite();
    if(activeHist.size() == 0)
        ShowNext();
}

void QHistPoolWidget::CheckFavotite() {
    if(curPage == 1)
        activeHist = GetFavorite();
    UpdateHists();
}
