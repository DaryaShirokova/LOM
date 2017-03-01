#ifndef CONFIGFILEREADER_H
#define CONFIGFILEREADER_H

#include <QMap>
#include <QString>
#include <QFile>

#include "inc/Logger.h"

class ConfigFileHandler
{
public:
    static void WriteFile(QString filename, QMap<QString, QString> map)
    {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly))
        {
            Logger::Log(Logger::LogLevel::ERROR, "ConfigFileReader: Can't open file "
                        + filename + ". " + file.errorString());
            return;
        }

        for(QString key: map.keys())
        {
            QString val = map.value(key);
            QString str = key + '\t' + val + '\n';
            file.write(str.toStdString().c_str());
        }
        file.close();
    }

    static QMap<QString, QString> ReadFile(QString filename)
    {
        QMap<QString, QString> map;

        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly))
        {
            Logger::Log(Logger::LogLevel::ERROR, "ConfigFileReader: Can't open file "
                        + filename + ". " + file.errorString());
            return map;
        }

        while (!file.atEnd())
        {
            // Read one line.
            QString l = file.readLine();

            // Skip comments and empty lines.
            if(l.isEmpty() || l.startsWith('\n') || l.startsWith('#'))
                continue;

            // Split to key/value pair.
            QString key = l.split(QRegExp("[\\s]+"))[0];
            QString value = l.split(QRegExp("[\\s]+"))[1];
            if (key.isEmpty())
            {
                Logger::Log(Logger::LogLevel::ERROR, "ConfigFileReader: Error parsing file "
                            + filename + ". " + "Empty key.");
                continue;
            }
            map.insert(key, value);
        }

        file.close();
        return map;
    }
};

#endif // CONFIGFILEREADER_H

