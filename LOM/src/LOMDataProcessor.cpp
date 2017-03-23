#include "inc/LOMDataProcessor.h"
#include "inc/Logger.h"

LOMDataProcessor::LOMDataProcessor(LOMDataUpdater *updater)
{
    this->updater = updater;

    isRunning = false;
    writeTree = false;
    treeSize = DEFAULT_TREE_SIZE;
    dataDir = DATA_PATH;

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

void LOMDataProcessor::Start()
{
    Logger::Log(Logger::LogLevel::INFO, "Data updating process has begun.");
    isRunning = true;
    UpdateAmplitudes();
    timerAmpls->start(updateAmplsFreq);
    timerCounters->start(updateCountersFreq);
    timerHists->start(updateHistsFreq);
    if(writeTree)
        counters.InitTree();
}

void LOMDataProcessor::Stop()
{
    timerAmpls->stop();
    timerCounters->stop();
    timerHists->stop();
    isRunning = false;
    Logger::Log(Logger::LogLevel::INFO, "Data updating process has been stopped.");
    if(writeTree)
        counters.ToFile(CreateFileName());
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
    LOMInitParameters tempParams;
    if(updater->ReadInitParameters(&tempParams)) {
        Logger::Log(Logger::LogLevel::INFO, "Received initialisation parameters "
                                            " from LOM.");
        initParams.Init(&tempParams);
        return true;
    }
    Logger::Log(Logger::LogLevel::ERROR, "Failed to get initialisation "
                                             "parameters.");
    return false;
}

void LOMDataProcessor::SetWriteTree(bool writeTree) {
    this->writeTree = writeTree;
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
