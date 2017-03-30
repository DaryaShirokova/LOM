#include "inc/LOMDataProcessor.h"
#include "inc/Logger.h"
#include "inc/LuminosityCalculator.h"

//******************************************************************************
// Constructor/ destructor.
//******************************************************************************

LOMDataProcessor::LOMDataProcessor(LOMDataUpdater *updater) {
    this->updater = updater;

    timerAmpls = new QTimer(this);
    timerCounters = new QTimer(this);
    timerHists = new QTimer(this);
    histsToFileTimer = new QTimer(this);

    isRunning = false;
    SetWriteTree(false);
    SetWriteHist(false);
    treeSize = DEFAULT_TREE_SIZE;
    dataDir = DATA_PATH;
    histDir = HIST_PATH;

    // Connect timers.
    connect(timerAmpls, SIGNAL(timeout()), SLOT(UpdateAmplitudes()));
    connect(timerCounters, SIGNAL(timeout()), SLOT(UpdateCounters()));
    connect(timerHists, SIGNAL(timeout()),SLOT(UpdateHistograms()));
    connect(histsToFileTimer, SIGNAL(timeout()), SLOT(HistsToFile()));
}

LOMDataProcessor::~LOMDataProcessor() {
    delete timerAmpls;
    delete timerCounters;
    delete timerHists;
    delete histsToFileTimer;
}

//******************************************************************************
// Data updates.
//******************************************************************************

void LOMDataProcessor::Start() {
    if(!isRunning) {
        Logger::Log(Logger::LogLevel::INFO, "Data updating process has begun.");
        isRunning = true;
        UpdateAmplitudes();
        timerAmpls->start(updateAmplsFreq * 1000);
        timerCounters->start(updateCountersFreq * 1000);
        timerHists->start(updateHistsFreq * 1000);
        if(writeHist)
            histsToFileTimer->start(writeHistFreq * 60 * 1000);
        if(writeTree)
            counters.InitTree();
    }
}

void LOMDataProcessor::Stop() {
    if(isRunning) {
        timerAmpls->stop();
        timerCounters->stop();
        timerHists->stop();
        histsToFileTimer->stop();
        isRunning = false;
        Logger::Log(Logger::LogLevel::INFO, "Data updating process has been stopped.");
        if(writeTree)
            counters.ToFile(CreateFileName());
    }
}


void LOMDataProcessor::UpdateAmplitudes() {
    if(updater->ReadAmplitudes(&amplitudes, initParams.GetBufSize())) {
        Logger::Log(Logger::LogLevel::DEBUG, "Received amplitudes.");
        emit AmplitudesUpdated();
    }
    else
        Logger::Log(Logger::LogLevel::ERROR, "Can't update amplitudes.");
}

void LOMDataProcessor::UpdateCounters() {
    if(updater->ReadCounters(&counters))     {
        Logger::Log(Logger::LogLevel::DEBUG, "Received counters.");
        luminosity.push_back(LuminosityCalculator::GetLuminosity(counters.GetNBhabhaTotal(),
                                                                 counters.GetDeltaT()));
        background.push_back(LuminosityCalculator::GetBackground(counters.GetNBkgTotal(),
                                                                 counters.GetDeltaT()));
        emit CountersUpdated();
        if(writeTree) {
            counters.FillTree();
            if(counters.TreeSize() >= treeSize) {
                counters.ToFile(CreateFileName());
                counters.ClearTree();
                counters.InitTree();
            }
        }
    }
    else
        Logger::Log(Logger::LogLevel::ERROR, "Can't update counters.");

}

void LOMDataProcessor::UpdateHistograms() {
    if(updater->ReadHists(&hists))     {
        Logger::Log(Logger::LogLevel::DEBUG, "Received hists.");
        emit HistsUpdated();
    }
    else
        Logger::Log(Logger::LogLevel::ERROR, "Can't update histograms.");
}

bool LOMDataProcessor::SetInitParameters(double thresholdFE, double thresholdBE,
                                         int coincidenceDurationThreshold,
                                         int hitThreshold, int bufSize) {
    if(timerCounters->isActive()) {
        Logger::Log(Logger::LogLevel::ERROR, "Trying to set thresholds while running.");
        return false;
    }

    initParams.Init(thresholdFE, thresholdBE, coincidenceDurationThreshold,
                    hitThreshold, bufSize);
    if(updater->WriteInitParameters(&initParams)) {
        Logger::Log(Logger::LogLevel::INFO, "Initialisation parameters have been"
                                            " succesfully updated.");
        initParams.SetStatus(true);
        return true;
    }
    else {
        Logger::Log(Logger::LogLevel::ERROR, "Failed to update initialisation "
                                             "parameters.");
        return false;
    }
}

