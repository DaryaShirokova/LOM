#include "../inc/LOMDataUpdater.h"
#include <TTree.h>
#include <TFile.h>

LOMDataUpdater::LOMDataUpdater()
{

}

LOMDataUpdater::~LOMDataUpdater()
{

}

bool LOMDataUpdater::ReadEventData(LOMEventData *eventData)
{
    TFile file("Event.root");
}
