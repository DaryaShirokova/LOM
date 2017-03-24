#ifndef CONSTANTS_H
#define CONSTANTS_H


//! Definition of common constants.

//! The number of sectors in one endcap of the calorimeter.
#define SECTOR_NUM  16

//! The maximum possible amplitude of the event (GeV).
#define MAX_AMPL    7

//! The minimum possible amplitude of the event (GeV).
#define MIN_AMPL    0

#define SCALE_FACTOR    200
#define COUNTS_PER_MSEC 40

//! The names of registers.
#define REG_FE          "FE"
#define REG_BE          "BE"
#define REG_COIN        "COIN"
#define REG_HIT         "HIT"
#define REG_BUF         "BUF"
#define REG_BHABHA      "BHABHA"
#define REG_BKG         "BKG"
#define REG_VETO        "VETO"
#define REG_DELTAT      "DELTAT"
#define REG_DEADT       "DEADT"
#define REG_TOTDEATT    "TOTDEADT"

#define AMPL_BIT_SIZE   12
#define HIST_BIT_SIZE   12
#define CHANNEL_PER_BUF 8

//! The names of memory blocks.
#define MEM_BLOCK1   "BLOCK1"   // 0-7 forward
#define MEM_BLOCK2   "BLOCK2"   // 8-15 forward
#define MEM_BLOCK3   "BLOCK3"   // 0-7 backward
#define MEM_BLOCK4   "BLOCK4"   // 8-15 backward

//! Histogramms.
#define HIST_AMPLFE "HIST_AMPLFE"   // prefix (+1-16)
#define HIST_AMPLBE "HIST_AMPLBE"   // prefix (+1-16)
#define HIST_AMPL_NBINS 50
#define HIST_AMPL_X0    0.0
#define HIST_AMPL_FE_X1    8.0
#define HIST_AMPL_BE_X1    6.0


#define READ_TIMEOUT    3000
#define WRITE_TIMEOUT   3000

#define DEFAULT_CONF    "config/appset.ini"
#define DEFAULT_NETWORK "config/network.conf"
#define DEFAULT_PARAM   "config/initparam.conf"
#define DATA_PATH    "data/"
#define HIST_PATH    "hist/"
#define LOG_PATH    "log/"
#define DEFAULT_TREE_SIZE   10000

#define VALIDIP "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"
#endif // CONSTANTS_H


