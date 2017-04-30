#pragma once
#ifndef _I2C_ADRESS_R_TRANSMITTED_ACK_RECEIVED_STATE_H_
#define _I2C_ADRESS_R_TRANSMITTED_ACK_RECEIVED_STATE_H_

#include "I2CState.h"

class I2CAddressRTransmitterACKReceivedState : public I2CState
{
	private:
		static I2CState* sInstance;
	
	public:
		enum _t_AddressRTransmitterACKReceived
		{
			DATA_RECEIVED_ACK_RETURNED,
			DATA_RECEIVED_NAK_RETURNED,
			ARBITRATION_LOST
		};

	protected:
		I2CAddressRTransmitterACKReceivedState() {};

	private:
		virtual void handleStatusRegSignal(I2CController&, uint8_t) override;

	public:
		static I2CState* getInstance();

};

#endif