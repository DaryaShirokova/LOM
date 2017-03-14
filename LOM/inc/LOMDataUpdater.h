#ifndef LOMDATAUPDATER_H
#define LOMDATAUPDATER_H

#include <inc/AbstractTransporter.h>
#include <inc/LOMInitParameters.h>
#include <inc/LOMEventData.h>

#include <QMap>
#include <QTimer>

//! A class for connetion establishment.
/*!
  A class which knows register map of the FPGA and the data structure.
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
    QString ipaddr;
    QTimer* timer;
    int port;

    //! A default constructor.
    LOMDataUpdater() {}

    QByteArray GetAnswer();
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

    QMap<QString, int> GetRegMap() {return regMap;}
    QMap<QString, int> GetMemMap() {return memMap;}
    QString GetIP() {return ipaddr;}
    int GetPort() {return port; }

    void Configure(QMap<QString, int> regMap, QMap<QString, int> memMap);

public slots:
    void CheckConnection();
};

#endif // LOMDATAUPDATER_H
