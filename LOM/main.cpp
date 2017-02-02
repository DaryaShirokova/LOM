#include "inc/LOMView.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LOMView w;
    w.show();

    return a.exec();
}
