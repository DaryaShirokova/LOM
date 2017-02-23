#include "inc/LOMDataProcessor.h"
#include "inc/Logger.h"

LOMDataProcessor::LOMDataProcessor(LOMDataUpdater *updater)
{
    this->updater = updater;

    // Connect timer.
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(Update()));

}

LOMDataProcessor::~LOMDataProcessor()
{

}

void LOMDataProcessor::Start()
{
    Update();
    timer->start(updateFreq);
    Logger::Log(Logger::LogLevel::DEBUG, "Data updating process has begun.");
}

void LOMDataProcessor::Stop()
{
    timer->stop();
    Logger::Log(Logger::LogLevel::DEBUG, "Data updating process has been stopped.");
}


void LOMDataProcessor::Update()
{
    updater->ReadEventData(&event);
    Logger::Log(Logger::LogLevel::DEBUG, "Received data.");
}





