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
    //QHostAddress ipaddr; /*!< IP address of the destination point.*/
   // int port;       /*!< Port number of the destination point.*/
    QTcpSocket* socket; /* Socket for communication with server. */

public:
    TCPTransporter();
    void SetHostAddress(QHostAddress ipaddr, int port) override;
    bool ConnectToHost() override;
    bool CloseConnection() override;
    bool SetReadMode(int msec) override;
    bool WriteData(QByteArray data, qint32 size) override;
    QByteArray ReadData() override;
    bool IsConnected();

private:
    bool connected;
    QString AddrToString();
    QByteArray inputBuffer;
    QTimer* timer;

public slots:
    void Connected();
    void Disconnected();
    void ReceiveData();
    void CheckConnection();

signals:
    void SigConnected();
    void SigDisconnected();
};

#endif // TCPTRANSPORTER_H
