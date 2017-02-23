#ifndef LOMEVENTDATA_H
#define LOMEVENTDATA_H

#include <QVector>
#include "inc/Constants.h"

//! A class representing event data coming from LOM.
/*!
  A class containing information which comes from LOM during the module operating.
*/

class Amplitudes
{
public:
    using VectorDouble = QVector<double>; /* QVector of double.*/
    using VectorDouble2D = QVector<VectorDouble>; /* 2D QVector of double.*/

private:
    VectorDouble2D amplitudes; /*!< The values of the signals.*/

public:
    //**************************************************************************
    // Constructor/destructor.
    //**************************************************************************

    //! A default constructor.
    Amplitudes() { }

    //! A destructor.
    ~Amplitudes() { }

    //**************************************************************************
    // Data manipulating functions.
    //**************************************************************************

    //! Get the values of amplitudes in a certain sector.
    /*!
     * \param sector    sector number (1 - 16).
     * \return  the values of amplitudes.
     */
    VectorDouble GetAmplitudesInSector(unsigned int sector);

    //! Get maximum value of amplitudes in sector.
    /*!
     * \param sector    sector number (1 - 16).
     * \return  maximum value of amplitudes.
     */
    double GetMaxAmplitudeInSector(unsigned int sector);

    //! Get maximum value of amplitudes in all sectors.
    /*!
     * \return  maximum values of amplitudes.
     */
    VectorDouble GetMaxAmplitudes();

    //! Get the sector with maximum aplitude value.
    /*!
     * \return  the sector with maximum aplitude value.
     */
    unsigned int GetHitSector();

    //**************************************************************************
    // Getters/Setters.
    //**************************************************************************

    //! Setter
    /*!
     * \param amplitudes set the value of amplitudes.
     */
    void SetAmplitudes(VectorDouble2D amplitudes) {this->amplitudes = amplitudes;}

    //! Getter
    /*!
     * \return array of amplitudes in all sectors.
     */
    VectorDouble2D GetAmplitudes() { return amplitudes;}
};

class LOMEventData
{
    using VectorInt = QVector<int>;
private:

    Amplitudes amplsBWD; /*!< Amplitudes in BWD sector.*/
    Amplitudes amplsFWD; /*!< Amplitudes in FWD sector.*/

    double deadTime; /*!< Dead time in the calorimeter. */
    double totalDeadTime; /*!< Total dead time in the calorimeter. */

    unsigned int nBhabhaTotal; /*!< The total number of detected bhabha events.*/
public:
    //**************************************************************************
    // Constructor/destructor.
    //**************************************************************************

    //! A default constructor.
    LOMEventData();

    //! A destructor.
    ~LOMEventData();

    //**************************************************************************
    // Data manipulating functions.
    //**************************************************************************

    //! Get coincidence region.
    /*!
     * \param sectorFWD the forward sector number.
     * \param sectorBWD the backward sector number.
     * \param thresholdFE threshold for amplitude in forward sector.
     * \param thresholdBE threshold for amplitude in backward sector.
     * \return  coincidence region (1 when intersects, 0 when not).
     */
    VectorInt GetCoincidenceRegion(unsigned int sectorFWD, unsigned int sectorBWD,
                                  double thresholdFE, double thresholdBE);


    //! Get coincidence region left boundary.
    /*!
     * \param sectorFWD the forward sector number.
     * \param sectorBWD the backward sector number.
     * \param thresholdFE threshold for amplitude in forward sector.
     * \param thresholdBE threshold for amplitude in backward sector.
     * \return  coincidence region right boundary (-1 if there is no
     *          coincidence region).
     */
    int GetCoincidenceRegionLeftBoundary(unsigned int sectorFWD,
                                              unsigned int sectorBWD,
                                              double thresholdFE,
                                              double thresholdBE);

    //! Get coincidence region right boundary.
    /*!
     * \param sectorFWD the forward sector number.
     * \param sectorBWD the backward sector number.
     * \param thresholdFE threshold for amplitude in forward sector.
     * \param thresholdBE threshold for amplitude in backward sector.
     * \return  coincidence region right boundary (-1 if there is no
     *          coincidence region).
     */
    int GetCoincidenceRegionRightBoundary(unsigned int sectorFWD,
                                              unsigned int sectorBWD,
                                              double thresholdFE,
                                              double thresholdBE);

    //! Check if there is a coincidence region for these two sectors.
    /*!
     * \param sectorFWD the forward sector number.
     * \param sectorBWD the backward sector number.
     * \param thresholdFE threshold for amplitude in forward sector.
     * \param thresholdBE threshold for amplitude in backward sector.
     * \return  true if coincidence region exists.
     */
    bool haveCoincidenceRegion(unsigned int sectorFWD,
                                               unsigned int sectorBWD,
                                               double thresholdFE,
                                               double thresholdBE);

    //**************************************************************************
    // Getters/Setters.
    //**************************************************************************

    //! Getter
    /*!
     * \return amplitudes in forward sectors.
     */
    Amplitudes& GetAmplsBWD() {return amplsBWD;}

    //! Getter
    /*!
     * \return amplitudes in forward sectors.
     */
    Amplitudes& GetAmplsFWD() {return amplsFWD;}

};

#endif // LOMEVENTDATA_H
