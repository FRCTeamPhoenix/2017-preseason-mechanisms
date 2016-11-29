#pragma once

#include "Actions.h"
#include "BaseController.h"
#include <queue>

class AutoController : public BaseController
{
public:
    AutoController(void);
    virtual ~AutoController(void);

    void run(void);
    bool performAction(void);
    void clearQueue(void);
private:
    std::queue<Action*> m_queue;
};
