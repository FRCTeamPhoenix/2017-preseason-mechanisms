/*
 * Arm.h
 *
 *  Created on: Dec 5, 2016
 *      Author: joshc
 */

#include "WPILib.h"
#include "constants.h"
#ifndef SRC_ARM_H_
#define SRC_ARM_H_

class Arm
{
public:
	enum state {
		IDLE,
		MOVING,
		AUTO
	};

private:
	float m_joystickX;

	state m_state;
	Talon * m_armMotorR;
	Talon * m_armMotorL;
	Encoder * m_encoderR;
	Encoder * m_encoderL;
	DigitalInput * m_armLimitR;
	DigitalInput * m_armLimitL;
	Joystick * m_gamepad;

public:
	Arm(
			Talon * armMotorR,
			Talon * armMotorL,
			Encoder * encoderR,
			Encoder * encoderL,
			DigitalInput * armLimitR,
			DigitalInput * armLimitL,
			Joystick * gamepad);
	virtual ~Arm();
	void run();
	void stop();
	void moving();
	void getGamepadWithDeadzone();
	bool checkOut();
	bool checkIn();
	bool hasJoystickMoved();


};

#endif /* SRC_ARM_H_ */
