#ifndef ABSTRACTTRANSPORTER_H
#define ABSTRACTTRANSPORTER_H

#include <QString>
#include <QObject>


//! A class for data transmitting and receiving.
/*!
  An abstract class which provides an interface for establishing connection
  and data transporting.
*/
class AbstractTransporter :  public QObject
{
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

signals:
    void DataReady(QByteArray data);

};

#endif // ABSTRACTTRANSPORTER_H
