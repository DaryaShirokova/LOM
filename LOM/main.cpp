#include "inc/LOMView.h"
#include "inc/LOMDataProcessor.h"
#include "inc/LOMDataUpdater.h"
#include "inc/TCPTransporter.h"
#include "inc/Logger.h"

#include <QApplication>

#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LOMView w;

    Logger::AddListener(&w);
    Logger::SetWriteToFile(false);
    Logger::SetPath(LOG_PATH);


    TCPTransporter* transporter = new TCPTransporter();
    QObject::connect(transporter, SIGNAL(SigConnected()), &w, SLOT(Connected()));
    QObject::connect(transporter, SIGNAL(SigDisconnected()), &w, SLOT(Disconnected()));

    LOMDataUpdater* updater = new LOMDataUpdater(transporter);
    updater->Configure(DEFAULT_NETWORK);
    LOMDataProcessor* model = new LOMDataProcessor(updater);
    w.SetModel(model);

    w.Load(DEFAULT_CONF);
    w.InitFromFile(DEFAULT_PARAM);

    updater->Connect();

    if(sizeof(int) != 4)
        Logger::Log(Logger::LogLevel::ERROR, "Main: the size of int is not 4, "
                                             "data transmitting may be broken.");

    w.show();
    return a.exec();
}
