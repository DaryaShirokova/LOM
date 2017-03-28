#include "inc/TCPTransporter.h"
#include "inc/Logger.h"
#include "inc/Constants.h"

TCPTransporter::TCPTransporter() {
    socket = new QTcpSocket(this);
    connected = false;

    connect(socket, SIGNAL(connected()),this, SLOT(Connected()));
    connect(socket, SIGNAL(readyRead()), SLOT(ReceiveData()));

}


void TCPTransporter::SetHostAddress(QHostAddress ipaddr, int port) {
    this->ip = ipaddr;
    this->port = port;
}

QString TCPTransporter::AddrToString() {
    return ip.toString() + "; port " +  QString::number(port) + ". ";
}

bool TCPTransporter::ConnectToHost() {
    if(connected) {
        Logger::Log(Logger::LogLevel::INFO, "Trying to reconnect while already connected.");
        return true;
    }
    socket->connectToHost(ip, port);
    bool conEstablished = socket->waitForConnected(10000);
    if(!conEstablished) {
        Logger::Log(Logger::LogLevel::ERROR, "Can't connect to LOM: " +
                        AddrToString() + socket->errorString());
        emit SigDisconnected();
        return false;
    }
    return true;
}

bool TCPTransporter::CloseConnection() {
    if(socket->isOpen())
        socket->close();
    connected = false;
    Logger::Log(Logger::LogLevel::ERROR, "Disconnected from LOM:" + AddrToString()
                + socket->errorString());
    emit SigDisconnected();
    return true;
}

void TCPTransporter::Connected() {
    connected = true;
    Logger::Log(Logger::LogLevel::INFO, "Connected to LOM:" + AddrToString());
    emit SigConnected();
}


bool TCPTransporter::SetReadMode(int msec) {
    return socket->waitForReadyRead(msec);
}

void TCPTransporter::ReceiveData() {
    inputBuffer = socket->readAll();
    Logger::Log(Logger::LogLevel::DEBUG,  "Received " +
                QString::number(inputBuffer.size()) + " bytes.");
}

QByteArray TCPTransporter::ReadData() {
    return inputBuffer;
}

bool TCPTransporter::WriteData(QByteArray data, qint32 size) {

    Logger::Log(Logger::LogLevel::DEBUG, "TCPTransporter: Start writing data.");
    if(!connected) {
        Logger::Log(Logger::LogLevel::ERROR, "TCPTransporter: Trying to write "
                                             "data, but the connection is closed."
                                             " Reconnecting...");
        if(!ConnectToHost()) {
            Logger::Log(Logger::LogLevel::ERROR, "TCPTransporter: Writing data "
                                                 "has been terminated, "
                                                 "please check the connection.");
            return false;
        }
    }

    socket->write(data, size);

    if(!socket->waitForBytesWritten(WRITE_TIMEOUT)) {
        Logger::Log(Logger::LogLevel::ERROR, "TCPTransporter: Failed to write data. "
                    + socket->errorString());
        return false;
    }

    Logger::Log(Logger::LogLevel::DEBUG, "TCPTransporter: Writing data has been "
                                         "finished successfully.");
    return true;
}


