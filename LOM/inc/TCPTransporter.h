#ifndef TCPTRANSPORTER_H
#define TCPTRANSPORTER_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
#include <QTimer>

#include "AbstractTransporter.h"

class TCPTransporter : public AbstractTransporter
{
    Q_OBJECT
private:
    QTcpSocket* socket; /*!< Socket. */

public:
    /*!
     * \brief TCPTransporter    Constructor.
     */
    TCPTransporter();

    //**************************************************************************
    //* Parent functions.
    //**************************************************************************
    void SetHostAddress(QHostAddress ipaddr, int port) override;
    bool ConnectToHost() override;
    bool CloseConnection() override;
    bool SetReadMode(int msec) override;
    bool WriteData(QByteArray data, qint32 size) override;
    QByteArray ReadData() override;

private:
    bool connected; /*!< Status of connection. */
    QByteArray inputBuffer; /*!< Input data buffer. */

    /*!
     * \brief AddrToString  Convert address and port to string.
     * \return  address in QString format.
     */
    QString AddrToString();

public slots:
    /*!
     * \brief Connected Connected to host.
     */
    void Connected();

    /*!
     * \brief ReceiveData   Data has been received.
     */
    void ReceiveData();


signals:
    /*!
     * \brief SigConnected  Connected to host.
     */
    void SigConnected();

    /*!
     * \brief SigDisconnected Disconnected from host.
     */
    void SigDisconnected();
};

#endif // TCPTRANSPORTER_H
