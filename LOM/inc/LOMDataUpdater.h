#ifndef LOMDATAUPDATER_H
#define LOMDATAUPDATER_H

#include <inc/AbstractTransporter.h>
#include <inc/LOMInitParameters.h>
#include <inc/LOMEventData.h>

#include <map>
#include <string>

//#include "root/TColor.h"

//! A class for connetion establishment.
/*!
  A class which knows register map of the FPGA and the data structure.
*/
class LOMDataUpdater
{
private:

    AbstractTransporter *transporter; /*!< Trasport protocol implementation.*/
    std::map<std::string, int> regMap; /*!< IP address of the destination point.*/

public:
    //**************************************************************************
    // Constructor/destructor.
    //**************************************************************************

    //! A default constructor.
    LOMDataUpdater();

    //! A constructor.
    /*!
     * \brief LOMDataUpdater
     * \param config        configuration file.
     * \param transporter   transport protocol.
     */
    LOMDataUpdater(std::string config, AbstractTransporter *transporter);

    //! A destructor.
    ~LOMDataUpdater();

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
