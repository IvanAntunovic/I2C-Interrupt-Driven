#pragma once
#ifndef _I2C_CONTROLLER_H_
#define _I2C_CONTROLLER_H_

#include "I2CTransmitter.h"
#include "I2CReceiver.h"
#include "I2CState.h"
#include "I2CControllerMode.h"

#define REPEATED_START	true

//Codes for openPort() method
#define PORT_OPENED_OK						0
#define PORT_ALREADY_OPENED		           -1
#define	PORT_OPENED_NOK					   -2

//Codes for setMode() method
#define INVALID_ADDRESS					   -1
#define	MODE_SET_OK							0

//Codes for readBytes() method
#define BUFFER_EMPTY					   -1
#define PORT_NOT_OPENED                    -2
#define READ_OK							    0


class I2CState;
class I2CTransmitter;
class I2CReceiver;
class I2CControllerMode;

class I2CController
{
	private:
		I2CTransmitter*		i2cTransmitter;
		I2CReceiver*		i2cReceiver;
		CircularQueue		txQueue;
		CircularQueue		rxQueue;
		I2CState*			currentState;
		I2CControllerMode*	currentMode;
		uint8_t				address;
		int					clockFrequency;
		bool				isRepeatedStartEnabled;
		uint8_t				bytesToRead;

	private:
		friend class I2CState;
		friend class I2CController;
		friend class I2COpened;
		friend class I2CAdrWTransmittedACKRec;
		friend class I2CAddressRTransmitterACKReceivedState;
		friend class I2CDataTransmittedACKRec;
		friend class I2CRepeatedStartSent;;
		friend class I2CStartTransmitted;
		friend class DataReceivedACKReturnedI2CState;
		friend class DataReceivedNAKReturnedI2CState;
		

	private:
		void changeState(I2CState*);
		void changeMode(I2CControllerMode*);

	public:
		I2CController(uint8_t address = -1, int clockFrequency = 0);
		~I2CController();

		int8_t openPort();
		void closePort();

		// Methods for setting up the communication
		int8_t setMode(uint8_t address, int clockFrequency, bool isRepeatedStartEnabled = false);
		int8_t setMode(uint8_t address, bool isRepeatedStartEnabled = false);
		void setMode(bool isRepeatedStartEnabled);

		// Methods for output stream
		uint8_t writeBytes(unsigned char* bytes, unsigned char offset, unsigned char length);
		unsigned char availableForWrite();

		// Methods for input stream
		uint8_t readBytes(unsigned char* buffer, unsigned int length);
		uint8_t available();
};

#endif