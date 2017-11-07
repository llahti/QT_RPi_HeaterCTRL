#include "heatercontroller.h"
#include "hal.h"


HeaterController::HeaterController(QObject* parent)
{
  this->setParent(parent);
}

HeaterController::~HeaterController()
{
  if (hal) {
    delete hal;
  }
}

int HeaterController::StartController()
{
  // Initialize HAL layer
  HAL phal = new HAL(this);
  hal = new HAL(this);
  hal->setHWType("hal_dummy");
  if (hal->init()) {
    return 1;
  }
  // TODO: Start controller thread
  // TODO: Connect measurement signals to controller

  return 0;
}
