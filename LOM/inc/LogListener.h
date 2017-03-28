#ifndef LOGLISTENER_H
#define LOGLISTENER_H

#include <QString>

//! An abstract class.
/*!
  Each class which extends LogListener can subscribe for notification about
  logger updates and handle the message from logger.
*/
class LogListener {
public:
    /*!
     * \brief handleMessage handle the message from logging system.
     * \param message   message.
     */
    virtual void handleMessage(QString message) = 0;
};

#endif // LOGLISTENER_H

