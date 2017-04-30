#pragma once
#ifndef _I2C_RECEIVER_H_
#define _I2C_RECEIVER_H_

#include <stdlib.h>
#include "CircularQueue.h"
#include "Readable.h"
#include "I2CController.h"
#include <stdint.h>

class I2CController;

class I2CReceiver
{
	public:
		void sendACKSignal(void);
		void sendNACKSignal(void);
};

#endif //!_I2C_RECEIVER_H_