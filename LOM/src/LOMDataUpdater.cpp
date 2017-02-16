#include "../inc/LOMDataUpdater.h"


#include <TTree.h>
#include <TFile.h>

#include <iostream>
#include <vector>

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
    //std::cout << eventData->GetSectorFE() << std::endl;
    TFile fileIn("../data/lomtest_15deg_1k_1.root");
    TTree *tree = (TTree*)fileIn.Get("testtree");

    Double_t bewf[16][64];
    Double_t fewf[16][64];

    TBranch *bbranch = tree->GetBranch("bewf[16][64]");
    TBranch *fbranch = tree->GetBranch("fewf[16][64]");

    tree->SetBranchAddress("bewf[16][64]", &bewf);
    tree->SetBranchAddress("fewf[16][64]", &fewf);

    for (int i=0; i < tree->GetEntries(); i++) {
        bbranch->GetEvent(i);
        fbranch->GetEvent(i);
        eventData->GetAmplsFWD().SetAmplitudes(fewf);
        eventData->GetAmplsBWD().SetAmplitudes(bewf);
       /* for(int j = 0; j < 16; j++)
        {
            for(int k = 0; k < 64; k++)
            {
                if(fewf[j][k] > 0.1)
                    std::cout << i  << " " << j << " " << k << " " << fewf[j][k] << " " << eventData->GetAmplsFWD().GetAmplitudes()[j][k] << std::endl;
            }
        }*/
        if(i == 1)
        break;
    }
    std::cout << "Read Event Data Func" << std::endl;

    /*for(int j = 0; j < 16; j++)
    {
        for(int k = 0; k < 64; k++)
        {

            //if(fewf[j][k] > 0.1)
            std::cout << eventData->GetAmplsBWD().GetAmplitudes()[j][k] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }*/
    return true;
}
