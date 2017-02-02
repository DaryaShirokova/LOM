#ifndef LOMDATAPROCESSOR_H
#define LOMDATAPROCESSOR_H

#include <inc/LOMInitParameters.h>
#include <inc/LOMEventData.h>
#include <inc/LOMDataUpdater.h>
#include <inc/LOMView.h>

#include <string>
#include <fstream>

//! The model class of the programme.
/*!
  This class processes and keeps the data which are stored in FPGA. It contains
  two member oblects representing two types of data: initialization data which
  are used to configure the FPGA and event data which uptates every time in
  operating mode.
  The instance of the class can be in two states: opertating and stopped.
  When operating, it initiates updates of data.When data are updated, it
  calculates the  luminosity. The frequence of updates can be configured.
  It also implements the Subject in Subject/Observer pattern.
*/

class LOMDataProcessor
{

private:

    LOMInitParameters* initParams; /*!< LOM initialisation data.*/
    LOMEventData* event; /*!< Data from LOM.*/

    unsigned int updateFreq; /*!< The frequency of data updates.*/

    // TODO: &
    LOMDataUpdater updater; /*!< The object which processes updates.*/

    double luminosity; /* The value of luminosity.*/

    std::string logfileName; /* The title of the log file.*/
    std::ofstream logfile; /* The log output stream.*/

private:

    //**************************************************************************
    // Internal functions.
    //**************************************************************************

    /*!
     * \brief Update    update event data.
     */
    void Update();

    /*!
     * \brief Log       write log.
     */
    void Log();

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
    LOMDataProcessor(std::string initfileName, std::string logfileName,
                     LOMDataUpdater updater);

    //! A destructor.
    ~LOMDataProcessor();


    //**************************************************************************
    // Subject/observer pattern.
    //**************************************************************************

    /*!
     * \brief AddView   attach an oberver.
     * \param view      observer.
     */
    void AddView(LOMView* view);

    /*!
     * \brief DetachView remove an observer.
     * \param view       observer.
     */
    void DetachView(LOMView* view);

    /*!
     * \brief Notify    notify all observers.
     */
    void Notify();

    //**************************************************************************
    // Lifecycle of the data updates.
    //**************************************************************************

    /*!
     * \brief Initialize
     * \param initfileName
     */
    void Initialize(std::string initfileName);

    /*!
     * \brief Initialize
     * \param thresholdFE
     * \param thresholdBE
     * \param coincidenceDurationThreshold
     * \param backgroundThreshold
     * \param deadTime
     * \param registrationEfficiency
     */
    void Initialize(unsigned int thresholdFE, unsigned int thresholdBE,
               unsigned int coincidenceDurationThreshold,
               unsigned int backgroundThreshold, unsigned int deadTime,
               unsigned int registrationEfficiency);

    /*!
     * \brief Start
     * \param updateFreq
     */
    void Start(unsigned int updateFreq);

    /*!
     * \brief Stop
     */
    void Stop();

    //! Calculate the luminosy using bhabha events number and registration efficiency.
    /*!
     * \brief CalculateLuminosity
     * \return  luminosity
     */
    double CalculateLuminosity();

};

#endif // LOMDATAPROCESSOR_H
