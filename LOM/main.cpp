#include "inc/LOMView.h"
#include "inc/LOMDataProcessor.h"
#include "inc/LOMDataUpdater.h"
#include "inc/Logger.h"

#include <QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LOMView w;
    LOMDataUpdater* updater = new LOMDataUpdater();
    LOMDataProcessor* model = new LOMDataProcessor(updater);
    w.SetModel(model);
    Logger::AddListener(&w);
    w.show();

    return a.exec();
}
