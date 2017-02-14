#include "../inc/LOMInitParameters.h"

#include <iostream>

LOMInitParameters::LOMInitParameters()
{
    std::cout << "Default constructor for LOMInitParamaters has been called" << std::endl;
}

LOMInitParameters::~LOMInitParameters()
{
    std::cout << "Default denstructor for LOMInitParamaters has been called" << std::endl;
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
