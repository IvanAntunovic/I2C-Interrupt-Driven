#pragma once
#ifndef _I2C_CLOSED_H_
#define _I2C_CLOSED_H_

#include "I2CState.h"

class I2CClosed : public I2CState
{
	private:
		static I2CState* i2cClosedInstance;

	protected:
		I2CClosed() {};

	public:
		static I2CState* getInstance();
		
};

#endif
