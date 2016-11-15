//
// Created by William Gebhardt on 10/28/16.
//

#ifndef INC_2017_PRESEASON_MECHANISMS_SMARTTALONTRAJECTORYCONTROLLER_H
#define INC_2017_PRESEASON_MECHANISMS_SMARTTALONTRAJECTORYCONTROLLER_H

#include "WPILib.h"
#include "SmartTalon.h"


class SmartTalonTrajectoryController
{
public:
    SmartTalonTrajectoryController(SmartTalon* SmartTalons[], int numberOfSmartTalons);

    void initTread();
    SmartTalon* getTalon(int deviceNumber);
    int getNumberOfTalons();


private:

    SmartTalon* m_allSmartTalons[];
    int m_numberOfTalons;

};


#endif //INC_2017_PRESEASON_MECHANISMS_SMARTTALONTRAJECTORYCONTROLLER_H
