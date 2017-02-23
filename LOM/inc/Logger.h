#ifndef LOGGER_H
#define LOGGER_H

#include <QVector>
#include <QString>

#include "inc/LogListener.h"


//! A class for logging events.
/*!
  This class has only static methods and can not be instantiated.
  The main purpose of this class is to provide interface for logging different
  types of events (errors, debug messages, info).
  These log messages are displayed on the main screen (last few events) and
  saved in file.
  Use Logger::Log method to log events.
*/


class Logger
{
public:

    //! The LogLevel enum
    //! Detalization of logging.
    enum LogLevel { ERROR, INFO, DEBUG };

    //! Convert enum to string.
    /*!
     * \param l log level
     * \return  converted enum.
     */
    static QString enumToString(LogLevel l)
    {
        switch(l)
        {
        case ERROR: return "ERROR";
        case INFO:  return "INFO";
        case DEBUG: return "DEBUG";
        }
    }

    //! Convert string to enum.
    /*!
     * \param str   input string (INFO, DEBUG, ERROR).
     * \return  log level.
     */
    static LogLevel stringToEnum(QString str)
    {
        if(!QString::compare(str, "INFO"))
            return Logger::INFO;
        if(!QString::compare(str, "DEBUG"))
            return Logger::DEBUG;
        if(!QString::compare(str, "ERROR"))
            return Logger::ERROR;
        Logger::Log(Logger::ERROR, "Logger: attempting to convert inappropriate"
                                   " string to log level");
        return Logger::DEBUG;
    }

private:
    //! A constructor.
    Logger();

    static QString path; /* The name of the log file.*/
    static bool writeToFile; /* Switch on / off writing to file.*/
    static LogLevel logLevel; /* The detalization of logging.*/
    static QVector<LogListener*> listeners; /* Listeners of logger.*/

public:
    //! Setter
    /*!
     * \param newpath the name of the log file.
     */
    static void SetPath(QString newPath) {path = newPath;}

    //! Setter
    /*!
     * \param newLogLevel new log level,
     */
    static void SetLogLevel(LogLevel newLogLevel) {logLevel = newLogLevel;}

    //! Setter
    /*!
     * \param val on/off writing to file.
     */
    static void SetWriteToFile(bool val) {writeToFile = val;}

    //! Add new listener.
    /*!
     * \param listener a listener.
     */
    static void AddListener(LogListener* listener) {listeners.push_back(listener);}

    //! Logging function.
    /*!
     * \param messageLevel  type of message.
     * \param message       content of message.
     */
    static void Log(LogLevel messageLevel, QString message)
    {
        static int messageNum = 0;
        QString out;
        QString type = enumToString(messageLevel) ;
        switch(logLevel)
        {
        case ERROR:
            if(messageLevel != ERROR)
                out = "";
            else out = type + " [message " + QString::number(messageNum) + "]: "
                    + message + '\n';
            break;
        case INFO:
            if(messageLevel == DEBUG)
                out = "";
            else out = type + " [message " + QString::number(messageNum) + "]: "
                    + message + '\n';
            break;
        case DEBUG:
            out = type + " [message " + QString::number(messageNum) + "]: "
                                + message + '\n';
            break;
        }
        messageNum++;
        for(LogListener* l: listeners)
            l->handleMessage(out);
    }


};

#endif // LOGGER_H
