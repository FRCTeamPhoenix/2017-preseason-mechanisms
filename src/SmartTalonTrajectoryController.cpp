//
// Created by William Gebhardt on 10/28/16.
//

#include "SmartTalonTrajectoryController.h"



SmartTalonTrajectoryController::SmartTalonTrajectoryController (SmartTalon* talons[], int numberOfSmartTalons):
    m_numberOfTalons(numberOfSmartTalons)
{
    m_allSmartTalons = talons;
}

void SmartTalonTrajectoryController::initTread ()
{
    std::thread controllingThread(run, *this);
    controllingThread.detach ();
}

int SmartTalonTrajectoryController::getNumberOfTalons ()
{
    return m_numberOfTalons;
}


SmartTalon* SmartTalonTrajectoryController::getTalon (int place)
{
    return m_allSmartTalons[place];
}

void run(SmartTalonTrajectoryController &controller)
{
    int numberOfTalons = controller.getNumberOfTalons ();
    //while(true)
    {
        for(int i = 0; i < numberOfTalons; i++)
        {
            SmartTalon* currentTalon = controller.getTalon (i);
            ProfilePoint currentPoint = currentTalon->getCurrentPoint ();
            ProfilePoint nextPoint = currentTalon->getNextPoint ();





        }
    }
}
