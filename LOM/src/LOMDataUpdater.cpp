#include "inc/LOMDataUpdater.h"
#include "inc/Logger.h"
#include "inc/Constants.h"

#include <QByteArray>
#include <QFile>

#include <TTree.h>
#include <TFile.h>
#include <time.h>
#include <QSettings>

//******************************************************************************
//  Data to bytes / bytes to data
//******************************************************************************
/*!
 * \brief getByte   get Nth byte of interer value.
 * \param num       input number.
 * \param byteN     byte number (0-3)
 * \return
 */
unsigned char getByte(int num, int byteN) {
    return (num >> (byteN * 8)) & 0xFF;
}

/*!
 * \brief pushNum  convert integer number to byte array.
 * \param arr      byte array.
 * \param num      number to convert.
 */
void pushNum(QByteArray* arr, int num) {
    for(uint i = 0; i < sizeof(int); i ++)
        arr->push_back(getByte(num, i));
}

/*!
 * \brief ReadInt   Convert 4 bytes from byte array to integer.
 * \param arr       byte array
 * \param k         number of integer
 * \return          converted integer
 */
int ReadInt(QByteArray arr, int k) {
    int n = k * 4;
    return (arr.at(n + 0) & 0xFF) |
           (arr.at(n + 1) & 0xFF) << 8 |
           (arr.at(n + 2) & 0xFF) << 16 |
           (arr.at(n + 3) & 0xFF) << 24;
}

/*!
 * \brief ReadInt12 Convert 12 bits from byte array to integer (each nubmer takes
 *        1.5 bytes). Example: 300 50 will be represented in the array as
 *        00010010 11000000 00110010, whrere 300 = 100101100, 50 = 00110010
 *        So 300 = arr(0) | first_half(arr(1))
 *           50  = second_half(arr(1)) | arr(2)
 * \param arr   array of bytes
 * \param k     number of integer
 * \return      converted integer
 */
int ReadInt12(QByteArray arr, int k) {
    int n;
    if(k%2 == 0)
        n = k * 3 / 2;
    else n = (k-1) * 3 / 2 + 1;
    if(k%2 == 0)
        return (arr.at(n + 0) & 0xFF) << 4 |
               (arr.at(n + 1) & 0xF0) >> 4;
    return (arr.at(n + 0) & 0x0F) << 8 |
           (arr.at(n + 1) & 0xFF);
}

//******************************************************************************
//  Constructor/destructor.
//******************************************************************************

LOMDataUpdater::LOMDataUpdater(AbstractTransporter *transporter) {
    this->transporter = transporter;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(CheckConnection()));
}

LOMDataUpdater::~LOMDataUpdater() {
    delete timer;
}

//******************************************************************************
//  Connfiguration.
//******************************************************************************

void ParseError(QString value) {
    Logger::Log(Logger::ERROR, "LOMDataUpdater: Can't convert value " + value +
                              "to address or port.");
}

bool LOMDataUpdater::Configure(QString config) {
    int check = 0;
    QStringList expectedReg;
    QStringList expectedMem;

    // Add all known registers.
    expectedReg << REG_FE     << REG_BE  << REG_COIN  << REG_HIT  << REG_BUF
                << REG_BHABHA << REG_BKG << REG_DEADT << REG_TOTDEATT
                << REG_DELTAT << REG_VETO;
    expectedMem << MEM_BLOCK1 << MEM_BLOCK2 << MEM_BLOCK3 << MEM_BLOCK4;
    for(int i = 1; i <= SECTOR_NUM; i++) {
        expectedMem << QString(HIST_AMPLFE) + QString::number(i);
        expectedMem << QString(HIST_AMPLBE) + QString::number(i);
    }

    QSettings settings(config, QSettings::IniFormat);
    QStringList keys = settings.allKeys();

    for(QString key : keys) {
        int k = key.indexOf('/');
        QString subkey = key;
        if(k != -1)
            subkey = key.mid(k + 1, key.length());

        // IP address.
        if(subkey == "IP") {
            QString value = settings.value(key, "127.0.0.1").toString();
            check++;
            QRegExp ipreg(VALIDIP);
            if (!ipreg.exactMatch(value)) {
                Logger::Log(Logger::ERROR, "LOMDataUpdater: IP address is not valid! "
                           + value);
                return false;
            }
            this->ipaddr = value;
            continue;
        }

        // Port.
        bool res;
        if(subkey == "PORT") {
            check++;
            this->port = settings.value(key, 0).toInt();
            continue;
        }

        QString value = settings.value(key, "0xFFFF").toString();
        // Parse address.
        int addr = value.toInt(&res, 16);
        if(!res) {
            Logger::Log(Logger::ERROR, "LOMDataUpdater: " + value +
                                      " is not an address.");
            return false;
        }
        // Memory address.
        if(expectedMem.contains(subkey)) {
            memMap.insert(subkey, addr);
            expectedMem.removeAll(subkey);
            continue;
        }
        // Register address.
        if(expectedReg.contains(subkey)) {
            regMap.insert(subkey, addr);
            expectedReg.removeAll(subkey);
            continue;
        }
        Logger::Log(Logger::ERROR, "LOMDataUpdater: unknown key " + key);
    }

    if(check != 2) {
        Logger::Log(Logger::ERROR, "LOMDataUpdater: IP or port is not configured.");
        return false;
    }
    if(!expectedMem.isEmpty() || !expectedReg.isEmpty()) {
        QString str;
        for(QString s :expectedMem)
            str += " " + s;
        for(QString s :expectedReg)
            str += " " + s;
        Logger::Log(Logger::ERROR, "LOMDataUpdater: Required registers "
                                   "are not configured." + str);
        return false;
    }
    Logger::Log(Logger::DEBUG, "LOMDataUpdater: Network settings are loaded from "
                            + config);
    if(settings.status() == QSettings::AccessError)
        Logger::Log(Logger::LogLevel::ERROR,
                    "Access error occured while loading configurations: " + config);
    if(settings.status() == QSettings::FormatError)
        Logger::Log(Logger::LogLevel::ERROR,
                    "Wrong format of the configuration file: " + config);
    return true;
}

