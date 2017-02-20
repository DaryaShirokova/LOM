#include "../inc/LOMEventData.h"

#include <algorithm>

LOMEventData::LOMEventData()
{
    /*double arr;
    for (int i = 0; i < arr.size(); i++)
        for(int j = 0; j < arr.size(); j++)
            arr[i] = 0;
    this->GetAmplsBWD().SetAmplitudes();*/
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

std::array<double, SECTORS_NUM> Amplitudes::GetMaxAmplitudes()
{
    std::array<double, SECTORS_NUM> arr;
    for (int i = 0; i < SECTORS_NUM; i++)
        arr[i] = GetMaxAmplitudeInSector(i);
    return arr;
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
                                                          double thresholdFE,
                                                          double thresholdBE)
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
bool LOMEventData::haveCoincidenceRegion(unsigned int sectorFWD,
                                         unsigned int sectorBWD,
                                         double thresholdFE, double thresholdBE)
{
    ArrayInt arr = GetCoincidenceRegion(sectorFWD, sectorBWD, thresholdFE, thresholdBE);

    for(int val: arr)
        if(val == 1) return true;
    return false;
}

int LOMEventData::GetCoincidenceRegionLeftBoundary(unsigned int sectorFWD,
                                                            unsigned int sectorBWD,
                                                            double thresholdFE,
                                                            double thresholdBE)
{

    ArrayInt arr = GetCoincidenceRegion(sectorFWD, sectorBWD, thresholdFE, thresholdBE);

    for (int i = 0; i < SAMPLES_NUM; i++)
        if(arr[i] == 1) return i;
    return -1;

}

int LOMEventData::GetCoincidenceRegionRightBoundary(unsigned int sectorFWD,
                                                            unsigned int sectorBWD,
                                                            double thresholdFE,
                                                            double thresholdBE)
{
    ArrayInt arr = GetCoincidenceRegion(sectorFWD, sectorBWD, thresholdFE, thresholdBE);

    for (int i = SAMPLES_NUM - 1; i >= 0; i--)
        if(arr[i] == 1) return i;
    return -1;

}
