#include "inc/LOMView.h"
#include "inc/LOMDataProcessor.h"
#include "inc/Logger.h"
#include "inc/QNetworkSettings.h"
#include "ui_LOMView.h"

#include <QVector>
#include <QFile>
#include <algorithm>
#include <QSettings>

LOMView::LOMView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LOMView) {
    ui->setupUi(this);

    widgetHists = new QHistPoolWidget(ui->tab_2);
    ui->tab_2->layout()->addWidget(widgetHists);

    advancedMode = false;
    lastCountersUpdate = 0;
    // Setup logging.
    SetLogType(ui->logTypeCheckBox->currentText());
    SetLogDepth(ui->logDepthspinBox->value());

    // Toggle buttons.
    ui->checkBoxHitSector->toggle();
    ui->checkBoxSaveLog->toggle();
    ChangePlottersMode();

    // Set luminosity/thresholds/connection palette labels to red.
    QPalette palette;
    palette.setColor(QWidget::foregroundRole(), Qt::red);
    //ui->labelLuminosity->setPalette(palette);
    ui->thresholdStatusLabel->setPalette(palette);
    ui->connectionStatusLabel->setPalette(palette);

    // Give titles to axis
    ui->widgetLuminosity->xAxis->setLabel("t, s");
    ui->widgetLuminosity->yAxis->setLabel("L, 1/s/cm2");
    ui->amplFWDWidget->xAxis->setLabel("Time stamps");
    ui->amplFWDWidget->yAxis->setLabel("Amplitude, GeV");
    ui->amplBWDWidget->xAxis->setLabel("Time stamps");
    ui->amplBWDWidget->yAxis->setLabel("Amplitude, GeV");
    ui->coinWidget->xAxis->setLabel("Time stamps");
    ui->coinWidget->yAxis->setLabel("Coincidence");

    // Set axes ranges.
    ChangePlottersSettings();

    // Set up menu.
   // ui->menuFile->addAction("&Open configuration file", this, SLOT(LoadConfigurations()));
    ui->menuFile->addAction("&Edit configuration", this, SLOT(EditConfigurations()));
 //   ui->menuFile->addAction("&Save configuration", this, SLOT(OnSaveConfiguration()));
    ui->menuFile->addSeparator();
    ui->menuFile->addAction("&Reconnect", this, SLOT(Reconnect()));
    ui->menuFile->addAction("&Network settings", this, SLOT(OpenNetworkSettings()));
    ui->menuFile->addSeparator();
    ui->menuFile->addAction("&Exit", this, SLOT(OnExit()));


}


void LOMView::SetModel(LOMDataProcessor *model) {
    this->model = model;
    connect(model, SIGNAL(AmplitudesUpdated()), SLOT(UpdateAll()));
    connect(model, SIGNAL(CountersUpdated()), SLOT(UpdateCounters()));

    widgetHists->SetModel(model->GetHistograms());
    connect(widgetHists, SIGNAL(UpdateRequired()), model, SLOT(UpdateHistograms()));
    connect(model, SIGNAL(HistsUpdated()), widgetHists, SLOT(UpdateHists()));
    connect(model, SIGNAL(TimingUpdated()), this, SLOT(UpdateTiming()));
    connect(widgetHists, SIGNAL(SaveHist()), model, SLOT(HistsToFile()));


    connect(&(model->GetInitParameters()),
            SIGNAL(StatusChanged(bool)),this, SLOT(SetThresholdStatus(bool)));
    connect(&(model->GetInitParameters()),
            SIGNAL(ParamsChanged()),this, SLOT(InitThresholds()));

}

LOMView::~LOMView() {
    delete ui;
}


void LOMView::handleMessage(QString message)
{
    if(message.isEmpty())
        return;
    QString text = ui->logBrowser->toPlainText();
    int index = 0;
    for(int i = 0; i < logDepth - 1; i++)
    {
        index = text.indexOf("\n", index+1);
        if(index == -1)
            break;
    }
    if (index != -1) text = text.left(index);

    text = message + text;
    text = text.replace('\n',"<br />");
    text.replace("ERROR", "<font color='red'><b>ERROR</b></font>");
    text.replace("INFO", "<font color='green'><b>INFO</b></font>");
    text.replace("DEBUG", "<font color='gray'><b>DEBUG</b></font>");

    ui->logBrowser->setText(text);
}

