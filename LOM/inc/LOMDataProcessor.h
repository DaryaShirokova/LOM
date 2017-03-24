#ifndef LOMDATAPROCESSOR_H
#define LOMDATAPROCESSOR_H

#include "inc/LOMInitParameters.h"
#include "inc/LOMCounters.h"
#include "inc/LOMAmplitudes.h"
#include "inc/LOMHistograms.h"

#include "inc/LOMDataUpdater.h"

#include <QTimer>
#include <QSettings>
#include <QTimer>

//! The model class of the program.
/*!
  This class processes and keeps the data which are stored in FPGA. It contains
  two member oblects representing two types of data: initialization data which
  are used to configure the FPGA and event data which uptates every time in
  operating mode.
  The instance of the class can be in two states: opertating and stopped.
  When operating, it initiates updates of data. When data are updated, it
  calculates the  luminosity. The frequence of updates can be configured.
*/

class LOMDataProcessor : public QObject
{
    Q_OBJECT
private:

    LOMInitParameters initParams; /*!< LOM initialisation data.*/

    LOMCounters counters; /*!< Counters from LOM.*/

    LOMAmplitudes amplitudes; /*!< Amplitudes from LOM.*/

    LOMHistograms hists; /*!< Histograms collected by LOM.*/

    double updateAmplsFreq; /*!< The frequency of amplitudes updates.*/
    double updateCountersFreq; /*!< The frequency of counters updates.*/
    double updateHistsFreq;

    bool isRunning; /*!< The status of data updates.*/

    LOMDataUpdater* updater; /*!< The object which processes updates.*/

    double luminosity; /* The value of luminosity.*/

    //! Registration efficiency determined using the simulation process.
    double registrationEfficiency;

    QTimer* timerAmpls; /* Timer for amplitudes updates.*/
    QTimer* timerCounters; /* Timer for counters updates.*/
    QTimer* timerHists; /* Timer for histograms updates.*/

    bool writeTree;
    int treeSize;
    QString dataDir;
    QString CreateFileName();

    bool writeHist;
    int writeHistFreq;
    QString histDir;
    QTimer* histsToFileTimer;

public:

    //**************************************************************************
    // Constructors/destructors.
    //**************************************************************************

    //! A constructor.
    /*!
     * \param initfileName  the title of the initialization file.
     * \param logfileName   the title of the logfile.
     * \param updater       the object which processes updates.
     */
    LOMDataProcessor(LOMDataUpdater* updater);

    //! A destructor.
    ~LOMDataProcessor();

    //**************************************************************************
    // Lifecycle of the data updates.
    //**************************************************************************

    /*!
     * \brief Start
     */
    void Start();

    /*!
     * \brief Stop
     */
    void Stop();

    //! Calculate the luminosy using bhabha events number and registration efficiency.
    /*!
     * \brief CalculateLuminosity
     * \return  luminosity.
     */
    double CalculateLuminosity();

    void Save(QSettings *settings);
    void Load(QSettings *settings);
    //**************************************************************************
    // Signals/slots.
    //**************************************************************************
public slots:

    /*!
     * \brief Update    update event data.
     */
    void UpdateAmplitudes();
    void UpdateCounters();
    void UpdateHistograms();
    void HistsToFile();
    //**************************************************************************
    // Getters/Setters.
    //**************************************************************************


public:
    void SetWriteTree(bool writeTree) { this->writeTree = writeTree; emit TreeSettingsUpdated();}
    bool GetWriteTree() {return writeTree;}
    void SetDataDir(QString dataDir) {this->dataDir = dataDir; emit TreeSettingsUpdated();}
    QString GetDataDir() {return dataDir;}
    int GetTreeSize() {return treeSize;}
    void SetTreeSize(int treeSize) {this->treeSize = treeSize; emit TreeSettingsUpdated();}

    void SetWriteHist(bool writeHist) {
        this->writeHist = writeHist;
        if(histsToFileTimer == NULL)
            return;
        if(isRunning && writeHist)
            histsToFileTimer->start(writeHistFreq * 60 * 1000);
        else if(histsToFileTimer->isActive())
            histsToFileTimer->stop();
        emit HistSettingsUpdated();
    }
    bool GetWriteHist() {return writeHist;}
    void SetHistDir(QString histDir) {this->histDir = histDir; emit HistSettingsUpdated();}
    QString GetHistDir() {return histDir;}
    int GetWriteHistFreq() {return writeHistFreq;}
    void SetWriteHistFreq(int writeHistFreq) {this->writeHistFreq = writeHistFreq; emit HistSettingsUpdated();}

    /*!
     * \brief IsRunning check the status of updates.
     * \return  the status of updates (true if updating).
     */
    bool IsRunning() {return isRunning;}

    /*!
     * \brief GetInitParameters getter.
     * \return  init params.
     */
    LOMInitParameters& GetInitParameters() {return initParams;}

    //! Update init parameters.
    /*!
    * \param thresholdFE forward endcap hit threshlold.
    * \param thresholdBE backward endcap hit threshlold.
    * \param coincidenceDurationThreshold the minimal coincidenc interval.
    * \param backgroundThreshold quality signal detection threshold.
    * \return statusof updates.
    */
    bool SetInitParameters(double thresholdFE, double thresholdBE,
                            int coincidenceDurationThreshold,
                            int hitThreshold, int bufSize);

    //! Get init parameters which are currently set in the lom.
    /*!
    * \return status of the operation.
    */
    bool LoadInitParameters();

    /*!
     * \brief GetCounters getter.
     * \return  reference to counters.
     */
    LOMCounters& GetCounters() {return counters;}

    /*!
     * \brief GetAmplitudes getter.
     * \return  reference to amplitudes.
     */
    LOMAmplitudes& GetAmplitudes() {return amplitudes;}

    LOMHistograms* GetHistograms() {return &hists;}
    /*!
     * \brief SetUpdateAmplsFreq setter.
     * \param freq    update amplitudes frequence (msec).
     */
    void SetUpdateAmplsFreq(double freq) {this->updateAmplsFreq = freq; emit TimingUpdated();}

    void SetUpdateCountersFreq(double freq) {this->updateCountersFreq = freq; emit TimingUpdated();}

    void SetUpdateHistsFreq(double freq) {this->updateHistsFreq = freq; emit TimingUpdated();}

    void SetFrequencies(double fCounters, double fAmpls, double fHist) {
        this->updateCountersFreq = fCounters;
        this->updateAmplsFreq = fAmpls;
        this->updateHistsFreq = fHist;
    }

    double GetUpdateCountersFreq() {return updateCountersFreq;}
    double GetUpdateAmplsFreq() {return updateAmplsFreq;}
    double GetUpdateHistsFreq() {return updateHistsFreq;}

    LOMDataUpdater* GetDataUpdater() {return updater;}

signals:
    void AmplitudesUpdated();
    void CountersUpdated();
    void HistsUpdated();
    void TimingUpdated();
    void TreeSettingsUpdated();
    void HistSettingsUpdated();
};

#endif // LOMDATAPROCESSOR_H
