#ifndef CONSTANTS_H
#define CONSTANTS_H


//! Definition of common constants.

//! The number of sectors in one endcap of the calorimeter.
#define SECTOR_NUM  16

//! The maximum possible amplitude of the event (GeV).
#define MAX_AMPL    7

//! The minimum possible amplitude of the event (GeV).
#define MIN_AMPL    0

// Scale factor between amplitude in GeV and integer amlitude.
#define SCALE_FACTOR    200
// LOM parameter: number of counts per second.
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

// Bits to encode one amplitude value.
#define AMPL_BIT_SIZE   12
// Bits to encode one hist bin.
#define HIST_BIT_SIZE   12
// Number of sectors in one data buffer.
#define CHANNEL_PER_BUF 8

//! The names of memory blocks.
#define MEM_BLOCK1   "BLOCK1"   // 0-7 forward
#define MEM_BLOCK2   "BLOCK2"   // 8-15 forward
#define MEM_BLOCK3   "BLOCK3"   // 0-7 backward
#define MEM_BLOCK4   "BLOCK4"   // 8-15 backward

//! Histogramms.
#define HIST_AMPLFE "HIST_AMPLFE"   // prefix (+1-16)
#define HIST_AMPLBE "HIST_AMPLBE"   // prefix (+1-16)
#define HIST_AMPL_NBINS 50          // number of bins in amplitudes distribution.
#define HIST_AMPL_X0    0.0         // x0 (amplitudes distribution)
#define HIST_AMPL_FE_X1    8.0      // x1 (amplitudes distribution, fwd)
#define HIST_AMPL_BE_X1    6.0      // x1 (amplitudes distribution, bwd)


#define READ_TIMEOUT    3000        // timeout for reading data via tcp/ip
#define WRITE_TIMEOUT   3000        // timeout for writing data via tcp/ip

#define DEFAULT_CONF    "config/appset.ini"     // default application config.
#define DEFAULT_NETWORK "config/network.conf"   // default network config.
#define DEFAULT_PARAM   "config/init.param"     // default init params config.
#define DATA_PATH    "data/"    // default path to store .root files.
#define HIST_PATH    "hist/"    // default path to store hists.
#define LOG_PATH    "log/"      // default path to store log.
#define DEFAULT_TREE_SIZE   10000   // default root tree size.

#define LOG_FILE_SIZE   100     // default log file size.

// Default thresholds values.
#define DEFAULT_HIT     20
#define DEFAULT_COIN    20
#define DEFAULT_FWD_TH  3.
#define DEFAULT_BWD_TH  1.
#define DEFAULT_BUF     64

#define VALIDIP "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"
#endif // CONSTANTS_H


