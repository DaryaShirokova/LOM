#include "inc/TCPTransporter.h"
#include "inc/Logger.h"

#include <QDebug>

TCPTransporter::TCPTransporter()
{
    socket = new QTcpSocket(this);
    connected = false;

    connect(socket, SIGNAL(connected()),this, SLOT(Connected()));
    //connect(socket, SIGNAL(disconnected()),this, SLOT(Disconnected()));

    connect(socket, SIGNAL(readyRead()), SLOT(ReceiveData()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(CheckConnection()));
}

void TCPTransporter::CheckConnection()
{
    socket->write(checkStatusMessage);
    socket->flush();
    if(SetReadMode(1000))
    {
        QByteArray ans = ReadData();
        if(!(ans.size() == checkStatusAnswer.size() && ans == checkStatusAnswer))
            Disconnected();
    }
    else Disconnected();
}

void TCPTransporter::SetHostAddress(QHostAddress ipaddr, int port)
{
    this->ip = ipaddr;
    this->port = port;
}

QString TCPTransporter::AddrToString()
{
    return ip.toString() + "; port " +  QString::number(port) + ". ";
}

bool TCPTransporter::ConnectToHost()
{
    if(connected)
    {
        Logger::Log(Logger::LogLevel::INFO, "Trying to reconnect while already connected.");
        return true;
    }
    socket->connectToHost(ip, port);
    bool conEstablished = socket->waitForConnected(10000);
    if(!conEstablished)
    {
        Logger::Log(Logger::LogLevel::ERROR, "Can't connect to LOM: " +
                        AddrToString() + socket->errorString());
        emit SigDisconnected();
        return false;
    }
    return true;
}

bool TCPTransporter::CloseConnection()
{
    if(socket->isOpen())
        socket->close();
    return true;
}

void TCPTransporter::Connected()
{
    connected = true;
    timer->start(3000);
    Logger::Log(Logger::LogLevel::INFO, "Connected to LOM:" + AddrToString());
    emit SigConnected();
}

void TCPTransporter::Disconnected()
{
    timer->stop();
    connected = false;
    socket->close();
    Logger::Log(Logger::LogLevel::ERROR, "Disconnected from LOM:" + AddrToString()
                + socket->errorString());
    emit SigDisconnected();
}

bool TCPTransporter::SetReadMode(int msec)
{
    socket->waitForReadyRead(msec);
}

void TCPTransporter::ReceiveData()
{
    inputBuffer = socket->readAll();
    Logger::Log(Logger::LogLevel::DEBUG,  "Received " +
                QString::number(inputBuffer.size()) + " byte.");
    emit DataReady(inputBuffer);
}

QByteArray TCPTransporter::ReadData()
{
    return inputBuffer;
}

bool TCPTransporter::WriteData(QByteArray data, qint32 size)
{
    Logger::Log(Logger::LogLevel::DEBUG, "TCPTransporter: Start writing data.");
    if(!socket->isOpen())
    {
        Logger::Log(Logger::LogLevel::ERROR, "TCPTransporter: Trying to write "
                                             "data, but the connection is closed."
                                             " Reconnecting...");
        if(!ConnectToHost())
        {
            Logger::Log(Logger::LogLevel::ERROR, "TCPTransporter: Writing data "
                                                 "has been terminated, "
                                                 "please check the connection.");
            return false;
        }
    }

    socket->write(data);
    if(!socket->waitForBytesWritten(10000))
    {
        Logger::Log(Logger::LogLevel::ERROR, "TCPTransporter: Failed to write data. "
                    + socket->errorString());
        return false;
    }

    Logger::Log(Logger::LogLevel::DEBUG, "TCPTransporter: Writing data has been "
                                         "finished successfully.");
    return true;
}


