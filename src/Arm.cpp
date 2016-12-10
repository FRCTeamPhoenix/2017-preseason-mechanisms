/*
 * Arm.cpp
 *
 *  Created on: Dec 5, 2016
 *      Author: joshc
 */

#include "Arm.h"

Arm::Arm(
		Talon * m_armMotorR,
		Talon * m_armMotorL,
		Encoder * m_encoderR,
		Encoder * m_encoderL,
		DigitalInput * m_armLimitR,
		DigitalInput * m_armLimitL
) {
	// TODO Auto-generated constructor stub

}

Arm::~Arm() {
	// TODO Auto-generated destructor stub
}

bool Arm::hasJoystickMoved(){
	if(fabs(m_joystickX) < 0.05f){
		return true;
	}
	return false;
}

void Arm::stop(){
	m_armMotorL->Set(0);
	m_armMotorR->Set(0);
}

void Arm::moving(){
	m_armMotorL->Set(m_joystickX);
	m_armMotorR->Set(m_joystickX);
}

void Arm::run() {
	switch (m_state) {
	case IDLE:
		stop();
		if(!hasJoystickMoved())
		{
			break;
		}
		m_state = MOVING;
		break;

	case MOVING:
		getGamepadWithDeadzone();
		moving();
		if(hasJoystickMoved())
		{
			break;
		} else {

	case AUTO:
		break;
		}
	}
}
