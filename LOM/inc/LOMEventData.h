#ifndef LOMEVENTDATA_H
#define LOMEVENTDATA_H

#define SAMPLES_NUM 32

#include <vector>

//! A class representing event data coming from LOM.
/*!
  A class containing information which comes from LOM during the module operating.
*/
class LOMEventData
{

private:

    unsigned int sectorFE; /*!< The forward sector which an electron stroke in.*/
    unsigned int sectorBE; /*!< The backward sector which an electron stroke in.*/

    std::vector<int> amplitudesBE; /*!< The values of the signal in BWD.*/
    std::vector<int> amplitudesFE; /*!< The values of the signal in FWD.*/

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
     * \param amplitudesBE set the value of amplitudes in BWD.
     */
    void SetAmplitudesBE(std::vector<int> amplitudesBE) {this->amplitudesBE = amplitudesBE;}

    //! Getter
    /*!
     * \return current value of amplitudesBE.
     */
    std::vector<int> GetAmplitudesBE() {return this->amplitudesBE;}

    //! Setter
    /*!
     * \param amplitudesFE set the value of amplitudes in FWD.
     */
    void SetAmplitudesFE(std::vector<int> amplitudesFE) {this->amplitudesFE = amplitudesFE;}

    //! Getter
    /*!
     * \return current value of amplitudesFE.
     */
    std::vector<int> GetAmplitudesFE() {return this->amplitudesFE;}


};

#endif // LOMEVENTDATA_H
