//
// Created by William Gebhardt on 10/27/16.
//

#ifndef INC_2017_PRESEASON_MECHANISMS_PROFILEPOINT_H
#define INC_2017_PRESEASON_MECHANISMS_PROFILEPOINT_H


class ProfilePoint
{
public:
    ProfilePoint(double a, double v, double t);
    ProfilePoint(ProfilePoint& point);

    double getAcceleration();
    double getVelocity();
    double getTime();
    void copyFrom(ProfilePoint&);

private:
    double m_acceleration;
    double m_velocity;
    double m_time;

};


#endif //INC_2017_PRESEASON_MECHANISMS_PROFILEPOINT_H
