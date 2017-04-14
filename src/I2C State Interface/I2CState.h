#pragma once
#ifndef _I2C_STATE_H_
#define _I2C_STATE_H_

#include <iostream>
#include "I2CTransmitter.h"

class I2CTransmitter;
using namespace std;

class I2CState
{
	protected:
		void changeState(I2CTransmitter*, I2CState*);

	public:
		virtual void handleStatusRegSignal(I2CTransmitter*, uint8_t);
		virtual void sendStartSignal(I2CTransmitter*);
		virtual void sendStopSignal(I2CTransmitter*);
		virtual void sendTransmitSignal(I2CTransmitter*);
		virtual void sendACKSignal(I2CTransmitter*);
		virtual void sendNACKSignal(I2CTransmitter*);
};

#endif