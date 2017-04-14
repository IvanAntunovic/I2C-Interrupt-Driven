#pragma once
#ifndef _I2C_ADR_W_TRANSMITTED_ACK_REC_H_
#define _I2C_ADR_W_TRANSMITTED_ACK_REC_H_

#include "I2CState.h"

class I2CAdrWTransmittedACKRec : public I2CState
{
	private:
		static I2CState* i2cAdrWTransmittedAckRecInstance;

	public:
		enum _t_AdrWTransmittedACKRec
		{
			DATA_TRANSMITTED_ACK_REC,
			DATA_TRANSMITTED_NACK_REC,
			ARBITRATION_LOST
		};

	protected:
		I2CAdrWTransmittedACKRec() {};

	public:
		static I2CState* getInstance();
	
		virtual void handleStatusRegSignal(I2CTransmitter*, uint8_t) override;
		virtual void sendStopSignal(I2CTransmitter*) override;
		virtual void sendTransmitSignal(I2CTransmitter*) override;

};

#endif //!_I2C_DATA_TRANSMITTED_ACK_REC_H_