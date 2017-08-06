#pragma once
#ifndef _CIRCULARQUEUE_H_
#define _CIRCULARQUEUE_H_

#include "stdint.h"

#define BUFFER_SIZE 32
#define BUFFER_MASK (BUFFER_SIZE - 1)

#define QUEUE_OK	 0
#define QUEUE_NOK	-1

class CircularQueue
{
	private:
		volatile uint8_t head;
		volatile uint8_t tail;
		volatile uint8_t buffer[BUFFER_SIZE];
		volatile uint8_t availableItems;

	public:
		CircularQueue(void);
		void flush(void);
		uint8_t available(void);
		bool isEmpty(void);
		bool isFull(void);
		int8_t enqueue(uint8_t byte);
		int8_t dequeue(uint8_t* byte);
};

#endif // DEBUG

