#pragma once

#ifndef _DATA_RECEIVED_NAK_RETURNED_I2C_STATE_H_
#define _DATA_RECEIVED_NAK_RETURNED_I2C_STATE_H_

#include "I2CState.h"

class DataReceivedNAKReturnedI2CState : public I2CState 
{
	private:
		static I2CState* sInstance;
	protected:
		DataReceivedNAKReturnedI2CState() {}
	public:
		static I2CState* getInstance(void);
		void handleStatusRegSignal(I2CController&, uint8_t) override;

};

#endif // !_DATA_RECEIVED_NAK_RETURNED_I2C_STATE_H_