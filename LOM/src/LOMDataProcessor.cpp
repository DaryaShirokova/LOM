#include "inc/LOMDataProcessor.h"
#include "inc/Logger.h"

LOMDataProcessor::LOMDataProcessor(LOMDataUpdater *updater)
{
    this->updater = updater;

    isRunning = false;
    writeTree = false;
    treeSize = DEFAULT_TREE_SIZE;
    dataDir = DATA_PATH;

    // Connect timer.
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(Update()));

}

LOMDataProcessor::~LOMDataProcessor()
{

}

void LOMDataProcessor::Start()
{
    Logger::Log(Logger::LogLevel::INFO, "Data updating process has begun.");
    isRunning = true;
    Update();
    timer->start(updateFreq);
}

void LOMDataProcessor::Stop()
{
    timer->stop();
    isRunning = false;
    Logger::Log(Logger::LogLevel::INFO, "Data updating process has been stopped.");
}


void LOMDataProcessor::Update()
{
    updater->ReadEventData(&event);
    Logger::Log(Logger::LogLevel::DEBUG, "Received data.");
}

bool LOMDataProcessor::SetInitParameters(double thresholdFE, double thresholdBE,
                                         unsigned int coincidenceDurationThreshold,
                                         unsigned int backgroundThreshold)
{
    LOMInitParameters tempParams;
    tempParams.Init(thresholdFE, thresholdBE, coincidenceDurationThreshold,
                    backgroundThreshold);
    if(updater->WriteInitParameters(&tempParams))
    {
        Logger::Log(Logger::LogLevel::INFO, "Initialisation parameters has been"
                                            " succesfully updated.");
        initParams.Init(thresholdFE, thresholdBE, coincidenceDurationThreshold,
                        backgroundThreshold);
        return true;
    }
    else
    {
        Logger::Log(Logger::LogLevel::ERROR, "Failed to update initialisation "
                                             "parameters.");
        return false;
    }
}
