#include "inc/LOMInitParameters.h"
#include "inc/Constants.h"
#include "inc/Logger.h"

#include <QSettings>

LOMInitParameters::LOMInitParameters() {
    SetStatus(false);
}

LOMInitParameters::~LOMInitParameters() {
}

void LOMInitParameters::Init(double thresholdFE, double thresholdBE,
                             int coincidenceDurationThreshold,
                             int hitThreshold, int bufSize) {
    this->thresholdBE = thresholdBE;
    this->thresholdFE = thresholdFE;
    this->coincidenceDurationThreshold = coincidenceDurationThreshold;
    this->hitThreshold = hitThreshold;
    this->bufSize = bufSize;
    SetStatus(false);
    emit ParamsChanged();
}

void LOMInitParameters::Init(LOMInitParameters *newInit) {
    this->Init(newInit->GetThresholdFE(), newInit->GetThresholdBE(),
               newInit->GetCoincidenceDurationThreshold(),
               newInit->GetHitThreshold(),
               newInit->GetBufSize());
}

void LOMInitParameters::Init(QString filename) {
    QSettings settings(filename, QSettings::IniFormat );

    if(!settings.childGroups().contains("Thresholds"))
        Logger::Log(Logger::ERROR, "Init file doesn't contain threshold section!"
                                   " Default parameters are set.");
    settings.beginGroup( "Thresholds" );
    double thresholdFETemp = settings.value("fwd", DEFAULT_FWD_TH).toDouble();
    double thresholdBETemp = settings.value("bwd", DEFAULT_BWD_TH).toDouble();
    int coincidenceDurationThresholdTemp = settings.value("coin_dur", DEFAULT_COIN).toInt();
    int hitThresholdTemp = settings.value("hit", DEFAULT_HIT).toInt();
    settings.endGroup();

    if(!settings.childGroups().contains("Readout"))
        Logger::Log(Logger::ERROR, "Init file doesn't contain readout section!"
                                   " Default parameters are set.");
    settings.beginGroup( "Readout" );
    int bufSizeTemp = settings.value("buf", DEFAULT_BUF).toInt();
    settings.endGroup();

    Init(thresholdFETemp, thresholdBETemp, coincidenceDurationThresholdTemp,
         hitThresholdTemp, bufSizeTemp);
    Logger::Log(Logger::DEBUG, "LOM init parameters are loaded from " + filename);
}

void LOMInitParameters::Save(QString filename) {
    QSettings settings(filename, QSettings::IniFormat );

    settings.beginGroup( "Thresholds" );
    settings.setValue("fwd", thresholdFE);
    settings.setValue("bwd", thresholdBE);
    settings.setValue("coin_dur", coincidenceDurationThreshold);
    settings.setValue("hit", hitThreshold);
    settings.endGroup();
    settings.beginGroup( "Readout" );
    settings.setValue("buf", bufSize);
    settings.endGroup();
    settings.sync();
}
