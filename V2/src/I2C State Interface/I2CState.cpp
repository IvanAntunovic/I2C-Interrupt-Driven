#include "I2CState.h"

void I2CState::handleStatusRegSignal(I2CController&, uint8_t) {}

void I2CState::changeState(I2CController& controller, I2CState* state)
{
	controller.changeState(state);
}