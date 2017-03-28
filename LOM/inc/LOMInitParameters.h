#ifndef LOMINITPARAMETERS_H
#define LOMINITPARAMETERS_H

#include <QObject>

//! A class containing initial parameters of LOM.
/*!
  A class containing thresholds, time settings and other information which can
  be configured in LOM.
*/

class LOMInitParameters : public QObject {
    Q_OBJECT
private:
    double thresholdFE; /*!< Forward endcap hit threshlold. */
    double thresholdBE; /*!< Backward endcap hit threshlold. */
    //! The minimal interval when both signals (FE, BE) must exceed thresholds.
    int coincidenceDurationThreshold;
    int hitThreshold; /*!< The threshold for quality signal detection. */

    int bufSize;    /*!< Size of buffer. */
    bool status;    /*!<  Shows whether init parameters are consistent with FPGA settings. */

public:

    //**************************************************************************
    // Constructors/destructors.
    //**************************************************************************

    /*!
     * \brief LOMInitParameters A default constructor.
     */
    LOMInitParameters();

    //! A default destructor.
    ~LOMInitParameters();

    //**************************************************************************
    // Initialisation.
    //**************************************************************************

    /*!
    * \brief Init Initialisation function.
    * \param thresholdFE forward endcap hit threshlold.
    * \param thresholdBE backward endcap hit threshlold.
    * \param coincidenceDurationThreshold the minimal coincidenc interval.
    * \param hitThreshold quality signal detection threshold.
    */
    void Init(double thresholdFE, double thresholdBE,
              int coincidenceDurationThreshold,
              int hitThreshold, int bufSize);

    /*!
     * \brief Init  Initialisation function.
     * \param newInit   Initialisation parameters to copy.
     */
    void Init(LOMInitParameters* newInit);

    /*!
     * \brief Init  Initialisation function.
     * \param filename  file with initialisation prameters.
     */
    void Init(QString filename);

    /*!
     * \brief Save  Save current initialisation to a file.
     * \param filename  file to save initialisation parameters.
     */
    void Save(QString filename);

    //**************************************************************************
    // Getters/Setters.
    //**************************************************************************

    void SetStatus(bool status) { this->status = status; emit StatusChanged(status); }
    bool GetStatus() {return this->status;}
    void SetThresholdFE(double thresholdFE) {this->thresholdFE = thresholdFE;}
    double GetThresholdFE() {return this->thresholdFE;}
    void SetThresholdBE(double thresholdBE) {this->thresholdBE = thresholdBE;}
    double GetThresholdBE() {return this->thresholdBE;}
    void SetCoincidenceDurationThreshold(unsigned int coincidenceDurationThreshold)
           {this->coincidenceDurationThreshold = coincidenceDurationThreshold;}
    int GetCoincidenceDurationThreshold()
                              {return this->coincidenceDurationThreshold;}
    void SetHitThreshold(unsigned int hitThreshold)
                              {this->hitThreshold = hitThreshold;}

    int GetHitThreshold() {return this->hitThreshold;}
    void SetBufSize(int bufSize) {this->bufSize = bufSize;}
    int GetBufSize() {return this->bufSize;}


    //**************************************************************************
    // Signals.
    //**************************************************************************

signals:
    /*!
     * \brief StatusChanged Status of data consistence.
     */
    void StatusChanged(bool);

    /*!
     * \brief ParamsChanged Parameters has been changed.
     */
    void ParamsChanged();

};

#endif // LOMINITPARAMETERS_H
