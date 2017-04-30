#ifndef _I2C_DATA_TRANSMITTED_ACK_REC_H_
#define _I2C_DATA_TRANSMITTED_ACK_REC_H_

#include "I2CController.h"

class I2CDataTransmittedACKRec : public I2CState
{
private:
	static I2CState* sInstance;

public:
	enum _t_DataTransmittedACKRec
	{
		DATA_TRANSMITTED_ACK_REC,
		DATA_TRANSMITTED_NACK_REC,
		REPEATED_START_SENT,
		ARBITRATION_LOST
	};

protected:
	I2CDataTransmittedACKRec() {};

public:
	static I2CState* getInstance();

	virtual void handleStatusRegSignal(I2CController&, uint8_t) override;
};

#endif // _I2C_STATE_H_