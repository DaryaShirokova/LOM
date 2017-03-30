#ifndef LUMINOSITYCALCULATOR_H
#define LUMINOSITYCALCULATOR_H

#include <QSettings>

//! A class for luminosity calculation.
class LuminosityCalculator {
private:
    //! Registration efficiency is determined using the simulation process.
    static double registrationEfficiency; /*! The efficiency of Bhabha events registration. */
    static double crossSection; /*! Calculated bhabha cross section in barns.*/


    /*!
     * \brief LuminosityCalculator  Private constructor.
     */
    LuminosityCalculator() {}
public:
    /*!
     * \brief Init      Initialise registration efficiency and cross section.
     * \param settings
     */
    static void Init(QString filename);

    /*!
     * \brief GetLuminosity Calculate luminosity.
     * \param nBhabha       number of bhabha events.
     * \param dT            delta t.
     * \return  luminosity.
     */
    static double GetLuminosity(int nBhabha, double dT) { return nBhabha / dT / registrationEfficiency / crossSection; }

    /*!
     * \brief GetBackground Calculate background level.
     * \param nBkg          number of background events.
     * \param dT            delta t.
     * \return
     */
    static double GetBackground(int nBkg, double dT) { return nBkg / dT; }
};

#endif // LUMINOSITYCALCULATOR_H
