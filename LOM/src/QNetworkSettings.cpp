#include "inc/QNetworkSettings.h"
#include "ui_QNetworkSettings.h"
#include "inc/ConfigFileHandler.h"

#include <QDebug>
#include <QFormLayout>
#include <QPushButton>
#include <QFileDialog>

QNetworkSettings::QNetworkSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNetworkSettings)
{
    ui->setupUi(this);
    this->setWindowTitle("Network settings");
}

void QNetworkSettings::GenerateView(QMap<QString, int> regMap,
                                    QMap<QString, int> memMap,
                                    QString ip, int port)
{
    // Define form layout.
    QFormLayout *formLayout = new QFormLayout;

    // Host address section.
    QWidget* empty = new QWidget();
    QLabel* lHost = new QLabel("<b><font size='4'>Host address</font></b>");
    formLayout->addRow(lHost, empty);

    // Ip address.
    QLabel* lIP = new QLabel("IP");
    QLineEdit* leIP = new QLineEdit(ip);
    formLayout->addRow(lIP, leIP);
    Row r0(lIP,leIP);
    data.push_back(r0);

    // Port.
    QLabel* lPort = new QLabel("PORT");
    QLineEdit* lePort = new QLineEdit(QString::number(port));
    formLayout->addRow(lPort, lePort);
    Row r1(lPort, lePort);
    data.push_back(r1);

    // Registers section.
    QLabel* lab = new QLabel("<b><font size='4'>Registers</font></b>");
    formLayout->addRow(lab, empty);

    for(QString key: regMap.keys())
    {
        QLabel* l = new QLabel(key);
        int k = regMap.value(key);
        QLineEdit* le = new QLineEdit("0x" + QString("%1").arg(k,0,16).toUpper());
        Row r(l, le);
        data.push_back(r);
        formLayout->addRow(l, le);
    }

    // Memory addressed section.
    QLabel* lab2 = new QLabel("<b><font size='4'>Memory</font></b>");
    formLayout->addRow(lab2, empty);
    for(QString key: memMap.keys())
    {
        QLabel* l = new QLabel(key);
        int k = memMap.value(key);
        QLineEdit* le = new QLineEdit("0x" + QString("%1").arg(k,0,16).toUpper());
        Row r(l, le);
        data.push_back(r);
        formLayout->addRow(l, le);
    }

    // Add cancel button.
    QPushButton* bCancel = new QPushButton("Cancel");
    connect(bCancel, SIGNAL(clicked()), this, SLOT(Cancel()));

    // And save to file button.
    QPushButton* bSave = new QPushButton("Save to file");
    connect(bSave, SIGNAL(clicked()), this, SLOT(SaveToFile()));
    formLayout->addRow(bCancel, bSave);

    resize(200,(regMap.size()+memMap.size() + 7) * 28);

    setLayout(formLayout);
}

void QNetworkSettings::Cancel()
{
   this->close();
}

void QNetworkSettings::SaveToFile()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "config/network.conf",
                               tr("Config (*.conf)"));
    if(!filename.isNull())
    {
        QMap<QString,QString> map;
        for(Row r: data)
        {
            map.insert(r.first->text(), r.second->text());
        }
        ConfigFileHandler::WriteFile(filename, map);
    }
}

QNetworkSettings::~QNetworkSettings()
{
    delete ui;
}
