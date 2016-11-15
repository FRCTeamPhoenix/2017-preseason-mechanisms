//
// Created by William Gebhardt on 10/27/16.
//

#include "SmartTalon.h"
#include "math.h"


SmartTalon::SmartTalon (int deviceNumber, double maxForwardSpeed, double maxReverseSpeed) :
        CANTalon(deviceNumber),
        m_nextPoint(0,0,0),
        m_currentPoint(0,0,0),
        m_goal(0),
        m_totalTime(0),
        m_timeout(0),
        m_maxForwardSpeed(maxForwardSpeed),
        m_maxReverseSpeed(maxReverseSpeed)


{

}

ProfilePoint SmartTalon::getNextPoint ()
{
    return m_nextPoint;
}

ProfilePoint SmartTalon::getCurrentPoint ()
{
    return m_currentPoint;
}

double SmartTalon::getGoal ()
{
    return m_goal;
}

double SmartTalon::getTimeout ()
{
    return m_timeout;
}

double SmartTalon::getCurrentTime ()
{
    return m_currentPoint.getTime ();
}

double calculateTime(double displacement, double j){
    double beforeRoot = (32 / j) * displacement;
    double afterRoot = cbrt(beforeRoot);
    return afterRoot;
}

void SmartTalon::goTo (double position, double timeout = 0)
{
    SetControlMode (CANSpeedController::kPosition);
    m_timeout = timeout;
    m_goal = position;



}

void SmartTalon::goAt (double speed)
{
    SetControlMode (CANSpeedController::kSpeed);
    speed = (speed > 1) ? 1 : speed;
    speed = (speed < -1) ? -1 : speed;

    speed = (speed > 0) ? speed * m_maxForwardSpeed : speed * m_maxReverseSpeed;

    Set(speed);
}

void SmartTalon::goDistance (double distance, double timeout = 0)
{
    SetControlMode (CANSpeedController::kPosition);
    m_timeout = timeout;

    double cPos = GetPosition ();

    double fPos = cPos + distance;

    m_goal = fPos;

}

