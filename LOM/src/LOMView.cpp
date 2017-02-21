#include <inc/LOMView.h>
#include <inc/LOMDataProcessor.h>
#include "ui_LOMView.h"

#include <iostream>
#include <QVector>
#include <array>
#include <algorithm>

LOMView::LOMView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LOMView)
{
    ui->setupUi(this);

    ui->checkBoxHitSector->toggle();
    ui->checkBoxSaveLog->toggle();
    ChangePlottersMode();

    QPalette palette = ui->labelLuminosity->palette();
    palette.setColor(ui->labelLuminosity->foregroundRole(), Qt::red);
    ui->labelLuminosity->setPalette(palette);

    // Give titles to axis
    ui->luminosityWidget->xAxis->setLabel("t, s");
    ui->luminosityWidget->yAxis->setLabel("L, 1/s/cm2");
    ui->amplFWDWidget->xAxis->setLabel("Time stamps");
    ui->amplFWDWidget->yAxis->setLabel("Amplitude, GeV");
    ui->amplBWDWidget->xAxis->setLabel("Time stamps");
    ui->amplBWDWidget->yAxis->setLabel("Amplitude, GeV");
    ui->coinWidget->xAxis->setLabel("Time stamps");
    ui->coinWidget->yAxis->setLabel("Coincidence");

    // Set axes ranges.
    ChangePlottersSettings();

    ui->amplFWDWidget->replot();
    ui->amplBWDWidget->replot();
    ui->coinWidget->replot();


    // Set update timer.
    //UpdateSettings();
    plotsUpdateTimer = new QTimer(this);
    connect(plotsUpdateTimer, SIGNAL(timeout()), SLOT(UpdateAll()));
}

LOMView::~LOMView()
{
    delete plotsUpdateTimer;
    delete ui;
}

//******************************************************************************
// SLOTS
//******************************************************************************
void LOMView::ChangePlottersSettings()
{
    this->x0 = ui->xMinSpinBox->value();
    this->x1 = ui->xMaxSpinBox->value();
    this->ymaxFWD = ui->yFWDMaxSpinBox->value();
    this->ymaxBWD = ui->yBWDMaxSpinBox->value();
    ui->amplFWDWidget->xAxis->setRange(x0, x1);
    ui->amplFWDWidget->yAxis->setRange(-0.1, ymaxFWD);
    ui->amplBWDWidget->xAxis->setRange(x0, x1);
    ui->amplBWDWidget->yAxis->setRange(-0.1, ymaxBWD);
    ui->coinWidget->xAxis->setRange(x0, x1);
    ui->coinWidget->yAxis->setRange(-0.1, 1.2);
}

void LOMView::UpdateAll()
{
    UpdatePlots();
    UpdateEndcapsWiggets();
}

void LOMView::UpdateThresholds()
{
    unsigned int newValFE = ui->spinBoxAmplFWD->value();
    unsigned int newValBE = ui->spinBoxAmplBWD->value();
    unsigned int newValCoin = ui->spinBoxCoinDur->value();
    unsigned int newValBkg = ui->spinBoxBkg->value();
    model->GetInitParameters().Init(newValFE, newValBE, newValCoin, newValBkg);

    std::cout << "ThresholdBE: " << model->GetInitParameters().GetThresholdBE() << std::endl;
    std::cout << "Coin: " << model->GetInitParameters().GetCoincidenceDurationThreshold() << std::endl;
    std::cout << "Bkg: " << model->GetInitParameters().GetBackgroundThreshold() << std::endl;
}

void LOMView::UpdateSettings()
{
    this->redrawFreq = int(1000 * ui->spinBoxRedrawFreq->value());
    model->SetUpdateFreq(int(1000 * ui->spinBoxUpdFreq->value()));
}

void LOMView::StartUpdates()
{
    UpdateSettings();
    model->Start();
    UpdatePlots();
    UpdateEndcapsWiggets();
    plotsUpdateTimer->start(redrawFreq);
    ui->pushButtonSetSettings->setEnabled(false);
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);
}

void LOMView::StopUpdates()
{
    model->Stop();
    plotsUpdateTimer->stop();
    ui->pushButtonSetSettings->setEnabled(true);
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
}

void LOMView::ChangePlottersMode()
{
    if(ui->checkBoxHitSector->isChecked())
    {
        ui->fwdSectorCB->setEnabled(false);
        ui->bwdSectorCB->setEnabled(false);
    }
    else
    {
        ui->fwdSectorCB->setEnabled(true);
        ui->bwdSectorCB->setEnabled(true);
    }
}

