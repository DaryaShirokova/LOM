#include "../inc/LOMInitParameters.h"

#include <QDebug>

LOMInitParameters::LOMInitParameters()
{
}

LOMInitParameters::~LOMInitParameters()
{
}

void LOMInitParameters::Init(double thresholdFE, double thresholdBE,
                             int coincidenceDurationThreshold,
                             int backgroundThreshold)
{
    this->thresholdBE = thresholdBE;
    this->thresholdFE = thresholdFE;
    this->coincidenceDurationThreshold = coincidenceDurationThreshold;
    this->backgroundThreshold = backgroundThreshold;
}
