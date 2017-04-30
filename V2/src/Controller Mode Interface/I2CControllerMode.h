#pragma once
#ifndef _I2C_CONTROLLER_MODE
#define _I2C_CONTROLLER_MODE
#include "I2CController.h"

class I2CController;

class I2CControllerMode
{
	private:
		// Friend class kako bismo mogli pristupiti u funkciji changeMode privatnim 
		// varijablama objekta klase I2CController
		friend class I2CController;

	protected:
		void changeMode(I2CController&, I2CControllerMode*);
};

#endif