#pragma once

#include "Actions.h"
#include <queue>

class AutoController : public BaseController
{
public:
    AutoController(void);
    virtual ~AutoController(void);

    void run(void);
    void performAction(void);
    void clearQueue(void);
private:
    std::queue<Action*> m_queue;
};
