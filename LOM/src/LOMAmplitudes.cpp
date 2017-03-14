#include "inc/LOMAmplitudes.h"
#include "inc/Constants.h"

LOMAmplitudes::LOMAmplitudes()
{

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

LOMAmplitudes::VectorInt LOMAmplitudes::GetCoincidenceRegion(unsigned int sectorFWD,
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
bool LOMAmplitudes::haveCoincidenceRegion(unsigned int sectorFWD,
                                         unsigned int sectorBWD,
                                         double thresholdFE, double thresholdBE)
{
    VectorInt vec = GetCoincidenceRegion(sectorFWD, sectorBWD, thresholdFE, thresholdBE);

    for(int val: vec)
        if(val == 1) return true;
    return false;
}

int LOMAmplitudes::GetCoincidenceRegionLeftBoundary(unsigned int sectorFWD,
                                                            unsigned int sectorBWD,
                                                            double thresholdFE,
                                                            double thresholdBE)
{

    VectorInt vec = GetCoincidenceRegion(sectorFWD, sectorBWD, thresholdFE, thresholdBE);

    for (int i = 0; i < vec.size(); i++)
        if(vec.at(i) == 1) return i;
    return -1;

}

int LOMAmplitudes::GetCoincidenceRegionRightBoundary(unsigned int sectorFWD,
                                                            unsigned int sectorBWD,
                                                            double thresholdFE,
                                                            double thresholdBE)
{
    VectorInt vec = GetCoincidenceRegion(sectorFWD, sectorBWD, thresholdFE, thresholdBE);

    for (int i = vec.size() - 1; i >= 0; i--)
        if(vec.at(i) == 1) return i;
    return -1;

}
