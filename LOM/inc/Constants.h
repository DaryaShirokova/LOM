#ifndef CONSTANTS_H
#define CONSTANTS_H


//! Definition of common constants.

//! The number of sectors in one endcap of the calorimeter.
#define SECTOR_NUM  16

//! The maximum possible amplitude of the event (GeV).
#define MAX_AMPL    7

//! The minimum possible amplitude of the event (GeV).
#define MIN_AMPL    0

#define SCALE_FACTOR    1000
//! The names of registers.
#define REG_FE      "FE"
#define REG_BE      "BE"
#define REG_COIN    "COIN"
#define REG_HIT     "HIT"
#define REG_BUF     "BUF"


//! The names of memory blocks.
#define MEM_EVENT   "EVENT"

#define READ_TIMEOUT    3000
#define WRITE_TIMEOUT   3000

#define DEFAULT_CONF    "config/appset.conf"
#define DEFAULT_NETWORK "config/network.conf"
#define DEFAULT_PARAM   "config/initparam.conf"
#define DATA_PATH    "data/"
#define LOG_PATH    "log/"
#define DEFAULT_TREE_SIZE   10000

#define VALIDIP "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"
#endif // CONSTANTS_H


