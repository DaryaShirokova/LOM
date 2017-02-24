#ifndef LOMINITPARAMETERS_H
#define LOMINITPARAMETERS_H

//! A class containing initial parameters of LOM.
/*!
  A class containing thresholds, time settings and other information which can
  be configured.
*/

class LOMInitParameters
{
private:
    double thresholdFE; /*!< Forward endcap hit threshlold. */
    double thresholdBE; /*!< Backward endcap hit threshlold. */

    //! The minimal interval when both signals (FE, BE) must exceed thresholds.
    int coincidenceDurationThreshold;

    int backgroundThreshold; /*!< The threshold for quality signal detection. */

public:

    //**************************************************************************
    // Constructors/destructors.
    //**************************************************************************

    //! A default constructor.
    /*! A void constructor to initialize the module by default parameters. */
    LOMInitParameters();

    //! A default destructor.
    ~LOMInitParameters();

    //! Initialisation function.
    /*!
    * \param thresholdFE forward endcap hit threshlold.
    * \param thresholdBE backward endcap hit threshlold.
    * \param coincidenceDurationThreshold the minimal coincidenc interval.
    * \param backgroundThreshold quality signal detection threshold.
    */
    void Init(double thresholdFE, double thresholdBE,
              int coincidenceDurationThreshold,
              int backgroundThreshold);

    //**************************************************************************
    // Getters/Setters.
    //**************************************************************************

    //! Setter
    /*!
     * \param thresholdFE a new value of threshold for forward part.
     */
    void SetThresholdFE(double thresholdFE) {this->thresholdFE = thresholdFE;}

    //! Getter
    /*!
     * \return current value of thresholdFE.
     */
    double GetThresholdFE() {return this->thresholdFE;}

    //! Setter
    /*!
     * \param thresholdBE a new value of threshold for backward part.
     */
    void SetThresholdBE(double thresholdBE) {this->thresholdBE = thresholdBE;}

    //! Getter
    /*!
     * \return current value of thresholdBE.
     */
    double GetThresholdBE() {return this->thresholdBE;}

    //! Setter
    /*!
     * \param coincidenceDurationThreshold a new value of coincidence threshold.
     */
    void SetCoincidenceDurationThreshold(unsigned int coincidenceDurationThreshold)
           {this->coincidenceDurationThreshold = coincidenceDurationThreshold;}

    //! Getter
    /*!
     * \return current value of coincidenceDurationThreshold.
     */
    int GetCoincidenceDurationThreshold()
                              {return this->coincidenceDurationThreshold;}

    //! Setter
    /*!
     * \param backgroundThreshold a new value of background threshold.
     */
    void SetBackgroundThreshold(unsigned int backgroundThreshold)
                              {this->backgroundThreshold = backgroundThreshold;}

    //! Getter
    /*!
     * \return current value of backgroundThreshold.
     */
    int GetBackgroundThreshold() {return this->backgroundThreshold;}

};

#endif // LOMINITPARAMETERS_H
