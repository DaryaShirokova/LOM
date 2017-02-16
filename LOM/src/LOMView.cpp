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
    ymaxBWD = 5.0;
    ymaxFWD = 7.0;
}

LOMView::~LOMView()
{
    delete ui;
}

//******************************************************************************
// SLOTS
//******************************************************************************

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
    unsigned int newValFreq = ui->spinBoxUpdFreq->value();
    model->SetUpdateFreq(newValFreq);
}

void LOMView::StartUpdates()
{
    model->Start();
    UpdatePlots();
}

void LOMView::StopUpdates()
{
    model->Stop();
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
    std::array<double, 64> y_temp = model->GetEventData().GetAmplsFWD()
                                    .GetAmplitudesInSector(fwdSector - 1);
    QVector<double> x(64), y(64);
    for (int i=0; i<64; ++i)
    {
      x[i] = 1.0 * i;
      y[i] =y_temp[i];
    }

    // Set up style.
    ui->amplFWDWidget->addGraph();
    ui->amplFWDWidget->graph(0)->setPen(pen);
    ui->amplFWDWidget->graph(0)->setLineStyle(QCPGraph::lsLine);

    // Assign data.
    ui->amplFWDWidget->graph(0)->setData(x, y);

    // Give titles to axis
    ui->amplFWDWidget->xAxis->setLabel("Time stamps");
    ui->amplFWDWidget->yAxis->setLabel("Amplitude, GeV");

    // Set axes ranges.
    ui->amplFWDWidget->xAxis->setRange(0, 63);
    ui->amplFWDWidget->yAxis->setRange(-0.1, ymaxFWD);

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
    y_temp = model->GetEventData().GetAmplsBWD()
                                    .GetAmplitudesInSector(bwdSector - 1);
    for (int i=0; i<64; ++i)
      y[i] =y_temp[i];

    // Set up style.
    ui->amplBWDWidget->addGraph();
    ui->amplBWDWidget->graph(0)->setPen(pen);
    ui->amplBWDWidget->graph(0)->setLineStyle(QCPGraph::lsLine);

    // Assign data.
    ui->amplBWDWidget->graph(0)->setData(x, y);

    // Give titles to axis
    ui->amplBWDWidget->xAxis->setLabel("Time stamps");
    ui->amplBWDWidget->yAxis->setLabel("Amplitude, GeV");

    // Set axes ranges.
    ui->amplBWDWidget->xAxis->setRange(0, 63);
    ui->amplBWDWidget->yAxis->setRange(-0.1, ymaxBWD);

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
    std::array<int, 64> y_coin = model->GetEventData()
            .GetCoincidenceRegion(fwdSector-1, bwdSector-1, thresholdFE, thresholdBE);

    for (int i=0; i<64; ++i)
    {
      y[i] =y_coin[i];
      std::cout << y[i] << " " << y_coin[i] << " ";
    }
    std::cout <<endl;

    // Set up style.
    ui->coinWidget->addGraph();
    ui->coinWidget->graph(0)->setPen(pen);
    ui->coinWidget->graph(0)->setLineStyle(QCPGraph::lsStepCenter);

    // Assign data.
    ui->coinWidget->graph(0)->setData(x, y);

    // Give titles to axis
    ui->coinWidget->xAxis->setLabel("Time stamps");
    ui->coinWidget->yAxis->setLabel("Coincidence");

    // Set axes ranges.
    ui->coinWidget->xAxis->setRange(0, 63);
    ui->coinWidget->yAxis->setRange(-0.1, 1.2);

    // Replotting.
    ui->coinWidget->replot();

    // Update label.
}
