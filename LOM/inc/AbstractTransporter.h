#ifndef ABSTRACTTRANSPORTER_H
#define ABSTRACTTRANSPORTER_H

#include <QString>

//! A class for data transmitting and receiving.
/*!
  An abstract class which provides an interface for establishing connection
  and data transporting.
*/
class AbstractTransporter
{
public:
    /*!
     * \brief ReadData  read the content of the registers.
     * \param dataSize  the size of data block.
     * \param data      output data.
     * \return status of the operation (true means success).
     */
    virtual bool ReadData(size_t dataSize, int* data) = 0;

    /*!
     * \brief WriteData write data to the register.
     * \param data      data to write.
     * \return status of the operation (true means success).
     */
    virtual bool WriteData(QByteArray data, qint64 size) = 0;//(const char* data, qint64 size) = 0;

};

#endif // ABSTRACTTRANSPORTER_H
