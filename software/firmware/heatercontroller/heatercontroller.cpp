#include "heatercontroller.h"
#include "hal.h"


HeaterController::HeaterController(QObject* parent) : QObject(parent)
{
  HAL *phal = new HAL(this);
  delete phal;
  //pHal = new HAL(this);
}

HeaterController::~HeaterController()
{
  if (pHal) {
    //delete pHal;
  }
}

/*
int HeaterController::StartController()
{
  // Initialize HAL layer
  pHal = new HAL(this);
  pHal->setHWType("hal_dummy");
  if (pHal->init()) {
    return 1;
  }
  // TODO: Start controller thread
  // TODO: Connect measurement signals to controller

  return 0;
}
*/
