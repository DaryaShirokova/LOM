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

public slots:
    void Connected();
    void ReceiveData();


signals:
    void SigConnected();
    void SigDisconnected();
};

#endif // TCPTRANSPORTER_H
