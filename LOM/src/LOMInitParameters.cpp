#include "../inc/LOMInitParameters.h"

#include <QDebug>
#include "inc/ConfigFileHandler.h"

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
    QMap<QString, QString> map = ConfigFileHandler::ReadFile(filename);
    this->Init(map.value("FWD").toDouble(),
               map.value("BWD").toDouble(),
               map.value("COIN").toInt(),
               map.value("HIT").toInt(),
               map.value("BUF").toInt());
    Logger::Log(Logger::INFO, "LOM init parameters are loaded from " + filename);
}

void LOMInitParameters::Save(QString filename) {
    QMap<QString, QString> map;
    map.insert("FWD", QString::number(thresholdFE));
    map.insert("BWD", QString::number(thresholdBE));
    map.insert("COIN",QString::number(coincidenceDurationThreshold));
    map.insert("HIT", QString::number(hitThreshold));
    map.insert("BUF", QString::number(bufSize));
    ConfigFileHandler::WriteFile(filename, map);
}
