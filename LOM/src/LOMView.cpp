#include <inc/LOMView.h>
#include <inc/LOMDataProcessor.h>
#include "ui_LOMView.h"

#include <iostream>

LOMView::LOMView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LOMView)
{
    ui->setupUi(this);
    //ui->fwdEndcapWidget->se
    //centralWidget()->layout()->setAlignment(Qt::AlignTop);
    //layout()->setAlignment(widget, layout)
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
}

void LOMView::StopUpdates()
{
    model->Stop();
}
