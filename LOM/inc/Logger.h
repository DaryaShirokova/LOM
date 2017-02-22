#ifndef LOGGER_H
#define LOGGER_H

#include <QVector>
#include <QString>

#include "inc/LogListener.h"

#include <iostream>


class Logger
{
public:
    enum LogLevel { ERROR, INFO, DEBUG };
    static QString enumToString(LogLevel l)
    {
        switch(l)
        {
        case ERROR: return "ERROR";
        case INFO:  return "INFO";
        case DEBUG: return "DEBUG";
        }
    }
    static LogLevel stringToEnum(QString str)
    {
        if(!QString::compare(str, "INFO"))
            return Logger::INFO;
        if(!QString::compare(str, "DEBUG"))
            return Logger::DEBUG;
        if(!QString::compare(str, "ERROR"))
            return Logger::ERROR;

    }

private:
    Logger();
    static QString path;
    static bool writeToFile;
    static LogLevel logLevel;
    static QVector<LogListener*> listeners;

public:
    static void SetPath(QString newPath) { path = newPath; }
    static void SetLogLevel(LogLevel newLogLevel) {logLevel = newLogLevel;}
    static void SetWriteToFile(bool val) { writeToFile = val; }
    static void AddListener(LogListener* l) {listeners.push_back(l);}


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
