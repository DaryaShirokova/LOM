#ifndef LOMHISTORRAMMS_H
#define LOMHISTORRAMMS_H

#include "inc/Constants.h"
#include "inc/Logger.h"
#include <QMap>
#include <QVector>
#include <QFile>
#include <QString>
#include <iostream>


/*!
  A class representing simple histogram.
*/
class Hist {
private:
    /*!
     * \brief Hist  Default constructor.
     */
    Hist();

    QVector<int> hist; /*!< Hist data. */
    int nbins;  /*!< Number of bins. */
    double x0;  /*!< The left x value */
    double x1;  /*!< The right x value. */
    QString xTitle; /*!< x axis title. */
    QString yTitle; /*!< y axis title. */
    QString title;  /*!< Histogram title. */
    bool favorite;  /*!< Favorite flag. */

public:
    /*!
     * \brief Hist  Constructor.
     * \param nbins number of bins.
     * \param x0    the left x value.
     * \param x1    the right x value.
     * \param title histogram title.
     * \param xTitle    x axis title.
     * \param yTitle    y axis title.
     */
    Hist(int nbins, double x0 = 0., double x1 = 1., QString title = "",
         QString xTitle = "", QString yTitle = "");

    //**************************************************************************
    // Getters/setters.
    //**************************************************************************

    int GetBinsNumber() { return nbins; }
    QVector<int> GetHist() { return hist; }
    QVector<double> GetHistDouble();
    QVector<double> GetXValues();
    void ToFile(QString filename);
    double GetX0() {return x0;}
    double GetX1() {return x1;}
    int GetMax() {return *std::max_element(hist.begin(), hist.end());}
    bool IsFavorite() {return favorite;}
    void SetFavorite(bool favorite) {this->favorite = favorite;}
    QString GetXTitle() {return xTitle;}
    QString GetYTitle() {return yTitle;}
    QString GetTitle() {return title;}
    void SetHist(QVector<int> hist);
    void SetX0(double x0) {this->x0 =x0;}
    void SetX1(double x1) {this->x1 =x1;}
};

/*!
  A class representing LOM set of histograms.
*/
class LOMHistograms {
private:
    QMap<QString, Hist*> map; /*!< Pairs: key/histogram. */
    int runNum; /*!< The number used to create unique name for file. */
public:
    /*!
     * \brief LOMHistograms  Default constructor.
     */
    LOMHistograms();

    //**************************************************************************
    // Getters/setters.
    //**************************************************************************
    QMap<QString, Hist*> GetHists() {return this->map;}
    QStringList GetFavorite();
    void SaveToFiles(QString path);
    void SetRunNum(int runNum) {this->runNum = runNum; }
    int GetRunNum() {return runNum; }
};


#endif // LOMHISTORRAMMS_H