//******************************************************************************
// SLOTS
//******************************************************************************
void LOMView::SetThresholdStatus(bool val) {
    ui->thresholdStatusLabel->setVisible(!val);
}

void LOMView::InitThresholds() {
    ui->sbBufferSize->setValue(model->GetInitParameters().GetBufSize());
    ui->spinBoxAmplFWD->setValue(model->GetInitParameters().GetThresholdFE());
    ui->spinBoxAmplBWD->setValue(model->GetInitParameters().GetThresholdBE());
    ui->spinBoxCoinDur->setValue(model->GetInitParameters().GetCoincidenceDurationThreshold());
    ui->spinBoxBkg->setValue(model->GetInitParameters().GetHitThreshold());
}

void LOMView::UpdateTiming() {
    ui->sbUpdateAmplsFreq->setValue(model->GetUpdateAmplsFreq());
    ui->sbUpdCountersFreq->setValue(model->GetUpdateCountersFreq());
    ui->sbUpdateHistsFreq->setValue(model->GetUpdateHistsFreq());
}

void LOMView::ChangePlottersSettings() {
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
    ui->amplFWDWidget->replot();
    ui->amplBWDWidget->replot();
    ui->coinWidget->replot();
}

void LOMView::UpdateCounters() {

    if(time.restart() < 900)
        return;
    ui->leBhabhaEvents->setText(QString::number(model->GetCounters().GetNBhabhaTotal()));
    ui->leBackgroundEvents->setText(QString::number(model->GetCounters().GetNBkgTotal()));
    ui->leDeadTime->setText(QString::number(model->GetCounters().GetDeadTimeMSec()) + " us");
    ui->leDT->setText(QString::number(model->GetCounters().GetDeltaTMSec()) + " us");
    ui->leTotalDeadTime->setText(QString::number(model->GetCounters().GetTotalDeadTimeMSec()) + " us");
    ui->leVetoTime->setText(QString::number(model->GetCounters().GetVetoTimeMSec()) + " us");
}

void LOMView::UpdateAll()
{
    UpdatePlots();
    UpdateEndcapsWiggets();
}

void LOMView::UpdateThresholds() {
    double newValFE = ui->spinBoxAmplFWD->value();
    double newValBE = ui->spinBoxAmplBWD->value();
    int newValCoin = ui->spinBoxCoinDur->value();
    int newValBkg = ui->spinBoxBkg->value();
    int newBufSize = ui->sbBufferSize->value();
    model->SetInitParameters(newValFE, newValBE, newValCoin, newValBkg, newBufSize);
}

void LOMView::UpdateSettings() {
    model->SetFrequencies(ui->sbUpdCountersFreq->value(),
                          ui->sbUpdateAmplsFreq->value(),
                          ui->sbUpdateHistsFreq->value());
}

void LOMView::StartUpdates() {
    UpdateSettings();
    model->Start();
    time.start();

    ui->pushButtonSetThresholds->setEnabled(false);
    ui->pushButtonSetSettings->setEnabled(false);
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonGetThresholds->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);
    ui->pushButtonGetThresholds->setEnabled(false);
}

void LOMView::StopUpdates() {
    model->Stop();
    ui->pushButtonSetThresholds->setEnabled(true);
    ui->pushButtonGetThresholds->setEnabled(true);
    ui->pushButtonSetSettings->setEnabled(true);
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonGetThresholds->setEnabled(true);
}

void LOMView::ChangePlottersMode() {
    if(ui->checkBoxHitSector->isChecked()) {
        ui->fwdSectorCB->setEnabled(false);
        ui->bwdSectorCB->setEnabled(false);
    }
    else {
        ui->fwdSectorCB->setEnabled(true);
        ui->bwdSectorCB->setEnabled(true);
    }
}

