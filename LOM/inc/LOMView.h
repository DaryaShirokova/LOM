#ifndef LOMVIEW_H
#define LOMVIEW_H

#include <QMainWindow>
#include <QTime>

#include "inc/LogListener.h"
#include "inc/Logger.h"
#include "inc/Constants.h"
#include "inc/MenuConfig.h"


namespace Ui {
class LOMView;
}

class LOMDataProcessor;


class UIConfig
{
    QMap<QString, QString> params;
public:
    bool load()
    {
       // return load(CONFIG_PATH + DEFAULT_CONF);
    }

    bool load(QString file)
    {

    }

    bool save(QString file)
    {

    }
    QString GetParam(QString key)
    {
        return params.value(key);
    }

    void SetParam(QString key, QString value)
    {
        params.insert(key, value);
    }
};

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
    void SetModel(LOMDataProcessor* model);

    /*!
     * \brief handleMessage handle logger event.
     * \param message       message.
     */
    void handleMessage(QString message);


    void Save(QString filename, MenuConfig *config);
    void Load(QString filename);

    void InitFromFile(QString filename);
private:
    Ui::LOMView *ui; /* User interface.*/
    LOMDataProcessor* model; /* Model.*/

    double ymaxFWD; /* Max value of fwd ampl (for plotter).*/
    double ymaxBWD; /* Max value of bwd ampl (for plotter).*/
    int x0; /* Left value of x axis (for plotter).*/
    int x1; /* Right value of x axis (for plotter).*/

    int logDepth; /* Number of messages to show in log text browser.*/
    Logger::LogLevel logtype; /* Detalization of logging.*/

    bool advancedMode;
    long lastCountersUpdate;
    QTime time;


public slots:
    void UpdateThresholds(); /* Set the values of thresholds to model. */
    void UpdateSettings(); /* Update timing settings. */
    void UpdateCounters();

    void StartUpdates(); /* Begin reading data from FPGA. */
    void StopUpdates(); /* Stop reading data from FPGA. */

    void UpdatePlots(); /* Update plotters. */
    void UpdateEndcapsWiggets(); /* Update endcaps widgets. */
    void UpdateAll();   /* Call several update slots (plotters, endcaps). */
    void ChangePlottersSettings(); /* Change plotters settins. */
    void ChangePlottersMode(); /* Change mode: max ampl sector to fixed sector. */

    void SetLogType(QString str); /* Set loggig detalization. */
    void SetLogDepth(int depth); /* Set logging depth. */
    void SetLogToFile(bool val); /* Switch on/of logging to file. */

    void Connected();
    void Disconnected();

    void OpenNetworkSettings();
    void LoadConfigurations();
    void EditConfigurations();
    void Reconnect();
    void OnApplyCongiguration(MenuConfig* config);
    void OnSaveConfiguration(MenuConfig* config, QString path);

    void LoadLOMInitParams();
    void SaveLOMInitParams();
    void GetLOMInitParams();
};

#endif // LOMVIEW_H
