#pragma once
#ifndef _I2C_START_TRANSMITTED_H_
#define _I2C_START_TRANSMITTED_H_

#include "I2CTransmitter.h"

class I2CStartTransmitted : public I2CState
{
	private:
		static I2CState* i2cStartTransmittedInstance;

	public:
		enum _t_StartTransmittedType
		{
			ADR_W_TRANSMITTED_ACK_REC,
			ADR_W_TRANSMITTED_NACK_REC,
			ADR_R_TRANSMITTED_ACK_REC,
			ADR_R_TRANSMITTED_NACK_REC
		};

	protected:
		I2CStartTransmitted() {}

	public:
		static I2CState* getInstance();

		virtual void handleStatusRegSignal(I2CTransmitter*, uint8_t) override;
		virtual void sendTransmitSignal(I2CTransmitter*) override;
};

#endif

