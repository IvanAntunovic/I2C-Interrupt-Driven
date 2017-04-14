#pragma once
#ifndef _I2C_RECEIVER_H_
#define _I2C_RECEIVER_H_

#include <stdlib.h>
#include "CircularQueue.h"
#include "Readable.h"
#include <stdint.h>

class I2CReceiver : public Readable
{
	private:
		//CircularQueue rxQueue;
		uint8_t		address;
		int         clockFrequency;
		bool        isRepeatedStartEnabled;

	public:
		CircularQueue rxQueue;
		CircularQueue getRxQueue();

		void setMode(uint8_t, int, bool);
		void setMode(bool);

		bool readByte(unsigned char* byte);
		unsigned char readBytes(unsigned char* buffer, unsigned int length);
		unsigned char* read();
		unsigned int read(unsigned char* buffer);
		unsigned char available();
};

#endif //!_I2C_RECEIVER_H_