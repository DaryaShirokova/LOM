#ifndef LOMCounters_H
#define LOMCounters_H

#include <QVector>
#include "inc/Constants.h"

#include <TTree.h>
#include <TFile.h>

class LOMCounters {
private:
    int deltaT; /*!< Time between two readings. */
    int deadTime; /*!< Dead time in the calorimeter. */
    int totalDeadTime; /*!< Total dead time in the calorimeter. */
    int vetoTime; /*!< Total veto time. */

    int nBhabhaTotal; /*!< The total number of detected bhabha events.*/
    int nBkgTotal; /*!< The total number of background events.*/

    TTree* tree; /*!< root framework tree.*/

public:
    //**************************************************************************
    // Constructor/destructor.
    //**************************************************************************

    /*!
     * \brief Default constructor.
     */
    LOMCounters() {}

    /*!
     * \brief Destructor.
     */
    ~LOMCounters() {}

    //**************************************************************************
    // Preparing root tree.
    //**************************************************************************

    /*!
     * \brief Allocate memory and create branches.
     */
    void InitTree();

    /*!
     * \brief Add counters to the tree.
     */
    void FillTree();

    /*!
     * \brief Save the tree to file.
     * \param filename file name.
     */
    void ToFile(QString filename);

    /*!
     * \brief Get current size of the tree.
     * \return current size of the tree.
     */
    int TreeSize();

    /*!
     * \brief Deallocate used memory.
     */
    void ClearTree();

    //**************************************************************************
    // Getters/Setters.
    //**************************************************************************

    /*!
     * \brief Get dT counter.
     * \return dT
     */
    int GetDeltaT() { return deltaT; }

    /*!
     * \brief Get dT counter in msec.
     * \return dT (msec)
     */
    double GetDeltaTMSec() {return deltaT * 1.0 / COUNTS_PER_MSEC;}

    /*!
     * \brief Set dT counter.
     * \param dT    dT
     */
    void SetDeltaT(int deltaT) { this->deltaT = deltaT;}

    /*!
     * \brief Get dead time.
     * \return deadTime
     */
    int GetDeadTime() { return deadTime; }

    /*!
     * \brief Get dead time msec.
     * \return deadTime (msec)
     */
    double GetDeadTimeMSec() {return deadTime * 1.0 / COUNTS_PER_MSEC;}

    /*!
     * \brief Set dead time counter.
     * \param dT    dT
     */
    void SetDeadTime(int deadTime) { this->deadTime = deadTime;}

    /*!
     * \brief Get total dead time counter.
     * \return total dead time
     */
    int GetTotalDeadTime() { return totalDeadTime; }

    /*!
     * \brief Get total dead time counter in msec.
     * \return total dead time (msec)
     */
    double GetTotalDeadTimeMSec() {return totalDeadTime * 1.0 / COUNTS_PER_MSEC;}

    /*!
     * \brief Set total dead time counter.
     * \param totalDeadTime total dead time
     */
    void SetTotalDeadTime(int totalDeadTime) { this->totalDeadTime = totalDeadTime;}

    /*!
     * \brief Get veto time counter.
     * \return veto time
     */
    int GetVetoTime() { return vetoTime; }

    /*!
     * \brief Get veto time counter in msec.
     * \return veto time (msec)
     */
    double GetVetoTimeMSec() {return vetoTime * 1.0 / COUNTS_PER_MSEC;}

    /*!
     * \brief Set veto time counter.
     * \param vetoTime veto time
     */
    void SetVetoTime(int vetoTime) { this->vetoTime = vetoTime;}

    /*!
     * \brief Get total number of Bhabha events.
     * \return total number of Bhabha events.
     */
    int GetNBhabhaTotal() { return nBhabhaTotal; }

    /*!
     * \brief Set total number of Bhabha events.
     * \param nBhabhaTotal total number of Bhabha events.
     */
    void SetNBhabhaTotal(int nBhabhaTotal) { this->nBhabhaTotal = nBhabhaTotal;}

    /*!
     * \brief Get total number of background events.
     * \return total number of background events.
     */
    int GetNBkgTotal() { return nBkgTotal; }

    /*!
     * \brief Set total number of background events.
     * \param nBkgTotal total number of background events.
     */
    void SetNBkgTotal(int nBkgTotal) { this->nBkgTotal = nBkgTotal;}
};

#endif // LOMCounters_H
