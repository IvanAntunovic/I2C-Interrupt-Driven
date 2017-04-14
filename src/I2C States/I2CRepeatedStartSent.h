#pragma once
#ifndef _I2C_REPEATED_START_SENT_H_
#define _I2C_REPEATED_STAWRT_SENT_H_

#include "I2CState.h"

class I2CRepeatedStartSent : public I2CState
{
	private:
		static I2CState* repeatedStartSentInstance;

	public:
		enum _t_RepeatedStartTransmittedType
		{
			ADR_W_TRANSMITTED_ACK_REC,
			ADR_W_TRANSMITTED_NACK_REC,
			ADR_R_TRANSMITTED_ACK_REC,
			ADR_R_TRANSMITTED_NACK_REC
		};

	protected:
		I2CRepeatedStartSent() {}

	public:
		static I2CState* getInstance();

		virtual void handleStatusRegSignal(I2CTransmitter*, uint8_t) override;
		virtual void sendTransmitSignal(I2CTransmitter*) override;
		virtual void sendStartSignal(I2CTransmitter*) override;
		//virtual void sendStopSignal(I2CTransmitter*) override;
};

#endif