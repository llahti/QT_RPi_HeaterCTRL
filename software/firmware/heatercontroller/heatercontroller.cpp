#include "heatercontroller.h"


HeaterController::HeaterController()
{
}

int HeaterController::StartController()
{
  // Initialize HAL layer
  this->hal = new HAL(0);
  this->hal->setHWType("hal_dummy");
  if (this->hal->init()) {
    return 1;
  }
  // TODO: Start controller thread
  // TODO: Start measurement thread
  // TODO: Connect measurement signals to controller

  return 0;
}
