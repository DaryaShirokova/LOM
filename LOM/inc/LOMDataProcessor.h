#ifndef LOMDATAPROCESSOR_H
#define LOMDATAPROCESSOR_H

#include "inc/LOMInitParameters.h"
#include "inc/LOMCounters.h"
#include "inc/LOMAmplitudes.h"
#include "inc/LOMHistograms.h"
#include "inc/LOMDataUpdater.h"

#include <QTimer>
#include <QSettings>

//! The model class of the program.
/*!
  This class processes and keeps the data which are stored in FPGA. It contains
  several members representing data in FPGA: initialization data, amplitudes,
  hisrograms and counters.
  The instance of the class can be in two states: opertating and stopped.
  When operating, it initiates updates of data. When data are updated, it
  emits corresponding signals. The frequency of updates can be configured.
*/

class LOMDataProcessor : public QObject {
    Q_OBJECT
private:
    // LOM data types.
    LOMInitParameters initParams; /*!< LOM initialisation data.*/
    LOMCounters counters; /*!< Counters from LOM.*/
    LOMAmplitudes amplitudes; /*!< Amplitudes from LOM.*/
    LOMHistograms hists; /*!< Histograms collected by LOM.*/

    // Frequencies of updates and timers.
    double updateAmplsFreq; /*!< The frequency of the amplitudes updates.*/
    double updateCountersFreq; /*!< The frequency of counters updates.*/
    double updateHistsFreq; /*!< The frequency of the histograms updates.*/
    QTimer* timerAmpls; /* Timer for amplitudes updates.*/
    QTimer* timerCounters; /* Timer for counters updates.*/
    QTimer* timerHists; /* Timer for histograms updates.*/

    bool isRunning; /*!< The status of data updates.*/
    LOMDataUpdater* updater; /*!< The object which processes updates.*/

    // Writing root tree.
    bool writeTree; /*!< The flag which indicates whether we write root tree or not.*/
    int treeSize; /*!< The maximum size of one tree.*/
    QString dataDir; /*!< Path to save trees.*/

    // Writing hists.
    bool writeHist; /*!< The flag which indicates whether we write histograms tree or not.*/
    int writeHistFreq; /*!< Frequency of writing hists to files. */
    QString histDir; /*!< Path to save hists.*/
    QTimer* histsToFileTimer; /* Timer for writing hists. */

    //! Registration efficiency determined using the simulation process.
    double registrationEfficiency; /*! The efficiency of Bhabha events registration. */
    double luminosity; /*! The value of luminosity.*/

    /*!
     * \brief Create unique file name for tree (run + int).
     * \return unique file name.
     */
    QString CreateFileName(); /*!< Path to save trees.*/
public:

    //**************************************************************************
    // Constructors/destructors.
    //**************************************************************************

    /*!
     * \brief Constructor.
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
     * \brief Start data updating.
     */
    void Start();

    /*!
     * \brief Stop data updating.
     */
    void Stop();


    //**************************************************************************
    // Other.
    //**************************************************************************

    /*!
     * \brief Save current state to the file.
     * \param  settings settings
     */
    void Save(QSettings *settings);

    /*!
     * \brief Load the state from the file.
     * \param  settings settings
     */
    void Load(QSettings *settings);

    //**************************************************************************
    // Updater slots.
    //**************************************************************************
public slots:
    /*!
     * \brief Update amplitudes.
     */
    void UpdateAmplitudes();

    /*!
     * \brief Update counters.
     */
    void UpdateCounters();

    /*!
     * \brief Update histograms.
     */
    void UpdateHistograms();

    /*!
     * \brief Write histograms to file.
     */
    void HistsToFile();


    //**************************************************************************
    // Signals.
    //**************************************************************************
signals:
    /*!
     * \brief Signal indicating amplitudes updates.
     */
    void AmplitudesUpdated();

    /*!
     * \brief Signal indicating counters updates.
     */
    void CountersUpdated();

    /*!
     * \brief Signal indicating histograms updates.
     */
    void HistsUpdated();

    /*!
     * \brief Signal indicating timing updates.
     */
    void TimingUpdated();

    /*!
     * \brief Signal indicating writing tree settings updates.
     */
    void TreeSettingsUpdated();

    /*!
     * \brief Signal indicating writing histograms settings updates.
     */
    void HistSettingsUpdated();

public:
    //**************************************************************************
    // Getters/Setters.
    //**************************************************************************

    void SetWriteTree(bool writeTree) { this->writeTree = writeTree;
                                        emit TreeSettingsUpdated();}
    bool GetWriteTree() {return writeTree;}
    void SetDataDir(QString dataDir) {this->dataDir = dataDir;
                                      emit TreeSettingsUpdated();}
    QString GetDataDir() {return dataDir;}
    int GetTreeSize() {return treeSize;}
    void SetTreeSize(int treeSize) {this->treeSize = treeSize;
                                    emit TreeSettingsUpdated();}

    void SetWriteHist(bool writeHist);
    bool GetWriteHist() {return writeHist;}
    void SetHistDir(QString histDir) {this->histDir = histDir;
                                      emit HistSettingsUpdated();}
    QString GetHistDir() {return histDir;}
    int GetWriteHistFreq() {return writeHistFreq;}
    void SetWriteHistFreq(int writeHistFreq) {this->writeHistFreq = writeHistFreq;
                                              emit HistSettingsUpdated();}

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
    void SetUpdateAmplsFreq(double freq) {this->updateAmplsFreq = freq;
                                          emit TimingUpdated();}

    void SetUpdateCountersFreq(double freq) {this->updateCountersFreq = freq;
                                             emit TimingUpdated();}

    void SetUpdateHistsFreq(double freq) {this->updateHistsFreq = freq;
                                          emit TimingUpdated();}

    void SetFrequencies(double fCounters, double fAmpls, double fHist) {
        this->updateCountersFreq = fCounters;
        this->updateAmplsFreq = fAmpls;
        this->updateHistsFreq = fHist;
    }

    double GetUpdateCountersFreq() {return updateCountersFreq;}
    double GetUpdateAmplsFreq() {return updateAmplsFreq;}
    double GetUpdateHistsFreq() {return updateHistsFreq;}

    LOMDataUpdater* GetDataUpdater() {return updater;}




};

#endif // LOMDATAPROCESSOR_H
