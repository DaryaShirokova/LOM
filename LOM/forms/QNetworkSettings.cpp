#include "QNetworkSettings.h"
#include "ui_QNetworkSettings.h"

QNetworkSettings::QNetworkSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNetworkSettings)
{
    ui->setupUi(this);
}

QNetworkSettings::~QNetworkSettings()
{
    delete ui;
}