void LOMView::UpdatePlots()
{
    std::cout <<"hey " << std::endl;
    unsigned int fwdSector;
    unsigned int bwdSector;

    // Choose mode of data plotters (fixed sectors / hit sectors)
    if(ui->checkBoxHitSector->isChecked())
    {
        fwdSector = model->GetEventData().GetAmplsFWD().GetHitSector() + 1;
        bwdSector = model->GetEventData().GetAmplsBWD().GetHitSector() + 1;
    }
    else
    {
        fwdSector = ui->fwdSectorCB->currentText().toInt();
        bwdSector = ui->bwdSectorCB->currentText().toInt();
    }

    std::cout << "fwd sector: " << fwdSector << " bwd sector: " << bwdSector << std::endl;

    //**************************************************************************
    // Draw fwd plot.

    // Set up pen.
    QPen pen;
    pen.setColor(QColor("blue"));

    // Prepare data.
    QVector<double> y = model->GetEventData().GetAmplsFWD()
                                    .GetAmplitudesInSector(fwdSector - 1);
    QVector<double> x(64);
    for (int i=0; i<64; ++i)
      x[i] = 1.0 * i;

    // Set up style.
    ui->amplFWDWidget->addGraph();
    ui->amplFWDWidget->graph(0)->setPen(pen);
    ui->amplFWDWidget->graph(0)->setLineStyle(QCPGraph::lsLine);

    // Assign data.
    ui->amplFWDWidget->graph(0)->setData(x, y);

    // Add threshold.
    double thresholdFE = model->GetInitParameters().GetThresholdFE();
    ui->amplFWDWidget->addGraph();
    QPen penTh;
    penTh.setColor(QColor("red"));
    penTh.setStyle(Qt::PenStyle::DashLine);
    ui->amplFWDWidget->graph(1)->setPen(penTh);
    QVector<double> yTh(64);
    for (int i=0; i<64; ++i)
        yTh[i] = thresholdFE;
    ui->amplFWDWidget->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->amplFWDWidget->graph(1)->setData(x, yTh);


    // Replotting.
    ui->amplFWDWidget->replot();

    // Update label.
    ui->fwdWidgetLabel->setText("FWD: sector " + QString::number(fwdSector));

    //**************************************************************************
    // Draw bwd plot.

    // Set up pen.
    pen.setColor(QColor("blue"));

    // Prepare data.
    y = model->GetEventData().GetAmplsBWD()
                                    .GetAmplitudesInSector(bwdSector - 1);
    // Set up style.
    ui->amplBWDWidget->addGraph();
    ui->amplBWDWidget->graph(0)->setPen(pen);
    ui->amplBWDWidget->graph(0)->setLineStyle(QCPGraph::lsLine);

    // Assign data.
    ui->amplBWDWidget->graph(0)->setData(x, y);

    // Add threshold.
    double thresholdBE = model->GetInitParameters().GetThresholdBE();
    ui->amplBWDWidget->addGraph();
    ui->amplBWDWidget->graph(1)->setPen(penTh);
    for (int i=0; i<64; ++i)
        yTh[i] = thresholdBE;
    ui->amplBWDWidget->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->amplBWDWidget->graph(1)->setData(x, yTh);

    // Replotting.
    ui->amplBWDWidget->replot();

    // Update label.
    ui->bwdWidgetLabel->setText("BWD: sector " + QString::number(bwdSector));

    //**************************************************************************
    // Draw coincidence plot.

    // Set up pen.
    pen.setColor(QColor("red"));

    // Prepare data.
    QVector<int> y_coin = model->GetEventData()
            .GetCoincidenceRegion(fwdSector-1, bwdSector-1, thresholdFE, thresholdBE);

    for (int i=0; i<64; ++i)
        y[i] =y_coin[i];

    // Set up style.
    ui->coinWidget->addGraph();
    ui->coinWidget->graph(0)->setPen(pen);
    ui->coinWidget->graph(0)->setLineStyle(QCPGraph::lsStepCenter);

    // Assign data.
    ui->coinWidget->graph(0)->setData(x, y);

    // Replotting.
    ui->coinWidget->replot();

    // Update label.
    if(model->GetEventData().haveCoincidenceRegion(fwdSector-1, bwdSector-1, thresholdFE, thresholdBE))
    {
        ui->coinWidgetLabel->setText("Coincidence region: " +
            QString::number(model->GetEventData().GetCoincidenceRegionLeftBoundary
                            (fwdSector-1, bwdSector-1, thresholdFE, thresholdBE))
                            + "-" +
            QString::number(model->GetEventData().GetCoincidenceRegionRightBoundary
                           (fwdSector-1, bwdSector-1, thresholdFE, thresholdBE)));

    }
    else
        ui->coinWidgetLabel->setText("Coincidence region: none ");

}

void LOMView::UpdateEndcapsWiggets()
{
    ui->fwdEndcap->SetAmplitudes(model->GetEventData()
                                 .GetAmplsFWD().GetMaxAmplitudes());
    ui->fwdEndcap->repaint();

    ui->bwdEndcap->SetAmplitudes(model->GetEventData()
                                 .GetAmplsBWD().GetMaxAmplitudes());
    ui->bwdEndcap->repaint();
}
