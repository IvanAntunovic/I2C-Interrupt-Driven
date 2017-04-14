#pragma once
#ifndef  _I2C_TRANSMITTER_H_
#define  _I2C_TRANSMITTER_H_

#include "Writeable.h"
#include "CircularQueue.h"
#include "I2CState.h"

class I2CState;

class I2CTransmitter : public Writeable
{
	private:
		I2CState*	state;
		uint8_t		address;
		int         clockFrequency;
		bool        isRepeatedStartEnabled;

	private:
		friend class I2CState;
		friend class I2CDataTransmittedACKRec;
		void changeState(I2CState*);

	private:
		//CircularQueue txQueue;

	public:	
		I2CTransmitter();
		void setTransmitterState(I2CState* state);

		void setMode(uint8_t, int, bool);
		void setMode(bool);
		uint8_t getAddress();

		CircularQueue& getTxQueue();
		CircularQueue txQueue;

		unsigned int write(unsigned char* bytes, unsigned char offset, unsigned char length) override;
		unsigned char availableForWrite() override;
};

#endif // !_I2C_TRANSMITTER_H_





