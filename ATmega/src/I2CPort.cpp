/*
 * I2CPort.cpp
 *
 * Created: 8/4/2017 9:15:05 PM
 *  Author: fairenough
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "I2CPort.h"
#include "I2CStatusCodes.h"

I2CPort* I2CPort::sInstance = NULL;

I2CPort::I2CPort(void)
{
	I2CPort::sInstance = this;
	this->bytesToRead = 0;
	this->deviceAddress = 0;
	this->isRepeatedStart = false;
}

void I2CPort::open(void)
{
	TWIInfo.mode = Ready;
	TWIInfo.errorCode = 0xFF;
	TWIInfo.repStart = 0;

	// Set pre-scalers (no pre-scaling)
	TWSR = 0;
	// Set bit rate
	TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;
	// Enable TWI and interrupt
	TWCR = (1 << TWIE) | (1 << TWEN);
	
	sei();
}

void I2CPort::close(void)
{
	// Set bit rate
	TWBR = 0;
	// Disable TWI and interrupt
	TWCR &= ~(1 << TWIE) | ~(1 << TWEN);
}

bool I2CPort::isReady(void)
{
	return (TWIInfo.mode == Ready) | (TWIInfo.mode == RepeatedStartSent) ? true : false;
}

void I2CPort::selectSlaveDevice(uint8_t deviceAddress, bool isRepeatedStart)
{
	this->deviceAddress = deviceAddress;
	this->isRepeatedStart = isRepeatedStart;
	
	// Set repeated start mode
	TWIInfo.repStart = this->isRepeatedStart;
}

int8_t I2CPort::requestData(void)
{
	uint8_t dummyVariable;
	
	if (!this->isReady())
	{
		return I2C_PORT_BUSY;
	}
	
	this->loadUpQueue(&dummyVariable, 0, 0, TWI_READ);
	this->start();
	
	return I2C_PORT_OK;
}

int8_t I2CPort::loadUpQueue(uint8_t* buffer, uint8_t offset, uint8_t length, uint8_t readWrite)
{
	if (length > BUFFER_SIZE || length < 0)
	{
		return I2C_PORT_BUFFER_LEN_NOK;
	}
	
	if (buffer == NULL)
	{
		return I2C_PORT_BUFFER_NULL_PTR;
	}
	
	if (offset < 0 || offset > length)
	{
		return I2C_PORT_OFFSET_NOK;
	}
	
	this->txQueue.flush();
	
	// Copy data into the transmit buffer
	uint8_t address = readWrite == TWI_WRITE ? (this->deviceAddress << 1) : (this->deviceAddress << 1 | 0x01);
	this->txQueue.enqueue(address);
	
	for (int i = 0; i < length; i++)
	{
		this->txQueue.enqueue(buffer[i]);
	}
	
	return I2C_PORT_OK;
}

void I2CPort::start(void)
{	
	// If a repeated start has been sent, then devices are already listening for an address
	// and another start does not need to be sent.
	if (TWIInfo.mode == RepeatedStartSent)
	{
		uint8_t aByte;
				
		// Remove byte for sending
		this->txQueue.dequeue(&aByte);
				
		TWIInfo.mode = Initializing;
		TWDR = aByte; // Load data to transmit buffer
		TWISendTransmit(); // Send the data
	}
	else // Otherwise, just send the normal start signal to begin transmission.
	{
		TWIInfo.mode = Initializing;
		TWISendStart();
	}
}

int8_t I2CPort::writeBytes(uint8_t* buffer, uint8_t offset, uint8_t length)
{
	int8_t retVal;
	
	if (!this->isReady())
	{
		return I2C_PORT_BUSY;
	}
	
	retVal = this->loadUpQueue(buffer, offset, length, TWI_WRITE);	
	if ( retVal != I2C_PORT_OK )
	{
		return retVal;
	}
	
	this->start();

	return I2C_PORT_OK;
}

int8_t I2CPort::readBytes(uint8_t* buffer, uint8_t offset, uint8_t length)
{
	uint8_t byteReceived;
	uint8_t bytesRead = 0;
	
	if (length > BUFFER_SIZE || length < 0)
	{
		return I2C_PORT_BUFFER_LEN_NOK;
	}
	
	if (buffer == NULL)
	{
		return I2C_PORT_BUFFER_NULL_PTR;
	}
	
	if (offset < 0 || offset > length)
	{
		return I2C_PORT_OFFSET_NOK;
	}
	
	for (int index = offset; index < length; ++index, ++bytesRead)
	{
		if (this->rxQueue.dequeue(&byteReceived) != QUEUE_OK)
		{
			return bytesRead;
		}
		
		buffer[index] = byteReceived;
	}
	
	return I2C_PORT_OK;
}

void I2CPort::interruptHandler(void)
{
	switch (TWI_STATUS)
	{
		// ----\/ ---- MASTER TRANSMITTER OR WRITING ADDRESS ----\/ ----  //
		case TWI_MT_SLAW_ACK: // SLA+W transmitted and ACK received
		// Set mode to Master Transmitter
		TWIInfo.mode = MasterTransmitter;
		case TWI_START_SENT: // Start condition has been transmitted
		case TWI_MT_DATA_ACK: // Data byte has been transmitted, ACK received

		//if (TXBuffIndex < TXBuffLen) // If there is more data to send
		if ( !this->txQueue.isEmpty() )
		{
			uint8_t aByte;
			
			this->txQueue.dequeue(&aByte);
			//TWDR = TWITransmitBuffer[TXBuffIndex++]; // Load data to transmit buffer
			TWDR = aByte;
			TWIInfo.errorCode = TWI_NO_RELEVANT_INFO;
			TWISendTransmit(); // Send the data
		}
		// This transmission is complete however do not release bus yet
		else if (TWIInfo.repStart)
		{
			TWIInfo.errorCode = 0xFF;
			TWISendStart();
		}
		// All transmissions are complete, exit
		else
		{
			TWIInfo.mode = Ready;
			TWIInfo.errorCode = 0xFF;
			TWISendStop();
		}
		break;
		
		// ----\/ ---- MASTER RECEIVER ----\/ ----  //
		
		case TWI_MR_SLAR_ACK: // SLA+R has been transmitted, ACK has been received
		// Switch to Master Receiver mode
		TWIInfo.mode = MasterReceiver;
		// If there is more than one byte to be read, receive data byte and return an ACK
		//if (RXBuffIndex < RXBuffLen - 1)
		if (this->txQueue.available() < this->bytesToRead - 1)
		{
			TWIInfo.errorCode = TWI_NO_RELEVANT_INFO;
			TWISendACK();
		}
		// Otherwise when a data byte (the only data byte) is received, return NACK
		else
		{
			TWIInfo.errorCode = TWI_NO_RELEVANT_INFO;
			TWISendNACK();
		}
		break;
		
		case TWI_MR_DATA_ACK: // Data has been received, ACK has been transmitted.
		
		/// -- HANDLE DATA BYTE --- ///
		//TWIReceiveBuffer[RXBuffIndex++] = TWDR;
		this->rxQueue.enqueue(TWDR);
		// If there is more than one byte to be read, receive data byte and return an ACK
		//if (RXBuffIndex < RXBuffLen-1)
		if (this->txQueue.available() < this->bytesToRead - 1)
		{
			TWIInfo.errorCode = TWI_NO_RELEVANT_INFO;
			TWISendACK();
		}
		// Otherwise when a data byte (the only data byte) is received, return NACK
		else
		{
			TWIInfo.errorCode = TWI_NO_RELEVANT_INFO;
			TWISendNACK();
		}
		break;
		
		case TWI_MR_DATA_NACK: // Data byte has been received, NACK has been transmitted. End of transmission.
		
		/// -- HANDLE DATA BYTE --- ///
		
		//TWIReceiveBuffer[RXBuffIndex++] = TWDR;
		this->rxQueue.enqueue(TWDR);
		// This transmission is complete however do not release bus yet
		if (TWIInfo.repStart)
		{
			TWIInfo.errorCode = 0xFF;
			TWISendStart();
		}
		// All transmissions are complete, exit
		else
		{
			TWIInfo.mode = Ready;
			TWIInfo.errorCode = 0xFF;
			TWISendStop();
		}
		break;
		
		// ----\/ ---- MT and MR common ----\/ ---- //
		
		case TWI_MR_SLAR_NACK: // SLA+R transmitted, NACK received
		case TWI_MT_SLAW_NACK: // SLA+W transmitted, NACK received
		case TWI_MT_DATA_NACK: // Data byte has been transmitted, NACK received
		case TWI_LOST_ARBIT: // Arbitration has been lost
		// Return error and send stop and set mode to ready
		if (TWIInfo.repStart)
		{
			TWIInfo.errorCode = TWI_STATUS;
			TWISendStart();
		}
		// All transmissions are complete, exit
		else
		{
			TWIInfo.mode = Ready;
			TWIInfo.errorCode = TWI_STATUS;
			TWISendStop();
		}
		break;
		case TWI_REP_START_SENT: // Repeated start has been transmitted
		// Set the mode but DO NOT clear TWINT as the next data is not yet ready
		TWIInfo.mode = RepeatedStartSent;
		break;
		
		// ----\/ ---- SLAVE RECEIVER ----\/ ----  //
		
		// TODO  IMPLEMENT SLAVE RECEIVER FUNCTIONALITY
		
		// ----\/ ---- SLAVE TRANSMITTER ----\/ ----  //
		
		// TODO  IMPLEMENT SLAVE TRANSMITTER FUNCTIONALITY
		
		// ----\/ ---- MISCELLANEOUS STATES ----\/ ----  //
		case TWI_NO_RELEVANT_INFO: // It is not really possible to get into this ISR on this condition
		// Rather, it is there to be manually set between operations
		break;
		case TWI_ILLEGAL_START_STOP: // Illegal START/STOP, abort and return error
		TWIInfo.errorCode = TWI_ILLEGAL_START_STOP;
		TWIInfo.mode = Ready;
		TWISendStop();
		break;
	}
}

ISR (TWI_vect)
{
	I2CPort::sInstance->interruptHandler();
}
