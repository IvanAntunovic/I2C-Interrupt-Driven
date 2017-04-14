#pragma once
#ifndef _I2C_CONTROLLER_H_
#define _I2C_CONTROLLER_H_

#include "I2CTransmitter.h"
#include "I2CReceiver.h"

#define REPEATED_START	true

class I2CController
{
	private:
		I2CTransmitter i2cTransmitter;
		I2CReceiver	   i2cReceiver;
		int			   clockFrequency;

	public:
		I2CController();

		I2CTransmitter* getWritter();
		I2CReceiver*    getReader();

		// Methods for setting up the communication
		void setMode(uint8_t, int, bool = false);
		void setMode(uint8_t = -1, bool = false);

		// Methods for output stream
		unsigned int write(unsigned char* bytes, unsigned char offset, unsigned char length);
		unsigned char availableForWrite();

		// Methods for input stream
		unsigned char* read();
		unsigned int read(unsigned char* buffer);
		bool readByte(unsigned char*);
		unsigned char readBytes(unsigned char* buffer, unsigned int length);
		unsigned char available();
};

#endif

