#ifndef LOMMainWindow_H
#define LOMMainWindow_H

#include <QMainWindow>
#include <QTime>

#include "inc/LogListener.h"
#include "inc/Logger.h"
#include "inc/QMenuConfig.h"
#include "inc/QHistPoolWidget.h"

namespace Ui {
class LOMMainWindow;
}

class LOMDataProcessor;


//! View class.
/*!
  This class represents the graphical interface of the program for communication
  with users.
*/
class LOMMainWindow : public QMainWindow, public LogListener {
    Q_OBJECT
public:
    //! Constructor.
    explicit LOMMainWindow(QWidget *parent = 0);

    //! Destructor.
    ~LOMMainWindow();

    /*!
     * \brief SetModel  set model and update threshold.
     * \param model     model
     */
    void SetModel(LOMDataProcessor* model);

    /*!
     * \brief handleMessage handle logger event.
     * \param message       message.
     */
    void handleMessage(QString message);

    /*!
     * \brief Load  load configuration from file.
     * \param filename  cofig file.
     */
    void Load(QString filename);

    /*!
     * \brief Save  save configuration to file.
     * \param filename  cofig file.
     */
    void Save(QString filename);

private:
    Ui::LOMMainWindow *ui; /*!<  User interface.*/
    LOMDataProcessor* model; /*!<  Model.*/

    bool advancedMode; /*!< Advanced mode for opening network configuration. */

    //! Plotters settings.
    double ymaxFWD; /*!< Max value of fwd ampl (for plotter).*/
    double ymaxBWD; /*!< Max value of bwd ampl (for plotter).*/
    int x0; /*!< Left value of x axis (for plotter).*/
    int x1; /*!< Right value of x axis (for plotter).*/

    //! Logger settings.
    int logDepth; /*!< Number of messages to show in log text browser.*/
    Logger::LogLevel logtype; /*!< Detalization of logging.*/

    //! Counters updates info.
    long lastCountersUpdate; /*!< How much time has passed since last update. */
    QTime time; /*!< Timer to update counters. */

    long lastPlotsUpdate; /*!< How much time has passed since last plots update. */
    QTime timePlots;  /*!< Timer to update plots. */

    QVector<double> luminosityValues; /*!< values of luminosities. */
    QVector<double> bkgValues; /*!< values of background. */
    QVector<double> timeValues; /*!< time values. */
    double lumAndBkgUpdateFreq;
    int pointsPerPlot;
    //QVector<double> luminosityErrorValues; /*!<

    QHistPoolWidget * widgetHists; /*!< Widget in tab2 to show histograms. */

    /*!
     * \brief SetTips   Set tips to GUI elements.
     */
    void SetTips();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

public slots:
    // Update model.
    /*!
     * \brief UpdateThresholds Set the values of thresholds to model.
     */
    void UpdateThresholds();
    /*!
     * \brief UpdateSettings Update timing settings.
     */
    void UpdateSettings();


    // Start/stop.
    /*!
     * \brief StartUpdates  Begin reading data from FPGA.
     */
    void StartUpdates();
    /*!
     * \brief StopUpdates   Stop reading data from FPGA.
     */
    void StopUpdates();


    // GUI Updates.
    /*!
     * \brief UpdateCounters    Update counters.
     */
    void UpdateCounters();

    /*!
     * \brief UpdateLuminosityAndBkgPlots   Update luminosity and bkg plots.
     */
    void UpdateLuminosityAndBkgPlots();

    /*!
     * \brief UpdateTiming      update timing.
     */
    void UpdateTiming();
    /*!
     * \brief UpdatePlots   Update plotters.
     */
    void UpdatePlots();
    /*!
     * \brief InitThresholds    Update init thresholds.
     */
    void InitThresholds();
    /*!
     * \brief UpdateEndcapsWiggets   Update endcaps widgets.
     */
    void UpdateEndcapsWiggets();
    /*!
     * \brief ChangePlottersSettings    Change plotters settings.
     */
    void ChangePlottersSettings();

    /*!
     * \brief UpdateLumBkgPlottersSettings
     */
    void UpdateLumBkgPlottersSettings();

    /*!
     * \brief ChangeLuminosityPlottersSettings  Change luminosity plotters settins.
     */
    void ChangeLuminosityPlottersSettings(double x0);

    /*!
     * \brief ChangePlottersMode    Change mode: max ampl sector to fixed sector.
     * \param x0    starting time.
     */
    void ChangePlottersMode();


    // Logger updates.
    /*!
     * \brief SetLogType    Set loggig detalization.
     * \param str   Lpg type.
     */
    void SetLogType(QString str);
    /*!
     * \brief SetLogDepth   Set logging depth.
     * \param depth         the number of lines in the text window.
     */
    void SetLogDepth(int depth);
    /*!
     * \brief SetLogToFile  Switch on/of logging to file.
     * \param val   on/off logging to file.
     */
    void SetLogToFile(bool val);


    // Networking signals.
    /*!
     * \brief Connected     connected to host.
     */
    void Connected();
    /*!
     * \brief Disconnected  disconnected from host.
     */
    void Disconnected();
    /*!
     * \brief Reconnect reconnect to the host.
     */
    void Reconnect();
    /*!
     * \brief OpenNetworkSettings   open network menu.
     */
    void OpenNetworkSettings();


    // Configuration.
    /*!
     * \brief EditConfigurations    edit current configuration.
     */
    void EditConfigurations();

    /*!
     * \brief OnApplyCongiguration  Apply configuration.
     * \param config    user input from QMenuConfig window.
     */
    void OnApplyCongiguration(QMenuConfig* config);
    //void OnSaveConfiguration();
    //void LoadConfigurations();


    // LOM init parameters.
    /*!
     * \brief SetThresholdStatus    Set the status of thresholds (set/unset).
     * \param val   status.
     */
    void SetThresholdStatus(bool val);
    /*!
     * \brief GetLOMInitParams  Get init parameters from LOM.
     */
    void GetLOMInitParams();
    /*!
     * \brief LoadLOMInitParams Load parameters from file.
     */
    void LoadLOMInitParams();
    /*!
     * \brief LoadLOMInitParams Save parameters to file.
     */
    void SaveLOMInitParams();

    // Exit
    /*!
     * \brief OnExit    Proceed exit event.
     */
    void OnExit();

    // Help
    /*!
     * \brief About Display brief information about the app.
     */
    void About();

    /*!
     * \brief About Display brief information about Qt.
     */
    void AboutQt();
};

#endif // LOMMainWindow_H
