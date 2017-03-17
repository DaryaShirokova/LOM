#include "inc/LOMHistograms.h"

LOMHistograms::LOMHistograms()
{
    //map(Compare);
    for(int i = 1; i <= SECTOR_NUM; i++)
    {
        map.insert(QString(HIST_AMPLFE) + QString::number(i),
                   new Hist(HIST_AMPL_NBINS, HIST_AMPL_X0, HIST_AMPL_FE_X1,
                        "Amplitudes distribution in sector " +
                        QString::number(i) + " (FWD)",
                        "E, GeV", "N"));
        map.insert(QString(HIST_AMPLBE) + QString::number(i),
                   new Hist(HIST_AMPL_NBINS, HIST_AMPL_X0, HIST_AMPL_BE_X1,
                        "Amplitudes distribution in sector " +
                        QString::number(i) + " (BWD)",
                        "E, GeV", "N"));
    }
}

