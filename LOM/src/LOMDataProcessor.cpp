#include "../inc/LOMDataProcessor.h"

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
}

void LOMDataProcessor::Stop()
{
    timer->stop();
}


void LOMDataProcessor::Update()
{
    updater->ReadEventData(&event);
}





