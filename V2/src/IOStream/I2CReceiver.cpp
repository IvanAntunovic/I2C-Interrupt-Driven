#include "I2CReceiver.h"
#include <iostream>

using namespace std;

void I2CReceiver::sendACKSignal()
{
	cout << "Sending ACK Signal" << endl;
}

void I2CReceiver::sendNACKSignal()
{
	cout << "Sending NACK Signal" << endl;
}