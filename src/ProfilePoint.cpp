//
// Created by William Gebhardt on 10/27/16.
//

#include "ProfilePoint.h"

ProfilePoint::ProfilePoint(double a, double v, double t) :
        m_acceleration(a),
        m_velocity(v),
        m_time(t)
{

}

ProfilePoint::ProfilePoint (ProfilePoint &point) :
        m_acceleration(point.getAcceleration ()),
        m_velocity(point.getVelocity ()),
        m_time(point.getTime ())
{

}


double ProfilePoint::getAcceleration ()
{
    return m_acceleration;
}

double ProfilePoint::getVelocity ()
{
    return m_velocity;
}

double ProfilePoint::getTime ()
{
    return m_time;
}

void ProfilePoint::copyFrom (ProfilePoint& point)
{
    m_acceleration = point.getAcceleration ();
    m_velocity = point.getVelocity ();
    m_time = point.getTime ();
}
