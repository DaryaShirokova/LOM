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

public slots:
    void OnBrowseLog();
    void OnBrowseData();
    void OnSave();
    void OnApply();
    void OnCancel();
signals:
    void Save(MenuConfig* config, QString filename);
    void Apply(MenuConfig* config);
};

#endif // MENUCONFIG_H
