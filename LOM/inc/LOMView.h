#ifndef LOMVIEW_H
#define LOMVIEW_H

#include <QMainWindow>
#include <QTimer>
#include "inc/LogListener.h"
#include "inc/Logger.h"

namespace Ui {
class LOMView;
}

class LOMDataProcessor;
class LOMView : public QMainWindow, public LogListener
{
    Q_OBJECT

public:
    explicit LOMView(QWidget *parent = 0);
    ~LOMView();

    void SetModel(LOMDataProcessor* model) {this->model = model; UpdateThresholds();}
    void handleMessage(QString message);

private:
    Ui::LOMView *ui;
    LOMDataProcessor* model;

    int redrawFreq;
    double ymaxFWD;
    double ymaxBWD;
    int x0;
    int x1;
    int logDepth;
    Logger::LogLevel logtype;
    QTimer* plotsUpdateTimer;

public slots:
    void UpdateThresholds();
    void UpdateSettings();
    void StartUpdates();
    void StopUpdates();
    void UpdateAll();
    void ChangePlottersSettings();
    void UpdatePlots();
    void ChangePlottersMode();
    void UpdateEndcapsWiggets();
    void SetLogType(QString str);
    void SetLogDepth(int depth);
};

#endif // LOMVIEW_H
