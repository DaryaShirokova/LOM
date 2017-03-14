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

    connect(timerAmpls, SIGNAL(timeout()), SLOT(UpdateAmplitudes()));
    connect(timerCounters, SIGNAL(timeout()), SLOT(UpdateCounters()));
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
}

void LOMDataProcessor::Stop()
{
    timerAmpls->stop();
    timerCounters->stop();
    isRunning = false;
    Logger::Log(Logger::LogLevel::INFO, "Data updating process has been stopped.");
}


void LOMDataProcessor::UpdateAmplitudes()
{
    if(updater->ReadAmplitudes(&amplitudes))
    {
        Logger::Log(Logger::LogLevel::DEBUG, "Received amplitudes.");
        emit AmplitudesUpdated();
    }
    else
        Logger::Log(Logger::LogLevel::ERROR, "Can't update amplitudes.");

}

void LOMDataProcessor::UpdateCounters()
{
    if(updater->ReadCounters(&counters))
    {
        Logger::Log(Logger::LogLevel::DEBUG, "Received counters.");
        emit CountersUpdated();
    }
    else
        Logger::Log(Logger::LogLevel::ERROR, "Can't update counters.");

}

bool LOMDataProcessor::SetInitParameters(double thresholdFE, double thresholdBE,
                                         int coincidenceDurationThreshold,
                                         int hitThreshold, int bufSize)
{
    LOMInitParameters tempParams;
    tempParams.Init(thresholdFE, thresholdBE, coincidenceDurationThreshold,
                    hitThreshold, bufSize);
    if(updater->WriteInitParameters(&tempParams))
    {
        Logger::Log(Logger::LogLevel::INFO, "Initialisation parameters has been"
                                            " succesfully updated.");
        initParams.Init(thresholdFE, thresholdBE, coincidenceDurationThreshold,
                        hitThreshold, bufSize);
        return true;
    }
    else
    {
        Logger::Log(Logger::LogLevel::ERROR, "Failed to update initialisation "
                                             "parameters.");
        return false;
    }
}

bool LOMDataProcessor::LoadInitParameters()
{
    LOMInitParameters tempParams;
    if(updater->ReadInitParameters(&tempParams))
    {
        Logger::Log(Logger::LogLevel::INFO, "Received initialisation parameters "
                                            " from LOM.");
        initParams.Init(&tempParams);
        return true;
    }
    Logger::Log(Logger::LogLevel::ERROR, "Failed to get initialisation "
                                             "parameters.");
    return false;
}
