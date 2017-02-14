#ifndef LOMEVENTDATA_H
#define LOMEVENTDATA_H

#define SAMPLES_NUM 64
#define SECTORS_NUM 16

#include <array>
#include <iostream>

//! A class representing event data coming from LOM.
/*!
  A class containing information which comes from LOM during the module operating.
*/
class LOMEventData
{
    using Array2D = std::array< std::array< double, SAMPLES_NUM >, SECTORS_NUM >;

private:

    unsigned int sectorFE; /*!< The forward sector which highest amplitude.*/
    unsigned int sectorBE; /*!< The backward sector which highest amplitde.*/

    Array2D amplitudesBE; /*!< The values of the signals in BWD.*/
    Array2D amplitudesFE; /*!< The values of the signals in FWD.*/

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

    //**************************************************************************
    // Getters/Setters.
    //**************************************************************************
    //! Setter
    /*!
     * \param sectorFE set the value of current strike sector.
     */
    void SetSectorFE(unsigned int sectorFE) {this->sectorFE = sectorFE;}

    //! Getter
    /*!
     * \return current value of sectorFE.
     */
    unsigned int GetSectorFE() {return this->sectorFE;}

    //! Setter
    /*!
     * \param sectorBE set the value of current strike sector.
     */
    void SetSectorBE(unsigned int sectorBE) {this->sectorBE = sectorBE;}

    //! Getter
    /*!
     * \return current value of sectorBE.
     */
    unsigned int GetSectorBE() {return this->sectorBE;}

    //! Setter
    /*!
     * \param amplitudesBE set the value of amplitudes in BWD.
     */
    void SetAmplitudesBE(double amplitudesBE[SECTORS_NUM][SAMPLES_NUM]) {
        for (int i = 0; i < SECTORS_NUM; i++)
            for(int j = 0; j < SAMPLES_NUM; j++)
                this->amplitudesBE[i][j] = amplitudesBE[i][j];
    }

    Array2D GetAmplitudeBE() { return amplitudesBE;}
    Array2D GetAmplitudeFE() { return amplitudesFE;}

    //! Setter
    /*!
     * \param amplitudesFE set the value of amplitudes in FWD.
     */
    void SetAmplitudesFE(double amplitudesFE[SECTORS_NUM][SAMPLES_NUM]) {
        for (int i = 0; i < SECTORS_NUM; i++)
            for(int j = 0; j < SAMPLES_NUM; j++)
                this->amplitudesFE[i][j] = amplitudesFE[i][j];
    }

};

#endif // LOMEVENTDATA_H