void LOMView::SetLogType(QString str)
{
    logtype = Logger::stringToEnum(str);
    Logger::SetLogLevel(logtype);

}

void LOMView::SetLogDepth(int depth)
{
    logDepth = depth;
}

void LOMView::SetLogToFile(bool val){
    Logger::SetWriteToFile(val);
}

void LOMView::UpdatePlots()
{
    unsigned int fwdSector;
    unsigned int bwdSector;

    // Choose mode of data plotters (fixed sectors / hit sectors)
    if(ui->checkBoxHitSector->isChecked()) {
        fwdSector = model->GetAmplitudes().GetAmplsFWD().GetHitSector() + 1;
        bwdSector = model->GetAmplitudes().GetAmplsBWD().GetHitSector() + 1;
    }
    else {
        fwdSector = ui->fwdSectorCB->currentText().toInt();
        bwdSector = ui->bwdSectorCB->currentText().toInt();
    }

    //**************************************************************************
    // Draw fwd plot.

    // Set up pen.
    QPen pen;
    pen.setColor(QColor("blue"));

    // Prepare data.
    QVector<double> y = model->GetAmplitudes().GetAmplsFWD()
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
    y = model->GetAmplitudes().GetAmplsBWD()
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
    QVector<int> y_coin = model->GetAmplitudes()
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
    if(model->GetAmplitudes().haveCoincidenceRegion(fwdSector-1, bwdSector-1,
                                                   thresholdFE, thresholdBE)) {
        ui->coinWidgetLabel->setText("Coincidence region: " +
            QString::number(model->GetAmplitudes().GetCoincidenceRegionLeftBoundary
                            (fwdSector-1, bwdSector-1, thresholdFE, thresholdBE))
                            + "-" +
            QString::number(model->GetAmplitudes().GetCoincidenceRegionRightBoundary
                           (fwdSector-1, bwdSector-1, thresholdFE, thresholdBE)));

    }
    else
        ui->coinWidgetLabel->setText("Coincidence region: none ");

}

void LOMView::UpdateEndcapsWiggets()
{
    ui->fwdEndcap->SetAmplitudes(model->GetAmplitudes()
                                 .GetAmplsFWD().GetMaxAmplitudes());
    ui->fwdEndcap->repaint();

    ui->bwdEndcap->SetAmplitudes(model->GetAmplitudes()
                                 .GetAmplsBWD().GetMaxAmplitudes());
    ui->bwdEndcap->repaint();
}


void LOMView::Connected()
{
    QPalette palette;
    palette.setColor(QWidget::foregroundRole(), Qt::black);
    ui->connectionStatusLabel->setPalette(palette);
    ui->connectionStatusLabel->setText("connected.");

    ui->pushButtonSetThresholds->setEnabled(true);
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
}

void LOMView::Disconnected()
{
    QPalette palette;
    palette.setColor(QWidget::foregroundRole(), Qt::red);
    ui->connectionStatusLabel->setPalette(palette);
    ui->connectionStatusLabel->setText("disconnected.");

    if(model->IsRunning())
        StopUpdates();
    ui->pushButtonSetThresholds->setEnabled(false);
    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonStop->setEnabled(false);
}
void LOMView::LoadConfigurations()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Save File"),
                               DEFAULT_CONF,
                               tr("Config (*.ini)"));
    if(!filename.isNull())
        Load(filename);
}

void LOMView::EditConfigurations()
{
    MenuConfig* configWidget = new MenuConfig(this);
    configWidget->SetDataDir(model->GetDataDir());
    configWidget->SetLogDir(Logger::GetPath());
    configWidget->SetAdvanced(advancedMode);
    configWidget->SetRootFileSize(model->GetTreeSize());
    configWidget->SetWriteFile(model->GetWriteTree());
    configWidget->SetWriteHist(model->GetWriteHist());
    configWidget->SetHistRecordFreq(model->GetWriteHistFreq());
    configWidget->SetHistDir(model->GetHistDir());

    connect(configWidget, SIGNAL(Apply(MenuConfig*)), this,
            SLOT(OnApplyCongiguration(MenuConfig*)));
    configWidget->show();
}

