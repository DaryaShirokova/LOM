#ifndef LOMCounters_H
#define LOMCounters_H

#include <QVector>
#include "inc/Constants.h"

#include <TTree.h>
#include <TFile.h>

class LOMCounters
{
private:
    int deltaT; /*!< Time between two readings. */
    int deadTime; /*!< Dead time in the calorimeter. */
    int totalDeadTime; /*!< Total dead time in the calorimeter. */
    int vetoTime; /*!< Total veto time. */

    int nBhabhaTotal; /*!< The total number of detected bhabha events.*/
    int nBkgTotal; /*!< The total number of background events.*/

    TTree* tree;
public:
    //**************************************************************************
    // Constructor/destructor.
    //**************************************************************************

    //! A default constructor.
    LOMCounters();

    //! A destructor.
    ~LOMCounters();

    //**************************************************************************
    // Saving to root tree.
    //**************************************************************************
    void InitTree();
    void FillTree();
    void ToFile(QString filename);
    int TreeSize();
    void ClearTree();

    //**************************************************************************
    // Getters/Setters.
    //**************************************************************************
    int GetDeltaT() { return deltaT; }
    double GetDeltaTMSec() {return deltaT * 1.0 / COUNTS_PER_MSEC;}
    void SetDeltaT(int deltaT) { this->deltaT = deltaT;}

    int GetDeadTime() { return deadTime; }
    double GetDeadTimeMSec() {return deadTime * 1.0 / COUNTS_PER_MSEC;}
    void SetDeadTime(int deadTime) { this->deadTime = deadTime;}

    int GetTotalDeadTime() { return totalDeadTime; }
    double GetTotalDeadTimeMSec() {return totalDeadTime * 1.0 / COUNTS_PER_MSEC;}
    void SetTotalDeadTime(int totalDeadTime) { this->totalDeadTime = totalDeadTime;}

    int GetVetoTime() { return vetoTime; }
    double GetVetoTimeMSec() {return vetoTime * 1.0 / COUNTS_PER_MSEC;}
    void SetVetoTime(int vetoTime) { this->vetoTime = vetoTime;}

    int GetNBhabhaTotal() { return nBhabhaTotal; }
    void SetNBhabhaTotal(int nBhabhaTotal) { this->nBhabhaTotal = nBhabhaTotal;}

    int GetNBkgTotal() { return nBkgTotal; }
    void SetNBkgTotal(int nBkgTotal) { this->nBkgTotal = nBkgTotal;}
};

#endif // LOMCounters_H
