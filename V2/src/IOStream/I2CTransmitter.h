#pragma once
#ifndef  _I2C_TRANSMITTER_H_
#define  _I2C_TRANSMITTER_H_

#include "Writeable.h"
#include "CircularQueue.h"
#include "I2CController.h"
#include "I2CState.h"

class I2CTransmitter 
{
	public:
		void sendStartSignal(void);
		void sendStopSignal(void);
		void sendTransmitSignal(void);
};

#endif // !_I2C_TRANSMITTER_H_





