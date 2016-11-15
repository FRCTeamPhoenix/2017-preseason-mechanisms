//
// Created by William Gebhardt on 10/27/16.
//

#include "SmartTalon.h"


SmartTalon::SmartTalon (int deviceNumber, double maxForwardSpeed, double maxReverseSpeed) :
        CANTalon(deviceNumber),
        m_goal(0),
        m_maxForwardSpeed(maxForwardSpeed),
        m_maxReverseSpeed(maxReverseSpeed),
        m_tuneTimer()


{

}
double SmartTalon::getGoal ()
{
    return m_goal;
}

void SmartTalon::goTo (double position)
{
    SetControlMode (CANSpeedController::kPosition);

    Set (position);

}

void SmartTalon::goAt (double speed)
{
    SetControlMode (CANSpeedController::kSpeed);
    speed = (speed > 1) ? 1 : speed;
    speed = (speed < -1) ? -1 : speed;

    speed = (speed > 0) ? speed * m_maxForwardSpeed : speed * m_maxReverseSpeed;

    Set(speed);
}

void SmartTalon::goDistance (double distance)
{
    SetControlMode (CANSpeedController::kPosition);

    double cPos = GetPosition ();

    double fPos = cPos + distance;

    Set (fPos);

}

/*
 * DO NOT CALL IN ANY CASE WHERE YOU NEED ROBOT CONTROL
 * TAKES CONTROL OF SYSTEM AND DOES NOT RETURN IT TILL DONE
 * Returns True when done
 */
bool SmartTalon::tune (double pInit, double tuneDistance)
{
    SmartDashboard::PutString ("DB/String 5", "Not Tuned");
    double speed = GetSpeed ();
    while(speed < -0.01 || speed > 0.01){
        speed = GetSpeed ();
    }

    SetP (pInit);
    SetI (0);
    SetD (0);
    bool notTuned = true;
    bool ocillation = false;

    while(notTuned){
        SetControlMode (CANSpeedController::kPosition);
        SetPosition (0.0);
        Set(tuneDistance);
        tuneDistance *= -1;

        m_tuneTimer.Reset ();
        m_tuneTimer.Start ();

        bool forward = true;
        int changeCount = 0;

//        Wait(2);
        std::ostringstream outputP;
        outputP << "P: ";
        outputP << (GetP ());
        SmartDashboard::PutString("DB/String 2", outputP.str());

        std::ostringstream outputD;
        outputD << "D: ";
        outputD << (GetD ());
        SmartDashboard::PutString("DB/String 3", outputD.str());

        while (m_tuneTimer.Get () < 5)
        {
            speed = GetSpeed ();
            if(speed > 0 && !forward)
            {
                changeCount++;
            }

            if(speed < 0 && forward)
            {
                changeCount++;
            }

            forward = speed > 0;

            Wait(0.1);
            std::ostringstream outputL;
             outputL << "Time: ";
             outputL << (5 - m_tuneTimer.Get ());
             SmartDashboard::PutString("DB/String 0", outputL.str());

            std::ostringstream outputO;
            outputL << "Occilation: ";
            outputL << (changeCount);
            SmartDashboard::PutString("DB/String 1", outputL.str());
        }

        m_tuneTimer.Stop ();

        if (changeCount <= 15  && !ocillation)
        {
            SetP (GetP () + 0.1 * pInit);
        }
        else if (changeCount > 1)
        {
            ocillation = true;
            SetD (GetD () + 10 * GetP ());
        }
        else
        {
            notTuned = false;
        }
    }
    SmartDashboard::PutString ("DB/String 5", "Tuned");

//    StopMotor ();
    return true;
}
