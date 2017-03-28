#include "inc/LOMCounters.h"
#include "inc/Logger.h"

void LOMCounters::InitTree() {
    Logger::Log(Logger::DEBUG, "Creating new tree.");
    tree = new TTree("tree", "LOM countets.");
    tree->Branch("nbhabha", &nBhabhaTotal,"nbhabha/I");
    tree->Branch("nbkg",&nBkgTotal,"nbkg/I");
    tree->Branch("deadT",&deadTime,"deadT/I");
    tree->Branch("totalDeadT",&totalDeadTime,"totalDeadT/I");
    tree->Branch("vetoT",&vetoTime,"vetoT/I");
    tree->Branch("dT",&deltaT,"dT/I");
}

void LOMCounters::FillTree() {
    if(tree != NULL)
        tree->Fill();
    else Logger::Log(Logger::ERROR, "LOMCounters: Ponter to tree is null. Can't fill the tree.");
}

int LOMCounters::TreeSize() {
    if(tree!= NULL)
        return tree->GetEntries();
    return 0;
}

void LOMCounters::ToFile(QString filename)
{
    if(tree == NULL) {
        Logger::Log(Logger::ERROR, "LOMCounters: Ponter to tree is null. Can't save the tree to file.");
        return;
    }

    TFile f(filename.toStdString().c_str(),"recreate");
    if(!f.IsOpen()) {
        Logger::Log(Logger::ERROR, "LOMCounters: Can't open file to save the tree: " + filename);
        return;
    }

    if(!tree->Write())
        Logger::Log(Logger::ERROR, "LOMCounters: Error while writing tree to file: " + filename);
    else Logger::Log(Logger::DEBUG, "LOMCounters: Counters are saved to file: " + filename);
    f.Close();
}

void LOMCounters::ClearTree() {
    if(tree != NULL)
        delete tree;
}
