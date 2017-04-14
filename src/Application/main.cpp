#include "I2CController.h"
#include <stdio.h>

void repeatedStartTest(I2CController& controller)
{
	controller.setMode(30, 50000, REPEATED_START);
	unsigned char buffer[] = { '1' , '2' , '3'};
	controller.write(buffer, 0, sizeof(buffer) / sizeof(buffer[0]) - 1);
	controller.setMode(60, REPEATED_START);
	controller.write(buffer, 0, sizeof(buffer) / sizeof(buffer[0]));
	cout << endl;
}

void nonRepStartTest(I2CController& controller)
{
	controller.setMode(30, 50000, REPEATED_START);
	unsigned char buffer[] = { '1' , '2', '3' };
	controller.write(buffer, 0, sizeof(buffer) / sizeof(buffer[0]) - 1);
	controller.setMode(60);
	controller.write(buffer, 0, sizeof(buffer) / sizeof(buffer[0]));
	cout << endl;
}

int main(void)
{
	I2CController controller;
	cout << endl;
	
	repeatedStartTest(controller);
	nonRepStartTest(controller);
	
	return 0;	
}