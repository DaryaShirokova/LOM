#ifndef LOMDATAUPDATER_H
#define LOMDATAUPDATER_H

#include <inc/AbstractTransporter.h>
#include <inc/LOMInitParameters.h>
#include <inc/LOMEventData.h>

#include <QMap>

//! A class for connetion establishment.
/*!
  A class which knows register map of the FPGA and the data structure.
*/
class LOMDataUpdater// : public QObject
{
   // Q_OBJECT
private:
    //! The LogLevel enum
    //! Detalization of logging.
    // enum InquiryType { NONE, EVENT };

    AbstractTransporter *transporter; /*!< Trasport protocol implementation.*/
    QMap<QString, int> regMap; /*!< The addresses of registers.*/
    QMap<QString, int> memMap; /*!< The memory map. */


    //! A default constructor.
    LOMDataUpdater() {}

public:
    //**************************************************************************
    // Constructor/destructor.
    //**************************************************************************

    //! A constructor.
    /*!
     * \brief LOMDataUpdater
     * \param config        configuration file.
     * \param transporter   transport protocol.
     */
    LOMDataUpdater(AbstractTransporter *transporter);

    //! A destructor.
    ~LOMDataUpdater() {}

    /*!
     * \brief Configure load register settings from config file.
     * \param config    config file path.
     */
    void Configure(QString config);

    /*!
     * \brief WriteInitParameters
     * \param initParameters    initialisation parameters for FPGA.
     * \return  status of data transmition (true if OK).
     */
    bool WriteInitParameters(LOMInitParameters *initParameters);

    /*!
     * \brief ReadEventData
     * \param eventData informatiom about Bhabha event.
     * \return  status of data transmition (true if OK).
     */
    bool ReadEventData(LOMEventData* eventData);

};

#endif // LOMDATAUPDATER_H
