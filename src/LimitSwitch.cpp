#include "LimitSwitch.h"

LimitSwitch::LimitSwitch(uint32_t channel)
  : DigitalInput(channel)
{
}

LimitSwitch::~LimitSwitch(void)
{
}

bool
LimitSwitch::isPressed(void)
{
  return !get();
}
