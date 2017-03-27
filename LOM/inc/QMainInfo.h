#ifndef QMAININFO_H
#define QMAININFO_H

#include <QTabWidget>

namespace Ui {
class QMainInfo;
}

class QMainInfo : public QTabWidget
{
    Q_OBJECT

public:
    explicit QMainInfo(QWidget *parent = 0);
    ~QMainInfo();

private:
    Ui::QMainInfo *ui;
};

#endif // QMAININFO_H
