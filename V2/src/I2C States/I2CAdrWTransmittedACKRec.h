#pragma once
#ifndef _I2C_ADR_W_TRANSMITTED_ACK_REC_H_
#define _I2C_ADR_W_TRANSMITTED_ACK_REC_H_

#include "I2CState.h"

class I2CAdrWTransmittedACKRec : public I2CState
{
private:
	static I2CState* sInstance;

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

	virtual void handleStatusRegSignal(I2CController&, uint8_t) override;

};

#endif //!_I2C_DATA_TRANSMITTED_ACK_REC_H_