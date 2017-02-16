#ifndef LOMVIEW_H
#define LOMVIEW_H

#include <QMainWindow>

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

    void SetModel(LOMDataProcessor* model) {this->model = model;}

private:
    Ui::LOMView *ui;
    LOMDataProcessor* model;

    double ymaxFWD;
    double ymaxBWD;

public slots:
    void UpdateThresholds();
    void UpdateSettings();
    void StartUpdates();
    void StopUpdates();
    void UpdatePlots();
    void ChangePlottersMode();

};

#endif // LOMVIEW_H
