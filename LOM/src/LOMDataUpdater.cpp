#include "inc/LOMDataUpdater.h"
#include "inc/Logger.h"
#include "inc/Constants.h"

#include <QByteArray>
#include <QFile>

#include <TTree.h>
#include <TFile.h>
#include <time.h>
#include <QDebug>

/*!
 * \brief getByte   get Nth byte of interer value.
 * \param num       input number.
 * \param byteN     byte number (0-3)
 * \return
 */
unsigned char getByte(int num, int byteN)
{
    return (num >> (byteN * 8)) & 0xFF;
}

/*!
 * \brief pushNum  convert integer number to byte array.
 * \param arr      byte array.
 * \param num      number to convert.
 */
void pushNum(QByteArray* arr, int num)
{
    for(uint i = 0; i < sizeof(int); i ++)
        arr->push_back(getByte(num, i));
}

int ReadInt(QByteArray arr, int k)
{
    int n = k * 4;
    return (arr.at(n + 0) & 0xFF) |
           (arr.at(n + 1) & 0xFF) << 8 |
           (arr.at(n + 2) & 0xFF) << 16 |
           (arr.at(n + 3) & 0xFF) << 24;
}

LOMDataUpdater::LOMDataUpdater(AbstractTransporter *transporter)
{
    this->transporter = transporter;
}

void LOMDataUpdater::Configure(QString config)
{
    QFile file(config);
    if (!file.open(QIODevice::ReadOnly))
        Logger::Log(Logger::LogLevel::ERROR,
                    "LOMDataUpdater: can not open regmap config file: " + config);

    // TODO: move to configure (get key get key...)
    while (!file.atEnd())
    {
        QString l = file.readLine();
        if(l.isEmpty() || l.startsWith('\n') || l.startsWith('#'))
            continue;
        try
        {
            bool res;
            QString key = l.split(QRegExp("[\\s]+"))[0];
            int addr = l.split(QRegExp("[\\s]+"))[1].toInt(&res, 16);
            if(key == "IP")
                continue;
            if(key == MEM_EVENT)
            {
                memMap.insert(key, addr);
                continue;
            }
            if(key == REG_FE || key == REG_BE || key == REG_COIN || key == REG_HIT)
                regMap.insert(key, addr);
            else
                Logger::Log(Logger::LogLevel::ERROR,
                            "LOMDataUpdater: Attempted to add register which is"
                            " unknown to the programm:" + key);
        }
        catch(...)
        {
            Logger::Log(Logger::LogLevel::ERROR,
                        "LOMDataUpdater: Can't parse the input file: " + config);
        }
    }
}

bool LOMDataUpdater::ReadEventData(LOMEventData *eventData)
{
    QByteArray arr;

    arr.push_back("R");
    arr.push_back("M");
    pushNum(&arr, memMap.value(REG_FE));

    transporter->WriteData(arr, arr.size());

    // TODO change to signals slots
    if(!transporter->SetReadMode(READ_TIMEOUT))
    {
        Logger::Log(Logger::LogLevel::ERROR, "LOMDataUpdater: can't receive data."
                                             " Timeout error.");
        return false;
    }
    else arr = transporter->ReadData();

    QVector<QVector<double>> amplitudesFE;
    QVector<QVector<double>> amplitudesBE;

    for(int i = 0; i < SECTOR_NUM; i++)
    {
        QVector<double> sectorFE;
        for(int j = 0; j < 64; j++)
            sectorFE.push_back(ReadInt(arr, i*64 + j)* 1. / SCALE_FACTOR);
        amplitudesFE.push_back(sectorFE);
    }

    for(int i = 0; i < SECTOR_NUM; i++)
    {
        QVector<double> sectorBE;
        for(int j = 0; j < 64; j++)
            sectorBE.push_back(ReadInt(arr, SECTOR_NUM * 64 + i*64 + j) * 1. / SCALE_FACTOR);
        amplitudesBE.push_back(sectorBE);
    }
    eventData->GetAmplsFWD().SetAmplitudes(amplitudesFE);
    eventData->GetAmplsBWD().SetAmplitudes(amplitudesBE);

    return true;
}


bool LOMDataUpdater::WriteInitParameters(LOMInitParameters *initParameters)
{
    QByteArray arr;

    arr.push_back("W");
    arr.push_back("R");
    pushNum(&arr, regMap.value(REG_FE));
    pushNum(&arr, int(initParameters->GetThresholdFE() * 1000));
    pushNum(&arr, regMap.value(REG_BE));
    pushNum(&arr, int(initParameters->GetThresholdBE() * 1000));
    pushNum(&arr, regMap.value(REG_COIN));
    pushNum(&arr, int(initParameters->GetCoincidenceDurationThreshold()));
    pushNum(&arr, regMap.value(REG_HIT));
    pushNum(&arr, int(initParameters->GetHitThreshold()));

    return transporter->WriteData(arr, arr.size());
}