//******************************************************************************
//  Connnect/disconnect.
//******************************************************************************

bool LOMDataUpdater::Connect() {
    transporter->SetHostAddress(QHostAddress(ipaddr), port);
    bool connected = transporter->ConnectToHost();
    if(connected)
        timer->start(READ_TIMEOUT);

    return connected;
}

bool LOMDataUpdater::Disconnect() {
    return transporter->CloseConnection();
}


//******************************************************************************
//  Data transmission.
//******************************************************************************

QByteArray LOMDataUpdater::GetAnswer() {
    QByteArray arr;
    if(!transporter->SetReadMode(READ_TIMEOUT)) {
        Logger::Log(Logger::LogLevel::ERROR, "LOMDataUpdater: can't receive data."
                                             " Timeout error.");
        return NULL;
    }
    return arr = transporter->ReadData();
}

QByteArray LOMDataUpdater::ReadMemory(int address, int bitsNum) {
    QByteArray arr;
    arr.push_back("R");
    arr.push_back("M");
    pushNum(&arr, address);
    pushNum(&arr, bitsNum);

    transporter->WriteData(arr, arr.size());

    arr = GetAnswer();
    if(arr.isNull()) {
        Logger::Log(Logger::ERROR, "LOMDataUpdater: failed to receive data.");
        return NULL;
    }
    if(arr.size() != bitsNum / 8) {
        Logger::Log(Logger::ERROR, "LOMDataUpdater: the size of data is expected to be "
                                   + QString::number(bitsNum / 8) + " bytes, but it is"
                    + QString::number(arr.size()));
        return NULL;
    }
    return arr;
}

bool LOMDataUpdater::ReadAmplitudes(LOMAmplitudes *amplitudes, int bufSize) {
    QByteArray arr;
    QVector<QVector<double>> amplitudesFE;
    QVector<QVector<double>> amplitudesBE;

    int bitsNum = bufSize * AMPL_BIT_SIZE * CHANNEL_PER_BUF;

    // Reading out first 8 channels (0-7 forward).
    arr = ReadMemory(memMap.value(MEM_BLOCK1), bitsNum);
    if(arr.isNull()) return false;

    for(int i = 0; i < SECTOR_NUM / 2; i++) {
        QVector<double> sectorFE;
        for(int j = 0; j < bufSize; j++)
            sectorFE.push_back(ReadInt12(arr, i*bufSize + j)* 1. / SCALE_FACTOR);

        amplitudesFE.push_back(sectorFE);
    }

    // Reading out first 8-16 forward.
    arr = ReadMemory(memMap.value(MEM_BLOCK2), bitsNum);
    if(arr.isNull()) return false;

    for(int i = SECTOR_NUM / 2; i < SECTOR_NUM; i++) {
        QVector<double> sectorFE;
        for(int j = 0; j < bufSize; j++)
            sectorFE.push_back(ReadInt12(arr, (i-SECTOR_NUM / 2)*bufSize + j)* 1. / SCALE_FACTOR);
        amplitudesFE.push_back(sectorFE);
    }

    // Reading out first 0-8 backward.
    arr = ReadMemory(memMap.value(MEM_BLOCK3), bitsNum);
    if(arr.isNull()) return false;

    for(int i = 0; i < SECTOR_NUM / 2; i++) {
        QVector<double> sectorBE;
        for(int j = 0; j < bufSize; j++)
            sectorBE.push_back(ReadInt12(arr, i*bufSize + j)* 1. / SCALE_FACTOR);
        amplitudesBE.push_back(sectorBE);
    }

    // Reading out first 8-16 backward.
    arr = ReadMemory(memMap.value(MEM_BLOCK4), bitsNum);
    if(arr.isNull()) return false;

    for(int i = SECTOR_NUM / 2; i < SECTOR_NUM; i++) {
        QVector<double> sectorBE;
        for(int j = 0; j < bufSize; j++)
            sectorBE.push_back(ReadInt12(arr, (i - SECTOR_NUM / 2)*bufSize + j)* 1. / SCALE_FACTOR);
        amplitudesBE.push_back(sectorBE);
    }

    amplitudes->GetAmplsFWD().SetAmplitudes(amplitudesFE);
    amplitudes->GetAmplsBWD().SetAmplitudes(amplitudesBE);

    return true;
}

