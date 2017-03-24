#ifndef MENUCONFIG_H
#define MENUCONFIG_H

#include <QDialog>

namespace Ui {
class MenuConfig;
}

class MenuConfig : public QDialog
{
    Q_OBJECT
private:
    Ui::MenuConfig *ui;
public:
    explicit MenuConfig(QWidget* parent = 0);
    ~MenuConfig();

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

public slots:
    void OnBrowseLog();
    void OnBrowseData();
    void OnBrowseHist();
    void OnApply();
    void OnCancel();
signals:
    void Apply(MenuConfig* config);
};

#endif // MENUCONFIG_H
