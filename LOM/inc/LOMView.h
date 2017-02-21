#ifndef LOMVIEW_H
#define LOMVIEW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class LOMView;
}

class LOMDataProcessor;
class LOMView : public QMainWindow
{
    Q_OBJECT

public:
    explicit LOMView(QWidget *parent = 0);
    ~LOMView();

    void SetModel(LOMDataProcessor* model) {this->model = model; UpdateThresholds();}

private:
    Ui::LOMView *ui;
    LOMDataProcessor* model;

    int redrawFreq;
    double ymaxFWD;
    double ymaxBWD;
    int x0;
    int x1;
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
};

#endif // LOMVIEW_H
