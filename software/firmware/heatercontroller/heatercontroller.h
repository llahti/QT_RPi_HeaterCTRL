#ifndef HEATERCONTROLLER_H
#define HEATERCONTROLLER_H

#include "heatercontroller_global.h"
#include <QThread>

class HEATERCONTROLLERSHARED_EXPORT HeaterController
{

public:
  HeaterController();
  void StartController();

private:
  static QThread* ControllerThread;
};

#endif // HEATERCONTROLLER_H
