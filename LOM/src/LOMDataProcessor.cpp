#include "../inc/LOMDataProcessor.h"

LOMDataProcessor::LOMDataProcessor(std::string initfileName, std::string logfileName, LOMDataUpdater *updater)
{
    std::cout << "Data processor constructor." << std::endl;
    this->updater = updater;

    // TODO: get this from gui.
    updateFreq = 1000;

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
}

void LOMDataProcessor::Stop()
{
    timer->stop();
}


void LOMDataProcessor::Update()
{
    updater->ReadEventData(&event);
}





