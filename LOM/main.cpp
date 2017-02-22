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
    std::cout << "Create updater." << std::endl;
    LOMDataUpdater* updater = new LOMDataUpdater();
    std::cout << "Create data processor." << std::endl;
    LOMDataProcessor* model = new LOMDataProcessor("initfile", "logfile", updater);
    w.SetModel(model);
    //Logger::instance();
    Logger::AddListener(&w);
    w.show();

    return a.exec();
}
