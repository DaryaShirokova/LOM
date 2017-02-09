#include "inc/LOMView.h"
#include "inc/LOMDataProcessor.h"
#include "inc/LOMDataUpdater.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LOMView w;
    LOMDataUpdater updater;
    LOMDataProcessor* model = new LOMDataProcessor("initfile", "logfile", updater);
    w.SetModel(model);
    w.show();

    return a.exec();
}
