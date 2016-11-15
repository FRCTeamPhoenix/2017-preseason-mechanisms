//
// Created by William Gebhardt on 10/27/16.
//
#ifndef INC_2017_PRESEASON_MECHANISMS_SMARTTALON_H
#define INC_2017_PRESEASON_MECHANISMS_SMARTTALON_H

#include "WPILib.h"
#include "ProfilePoint.h"

class SmartTalon : public CANTalon
{
public:
    SmartTalon(int deviceNumber, double maxForwardSpeed, double maxReverseSpeed);

    ProfilePoint getNextPoint();
    ProfilePoint getCurrentPoint();

    void goTo(double position, double timeout /*= 0*/);
    void goAt(double speed);
    void goDistance(double distance, double timeout /*= 0*/);

    double getGoal();

    double getTimeout();

    double getCurrentTime();

private:
    ProfilePoint m_nextPoint;
    ProfilePoint m_currentPoint;

    double m_goal;
    double m_totalTime;
    double m_timeout;
    double m_maxForwardSpeed;
    double m_maxReverseSpeed;



};


#endif //INC_2017_PRESEASON_MECHANISMS_SMARTTALON_H
