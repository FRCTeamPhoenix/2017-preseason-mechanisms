#include "WPILib.h"

#include "LimitSwitch.h"

class Robot : public SampleRobot
{
  static const uint32_t LIMIT_SWITCH_PORT = 0;

  LimitSwitch m_limitSwitch;

public:
  Robot()
    : m_limitSwitch(LIMIT_SWITCH_PORT)
  {
    SmartDashboard::init();
  }

  void OperatorControl()
  {
    while (IsOperatorControl() && IsEnabled())
    {
      bool pressed = m_limitSwitch.get();
      SmartDashboard::PutString("DB/String 0", pressed ? "true" : "false");

      Wait(0.005); // wait 5ms to avoid hogging CPU cycles
    }
  }
};

START_ROBOT_CLASS(Robot)
