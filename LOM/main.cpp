#include "inc/LOMView.h"
#include "inc/LOMDataProcessor.h"
#include "inc/LOMDataUpdater.h"
#include "inc/TCPTransporter.h"
#include "inc/Logger.h"

#include <QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LOMView w;
    Logger::AddListener(&w);

    TCPTransporter* transporter = new TCPTransporter();
    transporter->SetHostAddress(QHostAddress::LocalHost, 5683);
    QObject::connect(transporter, SIGNAL(SigConnected()), &w, SLOT(Connected()));
    QObject::connect(transporter, SIGNAL(SigDisconnected()), &w, SLOT(Disconnected()));

    LOMDataUpdater* updater = new LOMDataUpdater(transporter);
    LOMDataProcessor* model = new LOMDataProcessor(updater);
    w.SetModel(model);

    transporter->ConnectToHost();


    w.show();
    return a.exec();
}
