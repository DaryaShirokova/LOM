#ifndef TCPTRANSPORTER_H
#define TCPTRANSPORTER_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QString>

#include "AbstractTransporter.h"

class TCPTransporter : public QObject, public AbstractTransporter
{
    Q_OBJECT
private:
    QHostAddress ipaddr; /*!< IP address of the destination point.*/
    int port;       /*!< Port number of the destination point.*/
    QTcpSocket* socket; /* Socket for communication with server. */

public:
    TCPTransporter();
    void SetHostAddress(QHostAddress ipaddr, int port);
    bool ConnectToHost();
    bool CloseConnection();
    bool ReadData(size_t dataSize, int *data) override;
    bool WriteData(QByteArray data, qint64 size) override;
    bool IsConnected();
private:
    QString AddrToString();

public slots:
    void Connected();
    void Disconnected();

signals:
    void SigConnected();
    void SigDisconnected();
};

#endif // TCPTRANSPORTER_H
