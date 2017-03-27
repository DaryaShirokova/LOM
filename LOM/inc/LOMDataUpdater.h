#ifndef LOMDATAUPDATER_H
#define LOMDATAUPDATER_H

#include "inc/AbstractTransporter.h"
#include "inc/LOMAmplitudes.h"
#include "inc/LOMInitParameters.h"
#include "inc/LOMCounters.h"
#include "inc/LOMHistograms.h"

#include <QMap>
#include <QTimer>

//! A class for connetion establishment and data transmission.
/*!
  A class which knows register map and memory map of the FPGA and the data structure.
*/
class LOMDataUpdater : public QObject
{
    Q_OBJECT
private:
    //! The LogLevel enum
    //! Detalization of logging.
    // enum InquiryType { NONE, EVENT };

    AbstractTransporter *transporter; /*!< Trasport protocol implementation.*/
    QMap<QString, int> regMap; /*!< The addresses of registers.*/
    QMap<QString, int> memMap; /*!< The memory map. */
    QString ipaddr; /* IP of the LOM. */
    int port;       /* Port number. */
    QTimer* timer;  /* Timer for checking the connection status. */


    /*!
     * \brief Constructor.
     */
    LOMDataUpdater() {}

    /*!
     * \brief Get an answer to inquiry from the transporter.
     * \return answer in form of byte array.
     */
    QByteArray GetAnswer();

public:
    //**************************************************************************
    // Constructor/destructor.
    //**************************************************************************

    /*!
     * \brief Constructor.
     * \param config        configuration file.
     * \param transporter   transport protocol.
     */
    LOMDataUpdater(AbstractTransporter *transporter);

    /*!
     * \brief Destructor.
     */
    ~LOMDataUpdater() {}

    //**************************************************************************
    // Connection and data transmission functions.
    //**************************************************************************

    /*!
     * \brief Configure load register settings from config file.
     * \param config    config file path.
     */
    bool Configure(QString config);
    /*!
     * \brief Connect connect to the host.
     * \return true if connected.
     */
    bool Connect();

    /*!
     * \brief Disconnect disconnect from the host.
     * \return true if disconnected.
     */
    bool Disconnect();

    /*!
     * \brief Write init parameters.
     * \param initParameters    initialisation parameters for FPGA.
     * \return  status of data transmission (true if OK).
     */
    bool WriteInitParameters(LOMInitParameters *initParameters);

    /*!
     * \brief Read init parameters.
     * \param initParameters    initialisation parameters for FPGA.
     * \return  status of data transmission (true if OK).
     */
    bool ReadInitParameters(LOMInitParameters *initParameters);

    /*!
     * \brief ReadAmplitudes
     * \param [out] amplitudes amplitudes in the calorimeter sectors.
     * \return  status of data transmission (true if OK).
     */
    bool ReadAmplitudes(LOMAmplitudes* amplitudes, int bufSize);

    /*!
     * \brief ReadCounters
     * \param [out] counters from LOM registers.
     * \return  status of data transmission (true if OK).
     */
    bool ReadCounters(LOMCounters *counters);

    //**************************************************************************
    // Getters/setters.
    //**************************************************************************

    bool ReadHists(LOMHistograms* hists);
    QMap<QString, int> GetRegMap() {return regMap;}
    QMap<QString, int> GetMemMap() {return memMap;}
    QString GetIP() {return ipaddr;}
    int GetPort() {return port; }



public slots:
    void CheckConnection();
};

#endif // LOMDATAUPDATER_H
