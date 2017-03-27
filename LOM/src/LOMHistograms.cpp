#include "inc/LOMHistograms.h"


//******************************************************************************
// Hist class.
//******************************************************************************
Hist::Hist(int nbins, double x0, double x1, QString title,
     QString xTitle, QString yTitle) {
    this->nbins = nbins;
    this->x0 = x0;
    this->x1 = x1;
    this->title = title;
    this->xTitle = xTitle;
    this->yTitle = yTitle;
    this->favorite = false;
}

void Hist::ToFile(QString filename) {
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    if(file.isOpen() && file.exists()) {
        for(int i = 0; i < hist.size(); i++){
            QString str = QString::number(GetXValues().at(i))+"\t"+QString::number(hist.at(i))+"\n";
            file.write(str.toStdString().c_str());
        }
        file.flush();
        file.close();
    }
    else Logger::Log(Logger::ERROR, "LOMHistograms: can't save histograms to file " +
                     filename + ". " + file.errorString());
}

void Hist::SetHist(QVector<int> hist) {
    if(hist.size() != nbins) {
        Logger::Log(Logger::DEBUG, "Logger: unexpected number of bins.");
        nbins = hist.size();
    }
    this->hist = hist;
}

QVector<double> Hist::GetXValues() {
    QVector<double> xval;
    for(int i = 0; i < nbins; i++)
        xval.push_back(x0 + i * (x1-x0)/(nbins-1));
    return xval;
}

QVector<double> Hist::GetHistDouble() {
    QVector<double> histDouble;
    for(int i = 0; i < hist.size(); i++)
        histDouble.push_back(hist.at(i));
    return histDouble;
}

//******************************************************************************
// LOMHistograms class.
//******************************************************************************

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

QStringList LOMHistograms::GetFavorite() {
    QStringList l;

    QMap<QString, Hist*>::iterator i;
    for(i = map.begin(); i != map.end(); ++i)
        if(i.value()->IsFavorite() && l.size() < 4)
            l.push_back(i.key());
    return l;
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

