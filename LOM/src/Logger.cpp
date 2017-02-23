#include "inc/Logger.h"

QVector<LogListener*> Logger::listeners;
Logger::LogLevel Logger::logLevel;
bool Logger::writeToFile;
QString Logger::path;
QFile Logger::file;
