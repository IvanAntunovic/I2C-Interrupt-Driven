#include "I2CController.h"

int test(void)
{
	I2CController controller;

	uint8_t bytes[] = { 1, 2, 3, 4 ,5 };
	uint8_t readBuffer[5];

	controller.openPort();
	controller.setMode(0x10, 1000000UL, false);
	controller.writeBytes(bytes, 0, 3);

	controller.setMode(REPEATED_START);
	if (controller.readBytes(readBuffer, 5))
	{
		return -1;
	}
	controller.closePort();

	cout << "Bytes read" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << readBuffer[i] << endl;
	}
}

int test2(void)
{
	I2CController controller(0x30, 50000UL);

	uint8_t bytes[] = { 1, 2, 3, 4 ,5 };
	uint8_t readBuffer[5];

	controller.openPort();
	controller.setMode(REPEATED_START);
	if (controller.readBytes(readBuffer, 1))
	{
		return -1;
	}
	controller.closePort();

	cout << "Bytes read" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << readBuffer[i] << endl;
	}
	return 0;
}

int main(void)
{
	if (test2())
	{
		cout << "Error" << endl;
	}
}

