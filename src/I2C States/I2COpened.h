#pragma once
#ifndef _I2C_OPENED_H_
#define _I2C_OPENED_H_

#include "I2CState.h"

class I2COpened : public I2CState
{
	private:
		static I2CState* _instance;

	public:
		enum _t_Opened_Type
		{
			START_TRANSMITTED_SUCCESFULLY,
			STRAT_TRANSMITTED_UNSUCCESFULLY
		};

	protected:
		I2COpened() {};

	public:
		static I2CState* getInstance();

		virtual void handleStatusRegSignal(I2CTransmitter*, uint8_t) override;
		virtual void sendStartSignal(I2CTransmitter*) override;
};

#endif