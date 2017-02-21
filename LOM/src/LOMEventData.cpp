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

Amplitudes::VectorDouble Amplitudes::GetAmplitudesInSector(unsigned int sector)
{
    return amplitudes[sector];
}

double Amplitudes::GetMaxAmplitudeInSector(unsigned int sector)
{
    return *(std::max_element(amplitudes[sector].begin(), amplitudes[sector].end()));
}

Amplitudes::VectorDouble Amplitudes::GetMaxAmplitudes()
{
    QVector<double> vec;
    for (int i = 0; i < SECTOR_NUM; i++)
        vec.push_back(GetMaxAmplitudeInSector(i));
    return vec;
}

unsigned int Amplitudes::GetHitSector()
{
    unsigned int hitSector = 0;
    double maxVal = 0;
    for(unsigned int i = 0; i < SECTOR_NUM; i++)
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

LOMEventData::VectorInt LOMEventData::GetCoincidenceRegion(unsigned int sectorFWD,
                                                          unsigned int sectorBWD,
                                                          double thresholdFE,
                                                          double thresholdBE)
{
    VectorInt coinRegion;
    Amplitudes::VectorDouble fwd = amplsFWD.GetAmplitudesInSector(sectorFWD);
    Amplitudes::VectorDouble bwd = amplsBWD.GetAmplitudesInSector(sectorBWD);

    int n = std::min(fwd.size(), bwd.size());
    for(int i = 0; i < n; i++)
        if (fwd.at(i) > thresholdFE && bwd.at(i) > thresholdBE)
            coinRegion.push_back(1);
        else coinRegion.push_back(0);

    return coinRegion;
}
bool LOMEventData::haveCoincidenceRegion(unsigned int sectorFWD,
                                         unsigned int sectorBWD,
                                         double thresholdFE, double thresholdBE)
{
    VectorInt vec = GetCoincidenceRegion(sectorFWD, sectorBWD, thresholdFE, thresholdBE);

    for(int val: vec)
        if(val == 1) return true;
    return false;
}

int LOMEventData::GetCoincidenceRegionLeftBoundary(unsigned int sectorFWD,
                                                            unsigned int sectorBWD,
                                                            double thresholdFE,
                                                            double thresholdBE)
{

    VectorInt vec = GetCoincidenceRegion(sectorFWD, sectorBWD, thresholdFE, thresholdBE);

    for (int i = 0; i < vec.size(); i++)
        if(vec.at(i) == 1) return i;
    return -1;

}

int LOMEventData::GetCoincidenceRegionRightBoundary(unsigned int sectorFWD,
                                                            unsigned int sectorBWD,
                                                            double thresholdFE,
                                                            double thresholdBE)
{
    VectorInt vec = GetCoincidenceRegion(sectorFWD, sectorBWD, thresholdFE, thresholdBE);

    for (int i = vec.size() - 1; i >= 0; i--)
        if(vec.at(i) == 1) return i;
    return -1;

}
