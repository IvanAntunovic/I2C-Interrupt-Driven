/*
 * I2CPort.cpp
 *
 * Created: 8/4/2017 9:13:37 PM
 *  Author: fairenough
 */ 

#ifndef TWILIB_H_
#define TWILIB_H_

#include <avr/interrupt.h>
#include "CircularQueue.h"

// Function declarations
uint8_t TWITransmitData(void *const TXdata, uint8_t dataLen, uint8_t repStart);
void TWIInit(void);
uint8_t TWIReadData(uint8_t TWIaddr, uint8_t bytesToRead, uint8_t repStart);
uint8_t isTWIReady(void);


extern "C" { void TWI_vect (void) __attribute__ ((signal, __INTR_ATTRS)); }
	
class I2CPort
{
	private:
		uint8_t deviceAddress;
		bool isRepeatedStart;
		static I2CPort* sInstance;
		CircularQueue txQueue;
		CircularQueue rxQueue;
		uint8_t bytesToRead;
		
		friend  void TWI_vect (void);
		
	public:
		I2CPort();
		int8_t writeBytes(uint8_t* buffer, uint8_t offset, uint8_t length);	
		int8_t readBytes(uint8_t* buffer, uint8_t offset, uint8_t length);	
		
		void open(void);
		void close(void);
		
		void selectSlaveDevice(uint8_t deviceAddress, bool isRepeatedStart);
		bool isReady(void);
		
		int8_t requestData(void);
		
		inline uint8_t available() { return this->rxQueue.available(); };
		
	private:
		inline void interruptHandler(void)  __attribute__((always_inline));
	 	inline int8_t loadUpQueue(uint8_t* buffer, uint8_t offset, uint8_t length, uint8_t readWrite)  __attribute__((always_inline));
		inline void start(void) __attribute__((always_inline));
};

#endif // TWICOMMS_H_