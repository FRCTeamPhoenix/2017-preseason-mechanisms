#include <iostream>
#include "Arm.h"
#include "WPILib.h"
#include "constants.h"
#include "sys/stat.h"

using namespace std;

class Robot : public SampleRobot
{

	Arm * m_arm;

public:
	Robot():
		m_arm()
{
}
	void Autonomous()
	{
		while(IsAutonomous() && IsEnabled())
		{

		}
	}
	void OperatorControl()
	{
		while(IsOperatorControl() && IsEnabled())
		{

		}
	}
	void Test()
	{
		while(IsTest() && IsEnabled())
		{

		}
	}
};
START_ROBOT_CLASS(Robot)
