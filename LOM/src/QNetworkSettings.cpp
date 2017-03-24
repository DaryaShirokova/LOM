#include "inc/QNetworkSettings.h"
#include "ui_QNetworkSettings.h"
#include "inc/ConfigFileHandler.h"

#include <QDebug>
#include <QSettings>
#include <QScreen>
#include <QFormLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QScrollArea>

QNetworkSettings::QNetworkSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNetworkSettings) {
    ui->setupUi(this);
    this->setWindowTitle("Network settings");
}

void QNetworkSettings::GenerateView(QMap<QString, int> regMap,
                                    QMap<QString, int> memMap,
                                    QString ip, int port) {
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

    for(QString key: regMap.keys()) {
        QLabel* l = new QLabel(key);
        int k = regMap.value(key);
        QLineEdit* le = new QLineEdit("0x" + QString("%1").arg(k,0,16).toUpper());
        Row r(l, le);
        data.push_back(r);
        formLayout->addRow(l, le);
    }
    data.push_back(Row(NULL, NULL));
    // Memory addressed section.
    QLabel* lab2 = new QLabel("<b><font size='4'>Memory</font></b>");
    formLayout->addRow(lab2, empty);
    for(QString key: memMap.keys()) {
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

    QLabel* mylabel = new QLabel(this);
    mylabel->setLayout(formLayout);
    mylabel->resize(200,(regMap.size()+memMap.size() + 7) * 28);
    mylabel->show();

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setBackgroundRole(QPalette::Light);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->resize(230, QGuiApplication::primaryScreen()->availableSize().height() * 3 / 5);
    scrollArea->setWidget(mylabel);
    scrollArea->setParent(this);
    scrollArea->show();
    scrollArea->setVisible(true);

    resize(230, QGuiApplication::primaryScreen()->availableSize().height() * 3 / 5);
}

void QNetworkSettings::Cancel() {
   this->close();
}

void QNetworkSettings::SaveToFile()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "config/network.conf",
                               tr("Config (*.conf)"));
    if(!filename.isNull()) {

        QSettings settings(filename, QSettings::IniFormat);
        settings.beginGroup("Address");
        settings.setValue(data.at(0).first->text(), data.at(0).second->text());
        settings.setValue(data.at(1).first->text(), data.at(1).second->text());
        settings.endGroup();
        settings.beginGroup("Registers");
        for(int i = 2; i < data.size(); i++) {
            Row r = data.at(i);
            if(r.first == NULL) {
                settings.endGroup();
                settings.beginGroup("Memory");
                continue;
            }
            settings.setValue(r.first->text(), r.second->text());
        }
        settings.endGroup();
        settings.sync();
    }
}

QNetworkSettings::~QNetworkSettings()
{
    delete ui;
}
