#pragma once
#ifndef _I2C_MODE_INITIAZLING_H_
#define _I2C_MODE_INITIAZLING_H_

#include "I2CControllerMode.h"

class I2CModeInitiazling : public I2CControllerMode
{
	private:
		static I2CControllerMode* sInstance;
	protected:
		I2CModeInitiazling() {};
	public:
		static I2CControllerMode* getInstance();
};

#endif