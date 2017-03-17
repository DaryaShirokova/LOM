#ifndef LOMHISTORRAMMS_H
#define LOMHISTORRAMMS_H

#include "inc/Constants.h"
#include "inc/Logger.h"
#include <QMap>
#include <QVector>
#include <iostream>

// lomdu - readhist. читать регистры из файла (переделать полностью)
// настроить таймеры и сигналы в датапроцессоре
class Hist {
public:
    int GetBinsNumber() { return nbins; }
    QVector<int> GetHist() { return hist; }
    QVector<double> GetHistDouble() {
        QVector<double> histDouble;
        for(int i = 0; i < hist.size(); i++)
            histDouble.push_back(hist.at(i));
        return histDouble;
    }
    QVector<double> GetXValues() {
        QVector<double> xval;
        for(int i = 0; i < nbins; i++)
            xval.push_back(x0 + i * (x1-x0)/(nbins-1));
        return xval;
    }

    double GetX0() {return x0;}
    double GetX1() {return x1;}
    int GetMax() {return *std::max_element(hist.begin(), hist.end());}
    bool IsFavorite() {return favorite;}
    void SetFavorite(bool favorite) {this->favorite = favorite;}
    QString GetXTitle() {return xTitle;}
    QString GetYTitle() {return yTitle;}
    QString GetTitle() {return title;}
    void SetHist(QVector<int> hist)
    {
        if(hist.size() != nbins) {
            Logger::Log(Logger::DEBUG, "Logger: unexpected number of bins.");
            nbins = hist.size();
        }
        for(int i = 0; i < hist.size(); i++)
            std::cout << hist.at(i) << " ";
        std::cout << std::endl;
        this->hist = hist;
    }

    void SetX0(double x0) {this->x0 =x0;}
    void SetX1(double x1) {this->x1 =x1;}
    Hist(int nbins, double x0 = 0., double x1 = 1., QString title = "",
         QString xTitle = "", QString yTitle = "") {
        this->nbins = nbins;
        this->x0 = x0;
        this->x1 = x1;
        this->title = title;
        this->xTitle = xTitle;
        this->yTitle = yTitle;
        this->favorite = false;
    }

private:
    Hist();
    QVector<int> hist;
    int nbins;
    double x0;
    double x1;
    QString xTitle;
    QString yTitle;
    QString title;
    bool favorite;
};


class LOMHistograms {
private:
    QMap<QString, Hist*> map;

public:
    LOMHistograms();
    QMap<QString, Hist*> GetHists() {return this->map;}
};
/*
 * class Compare {
    public:
        bool operator()(QString s1, QString s2) const {
            int num1 = 0; int num2 = 0;
            int n = std::min(s1.size(), s2.size());
            for(int i = 0; i < n; i++) {
                QChar c1 = s1.at(i);
                QChar c2 = s1.at(i);
                if(c1 != c2) {
                    if(!c1.isDigit() || !c2.isDigit())
                        return c1 < c2;
                    else {
                        num1 = s1.mid(i).toInt();
                        num2 = s2.mid(i).toInt();
                        return num1 < num2;
                    }
                }
                if(i == n-1)
                    return s1.size() < s2.size();
            }
        }
};
*/

#endif // LOMHISTORRAMMS_H
