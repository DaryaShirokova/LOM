#ifndef LOMAMPLITUDES_H
#define LOMAMPLITUDES_H

#include <QVector>
//! A class representing event data coming from LOM.
/*!
  A class containing information which comes from LOM during the module operating.
*/

class Amplitudes {
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

    /*!
     * \brief   Get the values of amplitudes in the certain sector.
     * \param sector    sector number (1 - 16).
     * \return  the values of amplitudes.
     */
    VectorDouble GetAmplitudesInSector(unsigned int sector);

    /*!
     * \brief   Get maximum value of amplitudes in a sector.
     * \param sector    sector number (1 - 16).
     * \return  maximum value of amplitudes.
     */
    double GetMaxAmplitudeInSector(unsigned int sector);

    /*!
     * \brief   Get maximum value of amplitudes in each sectors.
     * \return  maximum values of amplitudes.
     */
    VectorDouble GetMaxAmplitudes();

    /*!
     * \brief   Get the sector with maximum aplitude value.
     * \return  the sector with maximum aplitude value.
     */
    unsigned int GetHitSector();

    //**************************************************************************
    // Getters/Setters.
    //**************************************************************************

    /*!
     * \brief Set apmlitudes.
     * \param amplitudes the value of amplitudes.
     */
    void SetAmplitudes(VectorDouble2D amplitudes) {this->amplitudes = amplitudes;}

    /*!
     * \brief Get apmlitudes.
     * \return array of amplitudes in all sectors.
     */
    VectorDouble2D GetAmplitudes() { return amplitudes;}
};


class LOMAmplitudes {
    using VectorInt = QVector<int>;
private:
    Amplitudes amplsBWD; /*!< Amplitudes in BWD sector.*/
    Amplitudes amplsFWD; /*!< Amplitudes in FWD sector.*/


public:
    LOMAmplitudes() {}

    //**************************************************************************
    // Data manipulating functions.
    //**************************************************************************
    /*!
     * \brief Get coincidence region.
     * \param sectorFWD the forward sector number.
     * \param sectorBWD the backward sector number.
     * \param thresholdFE threshold for amplitude in forward sector.
     * \param thresholdBE threshold for amplitude in backward sector.
     * \return  coincidence region (1 when intersects, 0 when not).
     */
    VectorInt GetCoincidenceRegion(unsigned int sectorFWD, unsigned int sectorBWD,
                                  double thresholdFE, double thresholdBE);


    /*!
     * \brief Get coincidence region left boundary.
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

    /*!
     * \brief Get coincidence region right boundary.
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

    /*!
     * \brief Check if there is a coincidence region for these two sectors.
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

    /*!
     * \brief Get amplitudes in the backward sectors.
     * \return amplitudes in backward sectors.
     */
    Amplitudes& GetAmplsBWD() {return amplsBWD;}

    //! Getter
    /*!
     * \brief Get amplitudes in the forward sectors.
     * \return amplitudes in the forward sectors.
     */
    Amplitudes& GetAmplsFWD() {return amplsFWD;}

};

#endif // LOMAMPLITUDES_H
