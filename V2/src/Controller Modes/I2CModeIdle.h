#pragma once
#ifndef _I2C_MODE_IDLE_
#define _I2C_MODE_IDLE_

#include "I2CControllerMode.h"

class I2CModeIdle : public I2CControllerMode
{
	private:
		static I2CControllerMode* sInstance;

	protected:
		I2CModeIdle() {};

	public:
		static I2CControllerMode* getInstance();
};

#endif