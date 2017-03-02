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

    virtual void SetHostAddress(QHostAddress ipaddr, int port) = 0;
    virtual bool ConnectToHost() = 0;
    virtual bool CloseConnection() = 0;
    void SetCheckStatus(QByteArray mes, QByteArray ans) {
        this->checkStatusMessage = mes;
        this->checkStatusAnswer = ans;
    }

protected:
    QHostAddress ip;
    int port;
    QByteArray checkStatusMessage;
    QByteArray checkStatusAnswer;
signals:
    void DataReady(QByteArray data);

};

#endif // ABSTRACTTRANSPORTER_H
