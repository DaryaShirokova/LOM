#include "../inc/LOMInitParameters.h"

LOMInitParameters::LOMInitParameters()
{
}

LOMInitParameters::~LOMInitParameters()
{
}

void LOMInitParameters::Init(unsigned int thresholdFE, unsigned int thresholdBE,
                             unsigned int coincidenceDurationThreshold,
                             unsigned int backgroundThreshold)
{
    this->thresholdBE = thresholdBE;
    this->thresholdFE = thresholdFE;
    this->coincidenceDurationThreshold = coincidenceDurationThreshold;
    this->backgroundThreshold = backgroundThreshold;
}
