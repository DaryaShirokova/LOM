#ifndef QMenuConfig_H
#define QMenuConfig_H

#include <QDialog>

namespace Ui {
class QMenuConfig;
}

class QMenuConfig : public QDialog
{
    Q_OBJECT
private:
    Ui::QMenuConfig *ui; /*!< GUI. */

public:
    /*!
     * \brief QMenuConfig   Constructor.
     * \param parent        Parent widget.
     */
    explicit QMenuConfig(QWidget* parent = 0);

    /*!
     * Destructor.
     */
    ~QMenuConfig();

    //**************************************************************************
    //  Getters/Setters.
    //**************************************************************************
    QString GetDataDir();
    void SetDataDir(QString dataDir);
    QString GetLogDir();
    void SetLogDir(QString logDir);
    int GetRootFileSize();
    void SetRootFileSize(int size);
    bool IfWriteFile();
    void SetWriteFile(bool writeFile);
    bool IsAdvanced();
    void SetAdvanced(bool advanced);
    int GetHistRecordFreq();
    void SetHistRecordFreq(int freq);
    bool IfWriteHist();
    void SetWriteHist(bool writeHist);
    void SetHistDir(QString histDir);
    QString GetHistDir();

    //**************************************************************************
    //  Slots.
    //**************************************************************************
public slots:
    /*!
     * \brief OnBrowseLog   Browse log path.
     */
    void OnBrowseLog();

    /*!
     * \brief OnBrowseData  Browse data path.
     */
    void OnBrowseData();

    /*!
     * \brief OnBrowseHist  Browse data hist.
     */
    void OnBrowseHist();

    /*!
     * \brief OnApply       Apply settings.
     */
    void OnApply();

    /*!
     * \brief OnCancel      Cancel.
     */
    void OnCancel();


    //**************************************************************************
    //  Signals.
    //**************************************************************************
signals:

    /*!
     * \brief Apply     Apply settings.
     * \param config    settings.
     */
    void Apply(QMenuConfig* config);
};

#endif // QMenuConfig_H
