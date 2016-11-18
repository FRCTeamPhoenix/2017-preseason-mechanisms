#include "AutoController.h"
#include <iostream>

AutoController::AutoController(void)
{
}

AutoController::~AutoController(void)
{
}

void
RobotController::run(void)
{
    /* TODO: Make Y button clear queue of robot. */
    performAction();
}

/*
 * Returns false if queue is empty.
 */
bool
RobotController::performAction(void)
{
    if (m_queue.empty())
    {
	return false;
    }

    Action *currentAction = m_queue.front();
    if (!currentAction->isInitialized())
	currentAction->init();
    /* Execute returns true if finished */
    if (currentAction->execute())
    {
	delete currentAction;
	m_queue.pop();
    }
}

/*
 * Simple utility function to clear Action queue.
 */
void
RobotController::clearQueue()
{
    while (!m_queue.empty())
    {
	delete m_queue.front();
	m_queue.pop();
    }
}
