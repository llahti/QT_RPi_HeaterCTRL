#ifndef HEATERCONTROLLER_H
#define HEATERCONTROLLER_H

#include "heatercontroller_global.h"
#include <QThread>
#include "hal.h"

class HEATERCONTROLLERSHARED_EXPORT HeaterController
{

public:
  HeaterController();
  int StartController();
  QThread* Controller = nullptr;

private:
  HAL* hal = nullptr;
};

#endif // HEATERCONTROLLER_H
