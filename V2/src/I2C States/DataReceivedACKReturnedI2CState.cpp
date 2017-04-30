#include "DataReceivedACKReturnedI2CState.h"
#include "DataReceivedNAKReturnedI2CState.h"
#include "I2CRepeatedStartSent.h"
#include "I2COpened.h"
#include "I2CModeIdle.h"

I2CState* DataReceivedACKReturnedI2CState::sInstance = NULL;

I2CState* DataReceivedACKReturnedI2CState::getInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new DataReceivedACKReturnedI2CState();
	}
	return sInstance;
}

void DataReceivedACKReturnedI2CState::handleStatusRegSignal(I2CController& controller, uint8_t statusRegisterCode)
{
	if (statusRegisterCode == DATA_RECEIVED_ACK_RETURNED)
	{
		static uint8_t TWDR = '2';

		if (!controller.rxQueue.enqueue(TWDR))
		{
			//ERROR while receiving data
			controller.i2cReceiver->sendNACKSignal();
		}

		//Check if how many items we enqueued on the Receiver Queue
		//On the last byte to be read we need to send NACK Signal
		//Otherwise we need to send NACK
		if (controller.bytesToRead > controller.rxQueue.getAvailableItems())
		{
			controller.i2cReceiver->sendACKSignal();
			// Stay in the same state
		}
		else
		{
			controller.i2cReceiver->sendNACKSignal();
			controller.changeState(DataReceivedNAKReturnedI2CState::getInstance());
		}
		TWDR++;
	}
	else if (statusRegisterCode == DATA_RECEIVED_NAK_RETURNED || statusRegisterCode == ARBITRATION_LOST)
	{
		if (controller.isRepeatedStartEnabled)
		{
			// ERROR - NOT READY
			controller.i2cTransmitter->sendStartSignal();
			controller.changeState(I2CRepeatedStartSent::getInstance());
			// no need to change Mode, we stay in Master Receiver Mode
		}
		else
		{
			// ERROR - BUT READY FOR NEXT READ/WRITE OPERATIONS
			controller.i2cTransmitter->sendStopSignal();
			controller.changeState(I2COpened::getInstance());
			controller.changeMode(I2CModeIdle::getInstance());
		}
	}
}