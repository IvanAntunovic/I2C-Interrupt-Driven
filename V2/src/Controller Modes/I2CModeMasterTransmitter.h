#pragma once
#ifndef _I2C_MODE_MASTER_TRANSMITTER_H_
#define _I2C_MODE_MASTER_TRANSMITTER_H_

#include "I2CControllerMode.h"

class I2CModeMasterTransmitter : public I2CControllerMode
{
	private:
		static I2CControllerMode* sInstance;

	protected:
		I2CModeMasterTransmitter() {};

	public:
		static I2CControllerMode* getInstance(void);

};

#endif