bool LOMDataUpdater::ReadHists(LOMHistograms *hists) {
    // Update amplitude hists.
    QMap<QString, Hist*> map = hists->GetHists();
    QMap<QString, Hist*>::iterator i;
    for(i = map.begin(); i != map.end(); ++i) {
        int bitsNum = i.value()->GetBinsNumber() * 32;
        QByteArray ans = ReadMemory(memMap.value(i.key()), bitsNum);
        if(ans.isNull()) return false;
        QVector<int> hist;
        for(int k = 0; k < i.value()->GetBinsNumber(); k++)
            hist.push_back(ReadInt(ans, k));
        i.value()->SetHist(hist);
    }
    return true;
}

bool LOMDataUpdater::ReadCounters(LOMCounters *counters) {
    QByteArray arr;
    arr.push_back("R");
    arr.push_back("R");
    pushNum(&arr, regMap.value(REG_BHABHA));
    pushNum(&arr, regMap.value(REG_BKG));
    pushNum(&arr, regMap.value(REG_DEADT));
    pushNum(&arr, regMap.value(REG_TOTDEATT));
    pushNum(&arr, regMap.value(REG_DELTAT));
    pushNum(&arr, regMap.value(REG_VETO));
    if(!transporter->WriteData(arr, arr.size()))
        return false;
    QByteArray ans = GetAnswer();
    if(ans.isNull() || ans.size() != arr.size() - 2)
        return false;

    counters->SetNBhabhaTotal(ReadInt(ans, 0));
    counters->SetNBkgTotal(ReadInt(ans, 1));
    counters->SetDeadTime(ReadInt(ans, 2));
    counters->SetTotalDeadTime(ReadInt(ans, 3));
    counters->SetDeltaT(ReadInt(ans, 4));
    counters->SetVetoTime(ReadInt(ans, 5));
    return true;
}

bool LOMDataUpdater::ReadInitParameters(LOMInitParameters *initParameters) {
    QByteArray arr;
    arr.push_back("R");
    arr.push_back("R");
    pushNum(&arr, regMap.value(REG_FE));
    pushNum(&arr, regMap.value(REG_BE));
    pushNum(&arr, regMap.value(REG_COIN));
    pushNum(&arr, regMap.value(REG_HIT));
    pushNum(&arr, regMap.value(REG_BUF));
    if(!transporter->WriteData(arr, arr.size()))
        return false;

    QByteArray ans = GetAnswer();
    if(ans.isNull() || ans.size() != arr.size() - 2) {
        Logger::Log(Logger::ERROR, "LOMDataUpdater: the size of data is less than expected (counters).");
        return false;
    }
    initParameters->SetThresholdFE(1.0 * ReadInt(ans, 0) / SCALE_FACTOR);
    initParameters->SetThresholdBE(1.0 * ReadInt(ans, 1) / SCALE_FACTOR);
    initParameters->SetCoincidenceDurationThreshold(ReadInt(ans, 2));
    initParameters->SetHitThreshold(ReadInt(ans, 3));
    initParameters->SetBufSize(ReadInt(ans, 4));
    return true;
}

bool LOMDataUpdater::WriteInitParameters(LOMInitParameters *initParameters) {
    QByteArray arr;
    QVector<int> data;
    data.push_back(int(initParameters->GetThresholdFE() * SCALE_FACTOR));
    data.push_back(int(initParameters->GetThresholdBE() * SCALE_FACTOR));
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
    if(ans.isNull() || ans.size() < 1 || int(ans.at(0)) != 1)
        return false;


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

    if(uint(ans.size()) != uint(data.size() * sizeof(int)))
        return false;

    for(int i = 0; i < data.size(); i++) {
        if(data.at(i) != ReadInt(ans, i)) {
            Logger::Log(Logger::ERROR, "LOMDataUpdater: wrong parameters have been written.");
            return false;
        }
    }
    return true;
}

void LOMDataUpdater::CheckConnection()
{
    QByteArray arr;
    arr.push_back('S');
    if(!transporter->WriteData(arr, arr.size())) {
        transporter->CloseConnection();
        timer->stop();
        return;
    }

    QByteArray ans = GetAnswer();
    if(ans.isNull()) {
        transporter->CloseConnection();
        timer->stop();
        return;
    }

    if(int(ans.at(0)) != 1) {
        transporter->CloseConnection();
        timer->stop();
    }
}
