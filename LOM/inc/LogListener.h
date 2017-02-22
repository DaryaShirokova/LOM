#ifndef LOGLISTENER_H
#define LOGLISTENER_H

#include <QString>

class LogListener
{
public:
    virtual void handleMessage(QString message) = 0;
};

#endif // LOGLISTENER_H

