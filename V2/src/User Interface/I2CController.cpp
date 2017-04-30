#include "I2CController.h"
#include "I2COpened.h"
#include "I2CClosed.h"
#include "I2CRepeatedStartSent.h"
#include "I2CModeIdle.h"
#include "I2CModeInitializing.h"
#include "I2CModeMasterTransmitter.h"
#include "MasterReceiverI2CMode.h"
#include "DataReceivedACKReturnedI2CState.h"
#include "DataReceivedNAKReturnedI2CState.h"

#define DEFAULT_ADDRESS -1

I2CController::I2CController(uint8_t address, int clockFrequency)
{
	this->i2cTransmitter		 = new I2CTransmitter();
	this->i2cReceiver			 = new I2CReceiver();
	this->currentState			 = NULL;
	this->currentMode			 = NULL;

	this->isRepeatedStartEnabled = false;
	this->bytesToRead			 =  0;
	this->address				 = address;
	this->clockFrequency		 = clockFrequency;

	cout << "Opened state running!" << endl;
}

I2CController::~I2CController()
{
	delete i2cTransmitter;
	delete i2cReceiver;
	delete currentState;
	delete currentMode;
}

int8_t I2CController::openPort()
{	
	if (this->currentState == I2COpened::getInstance())
	{
		cout << "Port already opened!" << endl;
		return PORT_ALREADY_OPENED;
	}
	
	this->currentState	= I2COpened::getInstance();
	this->currentMode	= I2CModeIdle::getInstance();
	cout << "Port opened!" << endl;
	cout << "Idle Mode running" << endl;

	return PORT_OPENED_OK;
}

void I2CController::closePort()
{
	this->currentState = I2CClosed::getInstance();
	this->currentMode = I2CModeIdle::getInstance();
	cout << "Idle Mode running" << endl;
}

void I2CController::changeState(I2CState* newState)
{
	this->currentState = newState;
}

void I2CController::changeMode(I2CControllerMode* newMode)
{
	this->currentMode = newMode;
}


int8_t I2CController::setMode(uint8_t address, int clockFrequency, bool isRepeatedStartEnabled)
{
	if (address & (1 << 8) || address < 0)
	{
		return INVALID_ADDRESS;
	}

	this->clockFrequency = clockFrequency;
	this->address = address;
	this->isRepeatedStartEnabled = isRepeatedStartEnabled;

	return MODE_SET_OK;
}

int8_t I2CController::setMode(uint8_t address, bool isRepeatedStartEnabled)
{
	// check if address is in 7-bit format
	if (address & (1 << 8) || address < 0)
	{
		return INVALID_ADDRESS;
	}

	this->isRepeatedStartEnabled = isRepeatedStartEnabled;
	this->address = address;

	return MODE_SET_OK;
}

void I2CController::setMode(bool isRepeatedStartEnabled)
{
	this->isRepeatedStartEnabled = isRepeatedStartEnabled;
}

uint8_t I2CController::available()
{
	return this->rxQueue.getAvailableItems();
}

uint8_t I2CController::readBytes(unsigned char* buffer, unsigned int length)
{
	// Prvotno je zamisljeno da ova metoda vraca broj byteova koji su procitani
	// Mozda je bolje umjesto informacije vracati statusne kodove ?
	//unsigned char bytesRead = 0;
	uint8_t status = 0;

	if (this->currentState != I2COpened::getInstance() &&
		this->currentState != I2CRepeatedStartSent::getInstance())
	{
		return PORT_NOT_OPENED;
	}

	this->bytesToRead = length;
	this->changeMode(MasterReceiverI2CMode::getInstance());
	
	while (status != 1)
	{
		this->currentState->handleStatusRegSignal(*this, status);

		if (this->currentState == I2COpened::getInstance() || 
			this->currentState == I2CRepeatedStartSent::getInstance())
		{
			for (int i = 0; i < length; ++i)
			{
				if (!this->rxQueue.isEmpty())
				{
					this->rxQueue.dequeue(buffer);
					buffer++;
				}
				else
				{
					//return BUFFER_EMPTY;
				}
			}
			// After we finish reading all bytes 
			break;
		}
	}
	//return bytesRead;
	return READ_OK;
}


unsigned char I2CController::availableForWrite()
{
	return BUFFER_SIZE - this->txQueue.getAvailableItems();
}

uint8_t I2CController::writeBytes(unsigned char* bytes, unsigned char offset, unsigned char length)
{
	uint8_t status = 0;
	uint8_t bytesWrittenCnt = 0;

	if (this->currentState != I2COpened::getInstance() &&
		this->currentState != I2CRepeatedStartSent::getInstance())
	{
		return PORT_NOT_OPENED;
	}

	this->currentMode = I2CModeInitiazling::getInstance();
	cout << "Initializing Mode" << endl;

	//bytesWrittenCnt = this->i2cTransmitter->writeBytes(bytes, offset, length);

	for (int i = offset; i < length; i++)
	{
		if (txQueue.enqueue(bytes[i]))
		{
			bytesWrittenCnt++; // je li ima smisla vracat zapisan broj byteova?
		}
	}

	this->currentMode = I2CModeMasterTransmitter::getInstance();
	cout << "Master Transmitter Mode" << endl;

	while (status != 1)
	{
		this->currentState->handleStatusRegSignal(*this, status);
		if (this->currentState == I2COpened::getInstance() || this->currentState == I2CRepeatedStartSent::getInstance())
		{
			break;
		}
	}
	return bytesWrittenCnt;
}