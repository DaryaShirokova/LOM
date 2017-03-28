#include "inc/QHistPoolWidget.h"
#include "ui_QHistPoolWidget.h"

#include <QPainter>
#include <QKeyEvent>

QHistPoolWidget::QHistPoolWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QHistPoolWidget) {
    ui->setupUi(this);

    ui->pbSave->setToolTip("Save histograms to files.");
    ui->pbUpdate->setToolTip("Update histograms.");
    ui->pbNext->setToolTip("Show next page.");
    ui->pbPrevious->setToolTip("Show previous page.");

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

    setFocus();
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
    UpdateHists();
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
        for(int i = (curPage-2)*4; i<(curPage-1)*4 && i<GetSortedKeys().size(); i++)
            activeHist.push_back(GetSortedKeys().at(i));
    }
    if(activeHist.size() == 0 && GetPagesNumber() > 1)
        ShowPrevious();
    UpdateHists();
    SetLabel();
}

void QHistPoolWidget::ShowNext() {
    activeHist.clear();
    if(curPage == GetPagesNumber()) {
        activeHist = GetFavorite();
        curPage = 1;
    }
    else {
        activeHist.clear();
        for(int i=(curPage-1)*4; i < curPage*4 && i<GetSortedKeys().size(); i++)
            activeHist.push_back(GetSortedKeys().at(i));
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
    QStringList keys = GetSortedKeys();
    QMap<QString, Hist*> map = histPool->GetHists();

    for (QString key : keys) {
        if(map.value(key)->IsFavorite())
            list.push_back(key);
        if(list.size() == 4)
            break;
    }

    return list;
}

void QHistPoolWidget::SetModel(LOMHistograms *histPool) {
    this->histPool = histPool;
    curPage = 1;
    SetLabel();
    if(histPool == NULL)
        return;

    if(GetFavorite().size() != 0) {
        curPage = 1;
        activeHist = GetFavorite();
        UpdateHists();
    }
    else ShowNext();

}

void QHistPoolWidget::CheckFavotite() {
    if(curPage == 1)
        activeHist = GetFavorite();
    UpdateHists();
    setFocus();
}

void QHistPoolWidget::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_A)
        ShowPrevious();
    if(event->key() == Qt::Key_D)
        ShowNext();
}

bool mycomparator (QString s1, QString s2) {
    int n = std::min(s1.length(), s2.length());
    for(int i = 0; i < n; i++) {
        QChar c1 = s1.at(i);
        QChar c2 = s2.at(i);
        if(c1.isDigit() && c2.isDigit()) {
            int j, k;
            for(j = i; j < s1.length(); j++)
                if(!s1.at(j).isDigit())
                    break;
            int num1 = s1.mid(i, j-i+1).toInt();

            for(k = i; k < s2.length(); k++)
                if(!s2.at(k).isDigit())
                    break;
            int num2 = s2.mid(i, k-i+1).toInt();

            if(num1 != num2)
                return num1 < num2;

        } else if (c1 != c2)
            return c1 < c2;
    }
    return false;
}

QStringList QHistPoolWidget::GetSortedKeys() {
    QStringList keys = histPool->GetHists().keys();
    std::sort(keys.begin(), keys.end(), mycomparator);
    return keys;
}

void QHistPoolWidget::Save() {
    emit SaveHist();
}

void QHistPoolWidget::Update() {
    emit UpdateRequired();
}
