#include "inc/LOMHistograms.h"

LOMHistograms::LOMHistograms() {
    runNum = 0;
    for(int i = 1; i <= SECTOR_NUM; i++) {
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

void LOMHistograms::SaveToFiles(QString path) {
    runNum++;
    if(!path.isEmpty() && !path.endsWith('/'))
        path = path + '/';
    QMap<QString, Hist*>::iterator i;
    for(i = map.begin(); i != map.end(); ++i) {
        QString filename = path + i.key() + "_" + QString::number(runNum);
        i.value()->ToFile(filename);
    }

}

