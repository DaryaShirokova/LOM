#ifndef LOGGER_H
#define LOGGER_H

#include "inc/LogListener.h"
#include "inc/Constants.h"

#include <QDir>
#include <QVector>
#include <QString>
#include <QFile>

//! A class for logging events.
/*!
  This class has only static methods and can not be instantiated.
  The main purpose of this class is to provide interface for logging different
  types of events (errors, debug messages, info).
  These log messages are displayed on the main screen (last few events) and
  saved in file.
  Use Logger::Log method to log an event.
*/
class Logger
{
public:

    //! The LogLevel enum
    //! Detalization of logging.
    enum LogLevel { ERROR, INFO, DEBUG };

    /*!
     * \brief Convert enum to string.
     * \param l log level
     * \return  enum in form of QString.
     */
    static QString enumToString(LogLevel l);


    /*!
     * \brief Convert string to enum.
     * \param str   input string (INFO, DEBUG, ERROR).
     * \return  log level.
     */
    static LogLevel stringToEnum(QString str);

    /*!
     * \brief Create new file where the log is stored.
     */
    static void NewLogFile();

    /*!
     * \brief Set path and open file for log output.
     * \param newpath path to log.
     */
    static void SetPath(QString newPath);

    /*!
     * \brief Get current log path.
     * \return path current log path
     */
    static QString GetPath() { return path;}

    /*!
     * \brief Set log level.
     * \param newLogLevel new log level.
     */
    static void SetLogLevel(LogLevel newLogLevel) { logLevel = newLogLevel;}

    /*!
     * \brief Turn on/off writing log to file and open/close it.
     * \param val on/off writing to file.
     */
    static void SetWriteToFile(bool val);

    /*!
     * \brief Add new listener.
     * \param listener a listener.
     */
    static void AddListener(LogListener* listener) {listeners.push_back(listener);}

    /*!
     * \brief Logging function.
     * \param messageLevel  type of message.
     * \param message       content of message.
     */
    static void Log(LogLevel messageLevel, QString message);

private:
    //! A constructor.
    Logger();

    static QString path; /*!< Log file name.*/
    static QFile file; /*!< Log file.*/
    static bool writeToFile; /*!< Switch on / off writing to file.*/
    static LogLevel logLevel; /*!< The detalization of logging.*/
    static QVector<LogListener*> listeners; /*!< Listeners of logger.*/
    static int linesWritten; /*!< Number of lines in the current log file.*/

    /*!
     * \brief OpenFile  auxiliary function for opening file.
     */
    static void OpenFile();
};

#endif // LOGGER_H
