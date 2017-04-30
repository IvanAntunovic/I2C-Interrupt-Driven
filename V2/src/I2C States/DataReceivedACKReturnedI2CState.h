#pragma once
#ifndef _DATA_RECEIVED_ACK_RETURNED_I2C_STATE_H_
#define	_DATA_RECEIVED_ACK_RETURNED_I2C_STATE_H_

#include "I2CState.h"

class DataReceivedACKReturnedI2CState : public I2CState
{
	private:
		static I2CState* sInstance;

	public:
		enum _t_DataReceivedACKReturned
		{
			DATA_RECEIVED_ACK_RETURNED,
			DATA_RECEIVED_NAK_RETURNED,
			ARBITRATION_LOST
		};
	protected:
		DataReceivedACKReturnedI2CState() {};
	
	public:
		static I2CState* getInstance(void);
		virtual void handleStatusRegSignal(I2CController&, uint8_t) override;
};

#endif // !_DATA_RECEIVED_ACK_RETURNED_I2C_STATE_H_
