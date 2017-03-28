#ifndef ABSTRACTTRANSPORTER_H
#define ABSTRACTTRANSPORTER_H

#include <QString>
#include <QObject>
#include <QHostAddress>


//! A class for data transmitting and receiving.
/*!
  An abstract class which provides an interface for establishing connection
  and data transporting.
*/
class AbstractTransporter :  public QObject {
    Q_OBJECT
public:
    /*!
     * \brief SetReadMode   prepare for reading data.
     * \param msec          timeout.
     * \return status.
     */
    virtual bool SetReadMode(int msec) = 0;

    /*!
     * \brief SetReadMode   prepare for reading data.
     * \param msec          timeout.
     */
    virtual QByteArray ReadData() = 0;

    /*!
     * \brief WriteData write data to the register.
     * \param data      data to write.
     * \return status of the operation (true means success).
     */
    virtual bool WriteData(QByteArray data, qint32 size) = 0;

    /*!
     * \brief SetHostAddress set the address of the host.
     * \param ipaddr        ip address.
     * \param port         port number.
     */
    virtual void SetHostAddress(QHostAddress ipaddr, int port) = 0;

    /*!
     * \brief ConnectToHost connect to the host.
     * \return status of the operation (true means success).
     */
    virtual bool ConnectToHost() = 0;

    /*!
     * \brief CloseConnection disconnect from the host.
     * \return status of the operation (true means success).
     */
    virtual bool CloseConnection() = 0;

protected:
    QHostAddress ip; /*!< IP address of the host.*/
    int port;   /*!< The port number of the host.*/

};

#endif // ABSTRACTTRANSPORTER_H
