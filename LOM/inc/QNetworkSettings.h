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
    /*!
     * \brief QNetworkSettings  Constructor.
     * \param parent            parent widget.
     */
    explicit QNetworkSettings(QWidget *parent = 0);

    /*!
     * \brief GenerateView      Generate form.
     * \param regMap            Registers map.
     * \param memMap            Memory map.
     * \param ip                IP address.
     * \param port              Port number.
     */
    void GenerateView(QMap<QString, int> regMap, QMap<QString, int> memMap, QString ip, int port);

    /*!
     * Destructor.
     */
    ~QNetworkSettings();

private:
    Ui::QNetworkSettings *ui;   /*!< GUI. */
    QVector<Row> data;          /*! User input. */
public slots:
    /*!
     * \brief Cancel    Cancel changes.
     */
    void Cancel();

    /*!
     * \brief SaveToFile    Save new configuration to file.
     */
    void SaveToFile();
};

#endif // QNETWORKSETTINGS_H
