#include "inc/Logger.h"

#include <QDateTime>
#include <QLocale>

QVector<LogListener*> Logger::listeners;
Logger::LogLevel Logger::logLevel;
bool Logger::writeToFile;
int Logger::linesWritten;
QString Logger::path;
QFile Logger::file;

QString Logger::enumToString(LogLevel l) {
    switch(l) {
        case ERROR: return "ERROR";
        case INFO:  return "INFO";
        case DEBUG: return "DEBUG";
        default:
            Log(LogLevel::ERROR, "Logger: trying to convert non-existing "
                                 "loglevel to string.");
            return "DEBUG";
    }
}

Logger::LogLevel Logger::stringToEnum(QString str) {
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

void Logger::OpenFile() {
    if(file.isOpen())
        file.close();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        writeToFile = false;
        Log(LogLevel::ERROR, "Logger: can not open log file: " + path);
    }
}

void Logger::SetPath(QString newPath) {
    if(file.isOpen())
        file.close();
    path = newPath;

    QLocale::setDefault(QLocale(QLocale::English, QLocale::Japan));
    QDateTime date = QDateTime::currentDateTime();
    QString name = "Log-" + QLocale().toString(date);
    if(!path.endsWith('/'))
        name = '/' + name;

    file.setFileName(path + name);
    if(writeToFile)
        OpenFile();
}

void Logger::SetWriteToFile(bool val) {
    writeToFile = val;
    if(val == true) {
        OpenFile();
        linesWritten = 0;
    }
    else if(file.isOpen()) file.close();
}

void Logger::NewLogFile() {
    linesWritten = 0;
    file.close();
    SetPath(path);
}


void Logger::Log(LogLevel messageLevel, QString message) {
    static int messageNum = 0;
    QString out;
    QString type = enumToString(messageLevel) ;

    // Prepare message depending on current log level.
    switch(logLevel) {
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

    if(out.isEmpty())
    return;

    messageNum++;

    // Write to file
    if(writeToFile) {
        if(!file.exists()) {
            NewLogFile();
            Log(LogLevel::ERROR, "Logger: log file doesn't exist. Creating new file.");
        }
        if(file.write(out.toStdString().c_str())!=out.length())
            Log(LogLevel::ERROR, "Logger: error occured while writing "
                                 "log file.");
        else {
            file.flush();
            linesWritten++;
            if(linesWritten >= LOG_FILE_SIZE)
                NewLogFile();
        }
    }

    // Notify listeners.
    for(LogListener* l: listeners)
        l->handleMessage(out);

}
