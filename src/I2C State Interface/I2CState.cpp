#include "I2CState.h"

void I2CState::handleStatusRegSignal(I2CTransmitter*, uint8_t) {}
void I2CState::sendStartSignal(I2CTransmitter*) {}
void I2CState::sendStopSignal(I2CTransmitter*) {}
void I2CState::sendTransmitSignal(I2CTransmitter*) {}
void I2CState::sendACKSignal(I2CTransmitter*) {}
void I2CState::sendNACKSignal(I2CTransmitter*) {}

void I2CState::changeState(I2CTransmitter* transmitter, I2CState* state)
{
	transmitter->changeState(state);
}