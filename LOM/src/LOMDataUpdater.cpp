#include "../inc/LOMDataUpdater.h"


#include <TTree.h>
#include <TFile.h>

#include <iostream>
#include <vector>


#include <time.h>


LOMDataUpdater::LOMDataUpdater()
{
    std::cout << "Default constructor for LOMDataUpdater has been called" << std::endl;
}

LOMDataUpdater::~LOMDataUpdater()
{

}

bool LOMDataUpdater::ReadEventData(LOMEventData *eventData)
{
    std::cout << "Start reading data " << std::endl;
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
        eventData->GetAmplsFWD().SetAmplitudes(fewf);
        eventData->GetAmplsBWD().SetAmplitudes(bewf);
        if(i == stopsignal)
            break;
    }
    std::cout << "Read Event Data Func" << std::endl;

    return true;
}
