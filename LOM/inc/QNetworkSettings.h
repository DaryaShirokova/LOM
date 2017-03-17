#ifndef QNETWORKSETTINGS_H
#define QNETWORKSETTINGS_H

#include <QDialog>
#include <QMap>
#include <QVector>
#include <QPair>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
class QNetworkSettings;
}

class QNetworkSettings : public QDialog
{
    Q_OBJECT

public:
    using Row = QPair<QLabel*, QLineEdit*>;
    explicit QNetworkSettings(QWidget *parent = 0);
    void GenerateView(QMap<QString, int> regMap, QMap<QString, int> memMap, QString ip, int port);
    ~QNetworkSettings();

private:
    Ui::QNetworkSettings *ui;
    QVector<Row> data;
public slots:
    void Cancel();
    void SaveToFile();
};

#endif // QNETWORKSETTINGS_H
