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
                             int hitThreshold, int bufSize)
{
    this->thresholdBE = thresholdBE;
    this->thresholdFE = thresholdFE;
    this->coincidenceDurationThreshold = coincidenceDurationThreshold;
    this->hitThreshold = hitThreshold;
    this->bufSize = bufSize;
}

void LOMInitParameters::Init(LOMInitParameters *newInit)
{
    this->thresholdBE = newInit->GetThresholdBE();
    this->thresholdFE = newInit->GetThresholdFE();
    this->coincidenceDurationThreshold = newInit->GetCoincidenceDurationThreshold();
    this->hitThreshold = newInit->GetHitThreshold();
    this->bufSize = newInit->GetBufSize();
}
