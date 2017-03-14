#include "inc/LOMDataUpdater.h"
#include "inc/Logger.h"
#include "inc/Constants.h"
#include "inc/ConfigFileHandler.h"

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
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(CheckConnection()));
}

void ParseError(QString value)
{
    Logger::Log(Logger::ERROR, "LOMDataUpdater: Can't convert value " + value +
                              "to address or port.");
}

void LOMDataUpdater::Configure(QString config)
{
    QMap<QString, QString> map = ConfigFileHandler::ReadFile(config);

    for(QString key : map.keys())
    {
        QString value = map.value(key);
        if(key == "IP")
        {
            QRegExp ipreg(VALIDIP);
            if (!ipreg.exactMatch(value))
            {
                Logger::Log(Logger::ERROR, "LOMDataUpdater: IP address is not valid! "
                           + value);
                return;
            }
            this->ipaddr = value;
            continue;
        }
        bool res;
        if(key == "PORT")
        {
            int newport = value.toInt(&res, 10);
            if(!res)
            {
                ParseError(key);
                return;
            }
            this->port = newport;
            continue;
        }

        int addr = value.toInt(&res, 16);
        if(!res)
        {
            ParseError(key);
            return;
        }
        if(key == MEM_EVENT)
            memMap.insert(key, addr);
        else if(key == REG_FE || key == REG_BE || key == REG_COIN || key == REG_HIT
                || key == REG_BUF)
            regMap.insert(key, addr);
        else Logger::Log(Logger::ERROR,
                        "LOMDataUpdater: Unknown register or memory address "
                        + key);
    }
    Logger::Log(Logger::INFO, "LOMDataUpdater: Network settings are loaded from "
                            + config);

}

bool LOMDataUpdater::Connect()
{
    transporter->SetHostAddress(QHostAddress(ipaddr), port);
    bool connected = transporter->ConnectToHost();
    if(connected)
        timer->start(READ_TIMEOUT);

    return connected;
}

bool LOMDataUpdater::Disconnect()
{
    return transporter->CloseConnection();
}

QByteArray LOMDataUpdater::GetAnswer()
{
    QByteArray arr;
    if(!transporter->SetReadMode(READ_TIMEOUT))
    {
        Logger::Log(Logger::LogLevel::ERROR, "LOMDataUpdater: can't receive data."
                                             " Timeout error.");
        return NULL;
    }
    return arr = transporter->ReadData();
}

bool LOMDataUpdater::ReadEventData(LOMEventData *eventData)
{
    QByteArray arr;

    arr.push_back("R");
    arr.push_back("M");
    pushNum(&arr, memMap.value(REG_FE));

    transporter->WriteData(arr, arr.size());

    arr = GetAnswer();
    if(arr.isNull())
        return false;

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
    QVector<int> data;
    data.push_back(int(initParameters->GetThresholdFE() * 1000));
    data.push_back(int(initParameters->GetThresholdBE() * 1000));
    data.push_back(int(initParameters->GetCoincidenceDurationThreshold()));
    data.push_back(int(initParameters->GetHitThreshold()));
    data.push_back(int(initParameters->GetBufSize()));
    arr.push_back("W");
    arr.push_back("R");
    pushNum(&arr, regMap.value(REG_FE));
    pushNum(&arr, data.at(0));
    pushNum(&arr, regMap.value(REG_BE));
    pushNum(&arr, data.at(1));
    pushNum(&arr, regMap.value(REG_COIN));
    pushNum(&arr, data.at(2));
    pushNum(&arr, regMap.value(REG_HIT));
    pushNum(&arr, data.at(3));
    pushNum(&arr, regMap.value(REG_BUF));
    pushNum(&arr, data.at(4));


    if(!transporter->WriteData(arr, arr.size()))
        return false;

    QByteArray ans = GetAnswer();
    if(ans.isNull())
        return false;

    if(ans.size() < 1 || int(ans.at(0)) != 1)
    {
        Logger::Log(Logger::ERROR, "LOMDataUpdater: failed to update registers.");
        return false;
    }

    arr.clear();
    arr.push_back("R");
    arr.push_back("R");
    pushNum(&arr, regMap.value(REG_FE));
    pushNum(&arr, regMap.value(REG_BE));
    pushNum(&arr, regMap.value(REG_COIN));
    pushNum(&arr, regMap.value(REG_HIT));
    pushNum(&arr, regMap.value(REG_BUF));

    if(!transporter->WriteData(arr, arr.size()))
        return false;
    ans = GetAnswer();
    if(ans.isNull())
        return false;

    else ans = transporter->ReadData();
    qDebug() << ans.size();
    qDebug() << ReadInt(ans, 0);
    if(uint(ans.size()) != uint(data.size() * sizeof(int)))
    {
        Logger::Log(Logger::ERROR, "LOMDataUpdater: can't read registers.");
        return false;
    }
    for(int i = 0; i < data.size(); i++)
    {
        if(data.at(i) != ReadInt(ans, i))
        {
            Logger::Log(Logger::ERROR, "LOMDataUpdater: wrong parameters have been written.");
            return false;
        }

        qDebug() << data.at(i) << ReadInt(ans, i);
    }
    return true;
}

void LOMDataUpdater::CheckConnection()
{
    QByteArray arr;
    arr.push_back('S');
    if(!transporter->WriteData(arr, arr.size()))
    {
        transporter->CloseConnection();
        timer->stop();
        return;
    }

    QByteArray ans = GetAnswer();
    if(ans.isNull())
    {
        qDebug() << "Answer is null";
        transporter->CloseConnection();
        timer->stop();
        return;
    }
    if(int(ans.at(0)) != 1) {
        qDebug() << "Answer is not 1";
        transporter->CloseConnection();
        timer->stop();
    }
}
