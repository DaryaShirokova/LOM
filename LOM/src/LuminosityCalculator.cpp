#include "inc/LuminosityCalculator.h"
#include "inc/Logger.h"
#include "inc/Constants.h"

#include <QDebug>
double LuminosityCalculator::registrationEfficiency;
double LuminosityCalculator::crossSection;

void LuminosityCalculator::Init(QString filename) {
    QSettings settings(filename, QSettings::IniFormat );

    registrationEfficiency = settings.value("registrationEfficiency", DEFAULT_REG_EFFICIENCY).toDouble();
    crossSection = settings.value("crossSection", DEFAULT_CROSS_SECTION).toDouble();

    if(settings.status() != QSettings::NoError)
        Logger::Log(Logger::ERROR, "LuminosityCalculator: Error while initialising"
                                   " registration efficiency and cross section. ");

    Logger::Log(Logger::INFO, "Registration efficiency = "
                 + QString::number(registrationEfficiency) + "; "
                 + "Cross section = " +
                   QString::number(crossSection) + " barns.");


}
