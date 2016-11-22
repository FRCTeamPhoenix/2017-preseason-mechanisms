#pragma once

#include "Action.h"

class ActionNone : public Action
{
public:
    ActionNone(double dummy);
    void init(void);
    bool execute(void);
};
