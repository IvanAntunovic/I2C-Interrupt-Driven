#ifndef _I2C_DATA_TRANSMITTED_ACK_REC_H_
#define _I2C_DATA_TRANSMITTED_ACK_REC_H_

#include "I2CTransmitter.h"

class I2CDataTransmittedACKRec : public I2CState
{
	private:
		static I2CState* i2cDataTransmittedACKRecInstance;

	public:
		enum _t_DataTransmittedACKRec
		{
			DATA_TRANSMITTED_ACK_REC,
			DATA_TRANSMITTED_NACK_REC,
			REPEATED_START_SENT
		};

	protected:
		I2CDataTransmittedACKRec() {};

	public:
		static I2CState* getInstance();

		virtual void handleStatusRegSignal(I2CTransmitter*, uint8_t) override;
		virtual void sendTransmitSignal(I2CTransmitter*) override;
		virtual void sendStartSignal(I2CTransmitter*) override;
		virtual void sendStopSignal(I2CTransmitter*) override;

};

#endif // _I2C_STATE_H_