void LOMView::Reconnect() {
    model->GetDataUpdater()->Connect();
}

void LOMView::OpenNetworkSettings()
{
    if(!advancedMode)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Permission denied.");
        msgBox.setIcon(QMessageBox::Critical);
         msgBox.setText("Network settings are enable only in advanced mode. If"
                        " you need to change network settings, please set advanced"
                        " mode in Edit configurations menu.");
         msgBox.setStandardButtons(QMessageBox::Ok);
         msgBox.setDefaultButton(QMessageBox::Ok);
         msgBox.exec();
         return;
    }
    QMap<QString, int> regMap = model->GetDataUpdater()->GetRegMap();
    QMap<QString, int> memMap = model->GetDataUpdater()->GetMemMap();
    QNetworkSettings* networkSettings = new QNetworkSettings(this);
    networkSettings->GenerateView(model->GetDataUpdater()->GetRegMap(),
                                  model->GetDataUpdater()->GetMemMap(),
                                  model->GetDataUpdater()->GetIP(),
                                  model->GetDataUpdater()->GetPort());
    networkSettings->show();

}

void LOMView::OnApplyCongiguration(MenuConfig *config)
{
    Logger::SetPath(config->GetLogDir());
    model->SetDataDir(config->GetDataDir());
    model->SetWriteTree(config->IfWriteFile());
    model->SetTreeSize(config->GetRootFileSize());
    model->SetWriteHist(config->IfWriteHist());
    model->SetWriteHistFreq(config->GetHistRecordFreq());
    model->SetHistDir(config->GetHistDir());
    this->advancedMode = config->IsAdvanced();
    ui->sbBufferSize->setEnabled(advancedMode);
}

void LOMView::OnSaveConfiguration() {
   QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                               DEFAULT_CONF,
                               tr("Config (*.ini)"));
    if(!filename.isNull())
        Save(filename);
}

void LOMView::Save(QString filename) {
    QSettings settings(filename, QSettings::IniFormat );

    settings.beginGroup( "GLOBAL" );
    settings.setValue("write_log", ui->checkBoxSaveLog->isChecked());
    settings.setValue("log_level", ui->logTypeCheckBox->currentText());
    settings.setValue("log_dir", Logger::GetPath());
    settings.setValue("log_depth", ui->logDepthspinBox->value());
    settings.endGroup();

    settings.beginGroup( "GUI" );
    settings.setValue("x0", ui->xMinSpinBox->value());
    settings.setValue("x1", ui->xMaxSpinBox->value());
    settings.setValue("y_fwd", ui->yFWDMaxSpinBox->value());
    settings.setValue("y_bwd", ui->yBWDMaxSpinBox->value());
    settings.setValue("fwd", ui->fwdSectorCB->currentText().toInt());
    settings.setValue("bwd", ui->bwdSectorCB->currentText().toInt());
    settings.setValue("is_hit", ui->checkBoxHitSector->isChecked());
    settings.endGroup();

    model->Save(&settings);
    settings.sync();
}

