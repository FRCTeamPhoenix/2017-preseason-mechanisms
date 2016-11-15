#include "WPILib.h"
#include "SmartTalon.h"

/**
 * This is a quick sample program to show how to use the new Talon SRX over CAN.
 * This particular sample demonstrates running a basic PID control loop with an
 *   analog potentiometer.
 *
 */
class Robot : public SampleRobot
{
    SmartTalon m_smartTalon2;
    SmartTalon m_smartTalon4;

    Joystick m_gamepad;


//    CANTalon m_motor4;

public:
    Robot ()
            :
                m_smartTalon2 (2, 2000, 2000),
                m_smartTalon4 (4, 2000, 2000),

                m_gamepad(0)

//                m_motor4 (4)
    // Initialize the Talon as device 1. Use the roboRIO web
    // interface to change the device number on the m_motors.
    {
        // This sets the mode of the m_motor. The options are:
        // kPercentVbus: basic throttle; no closed-loop.
        // kCurrent: Runs the motor with the specified current if possible.
        // kSpeed: Runs a PID control loop to keep the motor going at a constant
        //   speed using the specified sensor.
        // kPosition: Runs a PID control loop to move the motor to a specified move
        //   the motor to a specified sensor position.
        // kVoltage: Runs the m_motor at a constant voltage, if possible.
        // kFollower: The m_motor will run at the same throttle as the specified other talon.
        m_smartTalon2.SetControlMode (CANSpeedController::kPosition);
        m_smartTalon4.SetControlMode (CANSpeedController::kFollower);

//        m_motor4.SetControlMode (CANSpeedController::kFollower);

        // This command allows you to specify which feedback device to use when doing
        // closed-loop control. The options are:
        // AnalogPot: Basic analog potentiometer
        // QuadEncoder: Quadrature Encoder
        // AnalogEncoder: Analog Encoder
        // EncRising: Counts the rising edges of the QuadA pin (allows use of a
        //   non-quadrature encoder)
        // EncFalling: Same as EncRising, but counts on falling edges.
        m_smartTalon2.SetFeedbackDevice (CANTalon::QuadEncoder);
        m_smartTalon4.Set(2);


        // This sets the basic P, I , and D values (F, Izone, and rampRate can also
        //   be set, but are ignored here).
        // These must all be positive floating point numbers (SetSensorDirection will
        //   multiply the sensor values by negative one in case your sensor is flipped
        //   relative to your motor).
        // These values are in units of throttle / sensor_units where throttle ranges
        //   from -1023 to +1023 and sensor units are from 0 - 1023 for analog
        //   potentiometers, encoder ticks for encoders, and position / 10ms for
        //   speeds.
//        m_motor4.Set (2);

    }


    /**
     * Runs the motor from the output of a Joystick.
     */
    void OperatorControl ()
    {
        m_smartTalon2.SetPosition (0.0);
        m_smartTalon2.SetControlMode(CANSpeedController::kPosition);
        while (IsOperatorControl () && IsEnabled ())
        {
            // In closed loop mode, this sets the goal in the units mentioned above.
            // Since we are using an analog potentiometer, this will try to go to
            //   the middle of the potentiometer range.
            m_smartTalon2.Set (10000);

            Wait(5.0);

            m_smartTalon2.Set (-10000);

            Wait(5.0);

            m_smartTalon2.Set (0);

            Wait(10);
        }
    }

    void Test ()
    {
        while(IsTest() && IsEnabled())
        {
            if(m_gamepad.GetRawButton (1))
            {
                m_smartTalon2.tune (2, 10000);
            }
        }
    }
};

START_ROBOT_CLASS(Robot)
