#include "CircularQueue.h"

CircularQueue::CircularQueue()
{
	head = 0;
	tail = 0;
	availableItems = 0;

	for (unsigned char i = 0; i < BUFFER_SIZE; ++i)
	{
		buffer[i] = 0;
	}
}

bool CircularQueue::isAvailable()
{
	if (availableItems)
	{
		return true;
	}
	return false;
}

unsigned char CircularQueue::getAvailableItems()
{
	return availableItems;
}

bool CircularQueue::isEmpty()
{
	if (availableItems)
	{
		return false;
	}
	return true;
}

bool CircularQueue::isFull()
{
	if (availableItems == BUFFER_SIZE)
	{
		return true;
	}
	return false;
}

bool CircularQueue::enqueue(unsigned char element)
{
	if (isFull())
	{
		return false;
	}

	this->tail = (this->tail + 1) & BUFFER_MASK;
	buffer[this->tail] = element;
	++availableItems;

	return true;
}

bool CircularQueue::dequeue(unsigned char* byte)
{
	if (isEmpty())
	{
		return false;
	}

	this->head = (this->head + 1) & BUFFER_MASK;
	*byte = buffer[this->head];
	--availableItems;

	return true;
}

