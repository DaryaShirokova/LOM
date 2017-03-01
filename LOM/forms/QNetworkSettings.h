#ifndef QNETWORKSETTINGS_H
#define QNETWORKSETTINGS_H

#include <QDialog>

namespace Ui {
class QNetworkSettings;
}

class QNetworkSettings : public QDialog
{
    Q_OBJECT

public:
    explicit QNetworkSettings(QWidget *parent = 0);
    ~QNetworkSettings();

private:
    Ui::QNetworkSettings *ui;
};

#endif // QNETWORKSETTINGS_H