bool LOMDataProcessor::LoadInitParameters() {
    if(timerCounters->isActive()) {
        Logger::Log(Logger::LogLevel::ERROR, "Trying to load thresholds while running.");
        return false;
    }

    LOMInitParameters tempParams;
    if(updater->ReadInitParameters(&tempParams)) {
        Logger::Log(Logger::LogLevel::INFO, "Received initialisation parameters "
                                            " from LOM.");
        initParams.Init(&tempParams);
        initParams.SetStatus(true);
        return true;
    }
    Logger::Log(Logger::LogLevel::ERROR, "Failed to get initialisation "
                                             "parameters.");
    return false;
}


//******************************************************************************
// Saving data / confidurations to files.
//******************************************************************************

void LOMDataProcessor::HistsToFile() {
    hists.SaveToFiles(histDir);
}

QString LOMDataProcessor::CreateFileName() {
    QString name;
    QStringList filters;
    filters << "run*.root";
    QDir dir(dataDir);
    if(!dir.exists()) {
        Logger::Log(Logger::ERROR, "LOMDataProcessor: The directory to save trees doesn't exist:" +
                     dataDir + " The tree will be saved in the temporary file temp.root.");
        return "temp.root";
    }
    QStringList l = dir.entryList(filters,
                                    QDir::Files,
                                    QDir::Name);
    for(int i = 0; true; i++) {
        name = "run" + QString::number(i) + ".root";
        if(!l.contains(name))
            break;
    }

    if(!dataDir.endsWith('/'))
        name = '/' + name;
    return dataDir + name;
}

void LOMDataProcessor::Save(QSettings* settings) {

    settings->beginGroup("MODEL");

    settings->setValue("counters_freq_s", this->updateCountersFreq);
    settings->setValue("ampl_freq_s", this->updateAmplsFreq);
    settings->setValue("hist_freq_s", this->updateHistsFreq);

    settings->setValue("write_tree", this->writeTree);
    settings->setValue("tree_size", this->treeSize);
    settings->setValue("data_dir", this->dataDir);

    settings->setValue("write_hist", this->writeHist);
    settings->setValue("write_hist_freq_min", this->writeHistFreq);
    settings->setValue("hist_dir", this->histDir);
    settings->setValue("hist_run_n", hists.GetRunNum());
    int i;
    for(i = 0; i < hists.GetFavorite().size(); i++)
        settings->setValue("favorite_hist"+QString::number(i+1),
                           hists.GetFavorite().at(i));
    for(int j = i; j < 4; j++)
        settings->setValue("favorite_hist"+QString::number(j+1),
                           "");

    settings->endGroup();
}

void LOMDataProcessor::Load(QSettings* settings) {
    settings->beginGroup("MODEL");
    updateCountersFreq = settings->value("counters_freq_s", 1.).toDouble();
    updateAmplsFreq = settings->value("ampl_freq_s", 5.).toDouble();
    updateHistsFreq = settings->value("hist_freq_s", 60.).toDouble();

    writeTree = settings->value("write_tree", false).toBool();
    treeSize = settings->value("tree_size", 10000).toInt();
    dataDir = settings->value("data_dir", DATA_PATH).toString();

    writeHist = settings->value("write_hist", false).toBool();
    writeHistFreq = settings->value("write_hist_freq_min", 60).toInt();
    histDir = settings->value("hist_dir", HIST_PATH).toString();
    hists.SetRunNum(settings->value("hist_run_n", 0).toInt());

    for(int i = 0; i < 4; i++) {
        QString key = settings->value("favorite_hist"+QString::number(i+1), "").toString();
        if(hists.GetHists().contains(key))
            hists.GetHists().value(key)->SetFavorite(true);
    }
    settings->endGroup();
    emit TimingUpdated();
    emit TreeSettingsUpdated();
    emit HistSettingsUpdated();
}

void LOMDataProcessor::SetWriteHist(bool writeHist) {
    this->writeHist = writeHist;
    if(histsToFileTimer == NULL)
        return;
    if(isRunning && writeHist)
        histsToFileTimer->start(writeHistFreq * 60 * 1000);
    else if(histsToFileTimer->isActive())
        histsToFileTimer->stop();
    emit HistSettingsUpdated();

}
