#include "inc/LOMDataProcessor.h"
#include "inc/Logger.h"

LOMDataProcessor::LOMDataProcessor(LOMDataUpdater *updater)
{
    this->updater = updater;

    isRunning = false;
    SetWriteTree(false);
    SetWriteHist(false);
    treeSize = DEFAULT_TREE_SIZE;
    dataDir = DATA_PATH;
    histDir = HIST_PATH;

    // Connect timers.
    timerAmpls = new QTimer(this);
    timerCounters = new QTimer(this);
    timerHists = new QTimer(this);

    connect(timerAmpls, SIGNAL(timeout()), SLOT(UpdateAmplitudes()));
    connect(timerCounters, SIGNAL(timeout()), SLOT(UpdateCounters()));
    connect(timerHists, SIGNAL(timeout()),SLOT(UpdateHists()));
}

LOMDataProcessor::~LOMDataProcessor()
{
}

void LOMDataProcessor::Start() {
    if(!isRunning) {
        Logger::Log(Logger::LogLevel::INFO, "Data updating process has begun.");
        isRunning = true;
        UpdateAmplitudes();
        timerAmpls->start(updateAmplsFreq * 1000);
        timerCounters->start(updateCountersFreq * 1000);
        timerHists->start(updateHistsFreq * 1000);
        if(writeTree)
            counters.InitTree();
    }
}

void LOMDataProcessor::Stop()
{
    if(isRunning) {
        timerAmpls->stop();
        timerCounters->stop();
        timerHists->stop();
        isRunning = false;
        Logger::Log(Logger::LogLevel::INFO, "Data updating process has been stopped.");
        if(writeTree)
            counters.ToFile(CreateFileName());
    }
}


void LOMDataProcessor::UpdateAmplitudes()
{
    if(updater->ReadAmplitudes(&amplitudes, initParams.GetBufSize()))
    {
        Logger::Log(Logger::LogLevel::DEBUG, "Received amplitudes.");
        emit AmplitudesUpdated();
    }
    else
        Logger::Log(Logger::LogLevel::ERROR, "Can't update amplitudes.");
}

void LOMDataProcessor::UpdateCounters() {
    if(updater->ReadCounters(&counters))     {
        Logger::Log(Logger::LogLevel::DEBUG, "Received counters.");
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

void LOMDataProcessor::UpdateHists() {
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
        Logger::Log(Logger::LogLevel::INFO, "Initialisation parameters has been"
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

    for(int i = 0; i < hists.GetFavorite().size(); i++)
        settings->setValue("favorite_hist"+QString::number(i+1),
                           hists.GetFavorite().at(i));

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
    settings->endGroup();
    for(int i = 0; i < 4; i++) {
        QString key = settings->value("favorite_hist"+QString::number(i+1), "").toString();
        if(hists.GetHists().contains(key))
            hists.GetHists().value(key)->SetFavorite(true);
    }
    emit TimingUpdated();
    emit TreeSettingsUpdated();
    emit HistSettingsUpdated();
}
