#include "WPILib.h"

#include "AutoController.h"
#include "ConfigEditor.h"
#include "LimitSwitch.h"

class Robot : public SampleRobot
{
    static const uint32_t LIMIT_SWITCH_PORT = 0;

    AutoController m_auto;
    ConfigEditor m_config;
    LimitSwitch m_limitSwitch;

public:
    Robot()
        : m_limitSwitch(LIMIT_SWITCH_PORT)
    {
    }

    void RobotInit()
    {
        SmartDashboard::init();
        m_config.showAllKeys();
    }

    void OperatorControl()
    {
        while (IsOperatorControl() && IsEnabled())
        {
            bool pressed = m_limitSwitch.get();
            SmartDashboard::PutString("DB/String 0", pressed ? "true" : "false");

            m_config.update();

            Wait(0.005); // wait 5ms to avoid hogging CPU cycles
        }
    }

    void Autonomous()
    {
        while (IsAutonomous() && IsEnabled())
        {
            m_auto.run();

            Wait(0.005); // wait 5ms to avoid hogging CPU cycles
        }
    }
};

START_ROBOT_CLASS(Robot)
