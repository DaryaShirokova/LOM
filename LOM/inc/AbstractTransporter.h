#ifndef ABSTRACTTRANSPORTER_H
#define ABSTRACTTRANSPORTER_H

//! A class for data exchange.
/*!
  An abstract class which provides an interface for establishing communication
  and data transporting.
*/
class AbstractTransporter
{

protected:
    // TODO: type
    int IPAddress; /*!< IP address of the destination point.*/

public:
    /*!
     * \brief ReadData  read the content of the register.
     * \param regAddr   register address.
     * \param data      output data.
     */
    virtual void ReadData(int regAddr, int* data) = 0;

    /*!
     * \brief ReadData  read the content of the registers.
     * \param regAddr   register address.
     * \param dataSize  the size of data block.
     * \param data      output data.
     */
    virtual void ReadData(int regAddr, int dataSize, int* data) = 0;

    /*!
     * \brief WriteData write data to the register.
     * \param regAddr   register address.
     * \param data      data to write.
     */
    virtual void WriteData(int regAddr, int* data) = 0;

    /*!
     * \brief WriteData write data to the register.
     * \param regAddr   register address.
     * \param dataSize  the size of data block.
     * \param data      data to write.
     */
    virtual void WriteData(int regAddr, int dataSize, int* data) = 0;

};

#endif // ABSTRACTTRANSPORTER_H
