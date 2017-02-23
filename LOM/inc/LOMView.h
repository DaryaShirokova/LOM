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

//! View class.
/*!
  This class represents the graphical interface of the program for communication
  with users.
  */
class LOMView : public QMainWindow, public LogListener
{
    Q_OBJECT

public:
    //! Constructor.
    explicit LOMView(QWidget *parent = 0);

    //! Destructor.
    ~LOMView();

    /*!
     * \brief SetModel  set model and update threshold.
     * \param model     model
     */
    void SetModel(LOMDataProcessor* model) {this->model = model; UpdateThresholds();}

    /*!
     * \brief handleMessage handle logger event.
     * \param message       message.
     */
    void handleMessage(QString message);

private:
    Ui::LOMView *ui; /* User interface.*/
    LOMDataProcessor* model; /* Model.*/

    int redrawFreq; /* Frequency of picture updating.*/

    double ymaxFWD; /* Max value of fwd ampl (for plotter).*/
    double ymaxBWD; /* Max value of bwd ampl (for plotter).*/
    int x0; /* Left value of x axis (for plotter).*/
    int x1; /* Right value of x axis (for plotter).*/

    int logDepth; /* Number of messages to show in log text browser.*/
    Logger::LogLevel logtype; /* Detalization of logging.*/

    QTimer* plotsUpdateTimer;   /* timer to update plotters */

public slots:
    void UpdateThresholds(); /* Set the values of thresholds to model. */
    void UpdateSettings(); /* Update timing settings. */
    void StartUpdates(); /* Begin reading data from FPGA. */
    void StopUpdates(); /* Stop reading data from FPGA. */
    void UpdatePlots(); /* Update plotters. */
    void UpdateEndcapsWiggets(); /* Update endcaps widgets. */
    void UpdateAll();   /* Call several update slots (plotters, endcaps). */
    void ChangePlottersSettings(); /* Change plotters settins. */
    void ChangePlottersMode(); /* Change mode: max ampl sector to fixed sector. */
    void SetLogType(QString str); /* Set loggig detalization. */
    void SetLogDepth(int depth); /* Set logging depth. */
};

#endif // LOMVIEW_H
