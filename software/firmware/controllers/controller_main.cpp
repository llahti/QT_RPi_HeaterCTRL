#include "controller_main.h"

Controller_Main::Controller_Main(QObject *parent)
    : Controller_Interface(parent)
{
  // Connect HAL signals to controllers
  connect(hal, SIGNAL(measuredBoilerTemp(MeasurementPackage)),
          circPump, SLOT(ProcessMeasurement(MeasurementPackage)));


  // Setup HAL and Start HAL updates with 1 second periods
  hal.setHWType("hal_dummy");
  hal.init();
  hal.startUpdates(1.0);
}
