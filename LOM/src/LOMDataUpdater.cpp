#include "inc/LOMDataUpdater.h"
#include "inc/Logger.h"


#include <TTree.h>
#include <TFile.h>
#include <QByteArray>

#include <time.h>
#include <QDebug>

LOMDataUpdater::LOMDataUpdater(AbstractTransporter *transporter)
{
    this->transporter = transporter;
}

bool LOMDataUpdater::ReadEventData(LOMEventData *eventData)
{
    TFile fileIn("../data/lomtest_15deg_1k_1.root");
    TTree *tree = (TTree*)fileIn.Get("testtree");

    Double_t bewf[16][64];
    Double_t fewf[16][64];

    TBranch *bbranch = tree->GetBranch("bewf[16][64]");
    TBranch *fbranch = tree->GetBranch("fewf[16][64]");

    tree->SetBranchAddress("bewf[16][64]", &bewf);
    tree->SetBranchAddress("fewf[16][64]", &fewf);

    srand (time(NULL));
    int stopsignal = rand() % 1000;

    for (int i=0; i < tree->GetEntries(); i++)
    {
        bbranch->GetEvent(i);
        fbranch->GetEvent(i);
        QVector<QVector<double>> amplitudesFE;
        QVector<QVector<double>> amplitudesBE;
        for(int t = 0; t < 16; t++)
        {
            QVector<double> sectorFE;
            QVector<double> sectorBE;
            for(int s = 0; s < 64; s++)
            {
                sectorFE.push_back(fewf[t][s]);
                sectorBE.push_back(bewf[t][s]);
            }
            amplitudesFE.push_back(sectorFE);
            amplitudesBE.push_back(sectorBE);
        }
        eventData->GetAmplsFWD().SetAmplitudes(amplitudesFE);
        eventData->GetAmplsBWD().SetAmplitudes(amplitudesBE);
        if(i == stopsignal)
            break;
    }
    return true;
}

bool LOMDataUpdater::WriteInitParameters(LOMInitParameters *initParameters)
{
    QByteArray arr;
    int aa;
    arr.push_back('W');
    arr.push_back('R');
    aa = 3000;
    arr.push_back(aa);
    return transporter->WriteData(arr, arr.size());//(out.toUtf8().constData(), out.size());
}
