#include "I2CTransmitter.h"

//
//#ifndef extern "C" { void __cxa_pure_virtual() { while (1); }}
//#endif

void I2CTransmitter::sendStartSignal()
{
	cout << "Sending Start Signal" << endl;
}

void I2CTransmitter::sendStopSignal()
{
	cout << "Sending Stop Signal" << endl;
}

void I2CTransmitter::sendTransmitSignal()
{
	cout << "Sending Transmit Signal" << endl;
}
