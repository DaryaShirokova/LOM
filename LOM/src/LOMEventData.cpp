#include "../inc/LOMEventData.h"

#include <algorithm>

LOMEventData::LOMEventData()
{
    std::cout << "Default constructor for LOMEventData has been called" << std::endl;
}

LOMEventData::~LOMEventData()
{
    std::cout << "Default destructor for LOMEventData has been called" << std::endl;
}

Amplitudes::ArrayDouble Amplitudes::GetAmplitudesInSector(unsigned int sector)
{
    return amplitudes[sector];
}

double Amplitudes::GetMaxAmplitudeInSector(unsigned int sector)
{
    return *(std::max_element(amplitudes[sector].begin(), amplitudes[sector].end()));
}

unsigned int Amplitudes::GetHitSector()
{
    unsigned int hitSector = 0;
    double maxVal = 0;
    for(unsigned int i = 0; i < SECTORS_NUM; i++)
    {
        double temp = this->GetMaxAmplitudeInSector(i);
        if(temp > maxVal)
        {
            maxVal = temp;
            hitSector = i;
        }
    }
    return hitSector;
}

LOMEventData::ArrayInt LOMEventData::GetCoincidenceRegion(unsigned int sectorFWD,
                                                          unsigned int sectorBWD,
                                                          double thresholdFE, double thresholdBE)
{
    ArrayInt coinRegion;
    Amplitudes::ArrayDouble fwd = amplsFWD.GetAmplitudesInSector(sectorFWD);
    Amplitudes::ArrayDouble bwd = amplsBWD.GetAmplitudesInSector(sectorBWD);

    for(int i = 0; i < SAMPLES_NUM; i++)
        if (fwd[i] > thresholdFE && bwd[i] > thresholdBE)
            coinRegion[i] = 1;
        else coinRegion[i] = 0;

    return coinRegion;
}
