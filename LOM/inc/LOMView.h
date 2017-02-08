#ifndef LOMVIEW_H
#define LOMVIEW_H

#include <QMainWindow>
#include <inc/LOMDataProcessor.h>

namespace Ui {
class LOMView;
}

class LOMView : public QMainWindow
{
    Q_OBJECT

public:
    explicit LOMView(QWidget *parent = 0);
    ~LOMView();

private:
    Ui::LOMView *ui;
    //LOMDataProcessor model;

public slots:
    void updateAmplFWD();
};

#endif // LOMVIEW_H
