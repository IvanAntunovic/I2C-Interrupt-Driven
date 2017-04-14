#include "I2CReceiver.h"


void I2CReceiver::setMode(uint8_t _address, int _clockFrequency, bool _isRepeatedStartEnabled)
{
	address = _address;
	clockFrequency = _clockFrequency;
	isRepeatedStartEnabled = _isRepeatedStartEnabled;
}

void I2CReceiver::setMode(bool _isRepeatedStartEnabled)
{
	isRepeatedStartEnabled = _isRepeatedStartEnabled;
}

unsigned char I2CReceiver::available()
{
	return rxQueue.getAvailableItems();
}

CircularQueue I2CReceiver::getRxQueue()
{
	return rxQueue;
}

bool I2CReceiver::readByte(unsigned char* byte)
{
	if (!rxQueue.isEmpty())
	{
		rxQueue.dequeue(byte);
		return true;
	}
	return false;
}


unsigned char I2CReceiver::readBytes(unsigned char* buffer, unsigned int length)
{
	unsigned char bytesRead = 0;
	for (unsigned char i = 0; bytesRead < length; ++i)
	{
		if (readByte(buffer))
		{
			buffer++;
			bytesRead++;
		}
	}
	buffer;
	return bytesRead;
}

unsigned char* I2CReceiver::read()
{
	unsigned char bytesWrittenCnt = 0;
	unsigned char byte;

	unsigned char rxBuffer[BUFFER_SIZE];

	while (readByte(&byte))
	{
		rxBuffer[bytesWrittenCnt++] = byte;
	}

	return rxBuffer;
}

unsigned int I2CReceiver::read(unsigned char* buffer)
{
	unsigned char bytesWrittenCnt;
	unsigned char byte;

	for (bytesWrittenCnt = 0; readByte(&byte); bytesWrittenCnt++)
	{
		buffer[bytesWrittenCnt++] = byte;
	}

	return bytesWrittenCnt;
}