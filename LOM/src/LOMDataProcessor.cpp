#include "../inc/LOMDataProcessor.h"

LOMDataProcessor::LOMDataProcessor(std::string initfileName, std::string logfileName, LOMDataUpdater *updater)
{
    std::cout << "Data processor constructor." << std::endl;
    this->updater = updater;

}

void LOMDataProcessor::Start()
{
    updater->ReadEventData(&event);
}

void LOMDataProcessor::Stop()
{
    std::cout << "Default destructor for LOMInitParamaters has been called" << std::endl;
}