void LOMView::Load(QString filename) {
    QSettings settings(filename, QSettings::IniFormat );
    settings.beginGroup( "GLOBAL" );
    ui->checkBoxSaveLog->setChecked(settings.value("write_log",
                                    ui->checkBoxSaveLog->isChecked()).toBool());
    ui->logTypeCheckBox->setCurrentText(settings.value("log_level",
                                        ui->logTypeCheckBox->currentText()).toString());
    Logger::SetPath(settings.value("log_dir", Logger::GetPath()).toString());
    ui->logDepthspinBox->setValue(settings.value("log_depth",
                                  ui->logDepthspinBox->value()).toInt());
    settings.endGroup();

    settings.beginGroup("GUI");
    ui->xMinSpinBox->setValue(settings.value("x0", ui->xMinSpinBox->value()).toInt());
    ui->xMaxSpinBox->setValue(settings.value("x1", ui->xMaxSpinBox->value()).toInt());
    ui->yFWDMaxSpinBox->setValue(settings.value("y_fwd", ui->yFWDMaxSpinBox->value()).toDouble());
    ui->yBWDMaxSpinBox->setValue(settings.value("y_bwd", ui->yBWDMaxSpinBox->value()).toDouble());
    ui->fwdSectorCB->setCurrentText(settings.value("fwd", ui->fwdSectorCB->currentText()).toString());
    ui->bwdSectorCB->setCurrentText(settings.value("bwd", ui->bwdSectorCB->currentText()).toString());
    ui->checkBoxHitSector->setChecked(settings.value("is_hit", ui->checkBoxHitSector->isChecked()).toBool());
    settings.endGroup();
    model->Load(&settings);

    if(settings.status() == QSettings::AccessError)
        Logger::Log(Logger::LogLevel::ERROR,
                    "Access error occured while loading configurations: " + filename);
    if(settings.status() == QSettings::FormatError)
        Logger::Log(Logger::LogLevel::ERROR,
                    "Wrong format of the configuration file: " + filename);
    ChangePlottersSettings();
    ChangePlottersMode();
    SetLogToFile(ui->checkBoxSaveLog->isChecked());
    SetLogDepth(ui->logDepthspinBox->value());
    SetLogType(ui->logTypeCheckBox->currentText());
    widgetHists->SetModel(model->GetHistograms());
    Logger::Log(Logger::LogLevel::DEBUG, "App configurations are loaded from " + filename);

}



void LOMView::GetLOMInitParams() {
    model->LoadInitParameters();
}

void LOMView::LoadLOMInitParams()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Save File"),
                               DEFAULT_PARAM,
                               tr("Config (*.param)"));
    if(!filename.isNull())
        model->GetInitParameters().Init(filename);

}

void LOMView::SaveLOMInitParams()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                               DEFAULT_PARAM,
                               tr("Config (*.param)"));
    if(!filename.isNull()) {
        model->GetInitParameters().Save(filename);
    }
}

void LOMView::OnExit() {
    this->close();
}

void LOMView::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);

    this->Save(DEFAULT_CONF);
    model->Stop();
    Logger::SetWriteToFile(false);
}

void LOMView::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    double scaleY = 0.16;
    double scaleX = 0.3;

    ui->logBrowser->setMinimumHeight(scaleY * this->height());
    ui->coinWidget->setMinimumSize(scaleX * this->width(),  scaleY * this->height());
    ui->amplBWDWidget->setMinimumSize(scaleX * this->width(),  scaleY * this->height());
    ui->amplFWDWidget->setMinimumSize(scaleX * this->width(),  scaleY * this->height());
    ui->fwdEndcap->setMinimumSize(scaleY * this->height(), scaleY * this->height());
    ui->bwdEndcap->setMinimumSize(scaleY * this->height(), scaleY * this->height());

    ui->logBrowser->setMaximumHeight(scaleY * this->height());
    ui->coinWidget->setMaximumSize(scaleX * this->width(),  scaleY * this->height());
    ui->amplBWDWidget->setMaximumSize(scaleX * this->width(),  scaleY * this->height());
    ui->amplFWDWidget->setMaximumSize(scaleX * this->width(),  scaleY * this->height());
    ui->fwdEndcap->setMaximumSize(scaleY * this->height(), scaleY * this->height());
    ui->bwdEndcap->setMaximumSize(scaleY * this->height(), scaleY * this->height());

    ui->labelBwdSector->setMaximumWidth(ui->fwdEndcap->width()-40);
    ui->labelFwdSector->setMaximumWidth(ui->fwdEndcap->width()-40);
    ui->labelBwdSector->setMinimumWidth(ui->fwdEndcap->width()-40);
    ui->labelFwdSector->setMinimumWidth(ui->fwdEndcap->width()-40);

}
