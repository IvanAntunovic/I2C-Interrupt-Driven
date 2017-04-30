#pragma once
#ifndef  _MASTER_RECEIVER_I2C_MODE_H_
#define  _MASTER_RECEIVER_I2C_MODE_H_

#include "I2CControllerMode.h"

class MasterReceiverI2CMode : public I2CControllerMode
{
	private:
		static I2CControllerMode* sInstance;

	protected:
		MasterReceiverI2CMode() {};

	public:
		static I2CControllerMode* getInstance(void);
};

#endif // ! _MASTER_RECEIVER_I2C_MODE_H_
