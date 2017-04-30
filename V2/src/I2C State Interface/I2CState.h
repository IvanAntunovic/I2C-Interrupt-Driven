#pragma once
#ifndef _I2C_STATE_H_
#define _I2C_STATE_H_

#include <iostream>
#include "I2CController.h"

class I2CController;
using namespace std;

class I2CState
{
	private:
		friend class I2CController;

	protected:
		void changeState(I2CController&, I2CState*);

	public:
		virtual void handleStatusRegSignal(I2CController&, uint8_t);

};

#endif